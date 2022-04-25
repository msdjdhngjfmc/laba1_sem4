#pragma once
#include <iomanip>
#include <iostream>
#include <list>

using namespace std;

enum RedBlackTreeColor { Black, Red };

template<class KeyType>
struct  RedBlackTreeNode
{
	KeyType key;
	int value;
	RedBlackTreeColor color;
	RedBlackTreeNode<KeyType>* left;
	RedBlackTreeNode<KeyType>* right;
	RedBlackTreeNode<KeyType>* parent;
	RedBlackTreeNode(KeyType k, int v, RedBlackTreeColor c, RedBlackTreeNode* p, RedBlackTreeNode* l, RedBlackTreeNode* r) :
		key(k), value(v), color(c), parent(p), left(l), right(r) { };
};

template<class T>
class  RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void insert(T key, int value);
	void remove(T key);
	RedBlackTreeNode<T>* search(T key);
	void print();
	void valuesList(list<T>& valueList);
	void keysList(list<T>& keyList);
	void clear();
	int isEmpty();

private:
	void leftRotate(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* x);
	void rightRotate(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* y);

	void insert(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* node);
	void InsertBalance(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* node);
	void clear(RedBlackTreeNode<T>*& node);

	void remove(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* node);
	void removeBalance(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* node, RedBlackTreeNode<T>* parent);

	RedBlackTreeNode<T>* search(RedBlackTreeNode<T>* node, T key) const;
	void print(RedBlackTreeNode<T>* node)const;
	void valuesList(RedBlackTreeNode<T>* tree, list<T>& valueList);
	void keysList(RedBlackTreeNode<T>* tree, list<T>& keyList);
private:
	RedBlackTreeNode<T>* root;
};

template<class T>
RedBlackTree<T>::RedBlackTree() :root(NULL) {
	root = nullptr;
}

template<class T>
RedBlackTree<T>::~RedBlackTree() {
	clear(root);
}

template<class T>
void RedBlackTree<T>::leftRotate(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* x) {
	RedBlackTreeNode<T>* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};

template<class T>
void RedBlackTree<T>::rightRotate(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* y) {
	RedBlackTreeNode<T>* x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};

template<class T>
void RedBlackTree<T>::insert(T key, int value)
{
	RedBlackTreeNode<T>* z = new RedBlackTreeNode<T>(key, value, Red, NULL, NULL, NULL);
	insert(root, z);
};

template<class T>
void RedBlackTree<T>::insert(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* node)
{
	RedBlackTreeNode<T>* x = root;
	RedBlackTreeNode<T>* y = NULL;
	while (x != NULL)
	{
		y = x;
		if (node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if (y != NULL)
	{
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
	}
	else
		root = node;
	node->color = Red;
	InsertBalance(root, node);
};

template<class T>
void RedBlackTree<T>::InsertBalance(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* node)
{
	RedBlackTreeNode<T>* parent;
	parent = node->parent;
	while (node != RedBlackTree::root && parent->color == Red)
	{
		RedBlackTreeNode<T>* gparent = parent->parent;
		if (gparent->left == parent)
		{
			RedBlackTreeNode<T>* uncle = gparent->right;
			if (uncle != NULL && uncle->color == Red)
			{
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					leftRotate(root, parent);
					swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else
		{
			RedBlackTreeNode<T>* uncle = gparent->left;
			if (uncle != NULL && uncle->color == Red)
			{
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rightRotate(root, parent);
					swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
}

template<class T>

void RedBlackTree<T>::clear()
{
	if (root != NULL)
		clear(root);
}
template<class T>

void RedBlackTree<T>::clear(RedBlackTreeNode<T>*& node)
{
	if (node == NULL)
		return;
	clear(node->left);
	clear(node->right);
	delete node;
	node = nullptr;
}

template<class T>
void RedBlackTree<T>::remove(T key)
{
	RedBlackTreeNode<T>* deletenode = search(root, key);
	if (deletenode != NULL)
		remove(root, deletenode);
}

template<class T>
void RedBlackTree<T>::remove(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* node)
{
	RedBlackTreeNode<T>* child, * parent;
	RedBlackTreeColor color;
	if (node->left != NULL && node->right != NULL)
	{
		RedBlackTreeNode<T>* replace = node;
		replace = node->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;

		child = replace->right;
		parent = replace->parent;
		color = replace->color;


		if (parent == node)
			parent = replace;
		else
		{
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			removeBalance(root, child, parent);

		delete node;
		return;
	}
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}

	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}

	else
		RedBlackTree::root = child;

	if (color == Black)
	{
		removeBalance(root, child, parent);
	}
	delete node;

}

template<class T>
void RedBlackTree<T>::removeBalance(RedBlackTreeNode<T>*& root, RedBlackTreeNode<T>* node, RedBlackTreeNode<T>* parent)
{
	RedBlackTreeNode<T>* othernode;
	while ((!node) || node->color == Black && node != RedBlackTree::root)
	{
		if (parent->left == node)
		{
			othernode = parent->right;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				leftRotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == Black)
				{
					othernode->left->color = Black;
					othernode->color = Red;
					rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->right->color = Black;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				rightRotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black))
			{
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == Black)
				{
					othernode->right->color = Black;
					othernode->color = Red;
					leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->left->color = Black;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = Black;
}

template<class T>
RedBlackTreeNode<T>* RedBlackTree<T>::search(T key)
{
	return search(root, key);
}

template<class T>
RedBlackTreeNode<T>* RedBlackTree<T>::search(RedBlackTreeNode<T>* node, T key) const
{
	if (node != NULL) {
		if (node->key == key)
			return node;
		else
			if (key > node->key)
				return search(node->right, key);
			else
				return search(node->left, key);
	}
	else {
		cout << "NOT FOUND !!!\n";
		cout << "return root...\n";
		return(root);
	}
}

template<class T>
void RedBlackTree<T>::print() {
	if (root == NULL)
		cout << "Empty tree...\n";
	else
		print(root);
}

template<class T>
void RedBlackTree<T>::print(RedBlackTreeNode<T>* node)const {
	if (node == NULL)
		return;
	if (node->parent == NULL)
		cout << "key: " << node->key << " value: " << node->value << " colore: (" << node->color << ") is root" << endl;
	else if (node->parent->left == node)
	{
		cout << "key: " << node->key << " value: " << node->value << " colore: (" << node->color << ") is " << node->parent->key << "'s " << "left child" << endl;
	}
	else
	{
		cout << "key: " << node->key << " value: " << node->value << " colore: (" << node->color << ") is " << node->parent->key << "'s " << "right child" << endl;
	}
	print(node->left);
	print(node->right);
}

template<class T>
void RedBlackTree<T>::valuesList(list<T>& valueList) {
	if (root == NULL)
		cout << "Empty tree...\n";
	else
		valuesList(root, valueList);
};

template<class T>
void RedBlackTree<T>::valuesList(RedBlackTreeNode<T>* tree, list<T>& valueList) {
	if (tree != NULL) {
		valueList.push_back(tree->value);
		valuesList(tree->left, valueList);
		valuesList(tree->right, valueList);
	}
}

template<class T>
void RedBlackTree<T>::keysList(list<T>& keyList) {
	if (root == NULL)
		cout << "Empty tree...\n";
	else
		keysList(root, keyList);
};

template<class T>
void RedBlackTree<T>::keysList(RedBlackTreeNode<T>* tree, list<T>& keyList) {
	if (tree != NULL) {
		keyList.push_back(tree->key);
		keysList(tree->left, keyList);
		keysList(tree->right, keyList);
	}
}

template<class T>
int RedBlackTree<T>::isEmpty() {
	if (root == NULL) {
		cout << "Empty tree...\n";
		return(0);
	}
	else {
		return(1);
	}
}
