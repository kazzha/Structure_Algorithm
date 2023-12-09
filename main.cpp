#include "BinarySearchTree.h"

int main()
{
	BST tree;
	tree.insert(12);
	tree.insert(1);
	tree.insert(2);
	tree.insert(9);
	tree.deleteValue(9);
	tree.inOrder();
	std::cout << tree.GetRoot();
}