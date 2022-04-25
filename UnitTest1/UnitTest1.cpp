#include "pch.h"
#include "CppUnitTest.h"
#include"RedBlackTree.h"

#include <iomanip>
#include <iostream>
#include <windows.h>
#include <list>

template<class T>
list<T>valueList;

template<class T>
list<T>keyList;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace RBTreeUnitTests

{
	TEST_CLASS(RBTreeUnitTests)
	{
	public:
		
		TEST_METHOD(insert_search_test)
		{
			RedBlackTree<int> tree;

			tree.insert(10, 10);
			
			Assert::IsTrue(tree.search(10)->key==10);
			Assert::IsTrue(tree.search(10)->value==10);
		}

		TEST_METHOD(remove_test)
		{
			RedBlackTree<int> tree;

			tree.insert(10, 10);
			tree.insert(20, 20);
			tree.remove(20);

			Assert::IsTrue(tree.search(20)->key==10);
			Assert::IsTrue(tree.search(20)->value==10);
		}

		TEST_METHOD(keysList_valuesList_test)
		{
		
			bool hehe;
			bool hehe2;
			int nums[2] = { 10,20 };
			int variables[2] = { 10,20 };
			RedBlackTree<int> tree;


			for (int i = 0; i < 2; i++) {
				tree.insert(nums[i], variables[i]);
			}

			tree.keysList(keyList<int>);
			tree.valuesList(valueList<int>);

			int i = 0;
			for (auto v : valueList<int>) {

				if (v == variables[i]) {
					hehe = true;
				}
				else {
					hehe = false;
					break;
				}
				i++;
			}

			i = 0;
			for (auto v : keyList<int>) {

				if (v == nums[i]) {
					hehe2 = true;
				}
				else {
					hehe2 = false;
					break;
				}
				i++;
			}

			Assert::IsTrue(hehe == true);
			Assert::IsTrue(hehe2 == true);

		}

		TEST_METHOD(isEmpty_test)
		{
			RedBlackTree<int> tree;
			RedBlackTree<int> tree1;

			tree.insert(10, 10);
			tree.insert(20, 20);
			tree.clear();

			tree1.insert(10, 10);
			tree1.insert(20, 20);

			Assert::IsTrue(tree.isEmpty() == 0);
			Assert::IsTrue(tree1.isEmpty() == 1);
		}
		TEST_METHOD(clear_test)
		{
			RedBlackTree<int> tree;

			tree.insert(10, 10);
			tree.insert(20, 20);
			
			tree.clear();
			
			Assert::IsTrue(tree.isEmpty()==0);
		}
	};
}