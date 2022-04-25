#include <iomanip>
#include <iostream>
#include <windows.h>
#include <list>

#include"RBTree.h"

using namespace std;

template<class T>
list<T>valueList;

template<class T>
list<T>keyList;

int main()
{
	setlocale(LC_ALL, "Russian");

	int nums[10] = { 10,40,30,60,90,70,20,50,80,100 };
	int variables[10] = { 1,4,3,6,9,7,2,5,8,10 };
	RedBlackTree<int> tree;


	for (int i = 0; i < 10; i++) {
		tree.insert(nums[i], variables[i]);
	}

	cout << "Red and black wood details: \n";
	tree.print();

	cout << "\nFind node with key 30: ";
	cout << tree.search(30)->value << "\n\n";

	cout << "Delete node with key 100\n";
	tree.remove(100);
	cout << endl;

	cout << "List of values: \n";
	tree.valuesList(valueList<int>);
	for (auto v : valueList<int>) cout << v << " ";
	cout << "\n";
	cout << endl;

	cout << "List of keys: \n";
	tree.keysList(keyList<int>);
	for (auto v : keyList<int>) cout << v << " ";
	cout << "\n";
	cout << endl;

	cout << "\nRed and black wood details: \n";
	tree.print();

	tree.clear();

	return 0;
}
