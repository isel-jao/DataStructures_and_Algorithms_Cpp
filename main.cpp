#include "main.hpp"

using namespace ft;

int main(int argc, char const *argv[])
{
	BinaryTree<int> *root = nullptr;

	std::cout << min(3, 4, 20) << std::endl;
	insert(root, 80);
	insert(root, 40);
	insert(root, 100);
	insert(root, 20);
	insert(root, 60);
	insert(root, 90);
	insert(root, 120);
	insert(root, 85);
	insert(root, 95);
	insert(root, 110);
	insert(root, 130);
	insert(root, 87);
	printTree(root);
	std::cout << "===========================================" << std::endl;
	BinaryTree<int> *node1 =  findMin(root);
	while (node1)
	{
		// DEBUG();
		std::cout << node1->key << " " << std::flush ;
		node1 = next(root, node1);
	}
	std::cout << std::endl;
	
	remove(root, 85);
	printTree(root);
	std::cout << "===========================================" << std::endl;
	node1 =  findMin(root);
	while (node1)
	{
		std::cout << node1->key << " " << std::flush ;
		node1 = next(root, node1);
	}
	std::cout << std::endl;

	makeEmpty(root);
	return 0;
}
