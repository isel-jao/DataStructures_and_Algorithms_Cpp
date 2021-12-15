#include "main.hpp"

using namespace ft;

template <typename BinaryTree>
void printTree(BinaryTree*root, size_t depth = 0, std::string const &dil = "      ")
{
	if (root == nullptr)
		return;
	printTree(root->_right, depth + 1);
	for (size_t i = 0; i < depth; i++)
		std::cout << dil;
	std::cout << BOLDCYAN << root->_key << RESET << std::endl;
	printTree(root->_left, depth + 1);
}
int main(int argc, char const *argv[])
{
	SplayTree<int> *root = nullptr;

	insert(root, 7);
	insert(root, 6);
	insert(root, 5);
	insert(root, 4);
	insert(root, 3);
	insert(root, 2);
	insert(root, 1);
	printTree(root);
	right_rotate(root);
	printTree(root);
	right_rotate(find(root, 4));
	printTree(root);
	right_rotate(find(root, 5));
	printTree(root);
	SplayTree<int > *node = find(root, 7);
	while (node)
	{
		std::cout << node->_key << " ";
		node = node->_parent;
	}
	std::cout << std::endl;
	

	return 0;
}


