#include "main.hpp"

#define DEBUG() std::cout << "function: " << __FUNCTION__ << ", line: " << __LINE__ << std::endl

template <typename KEY>
struct BinaryTree
{
	KEY key;
	BinaryTree *left;
	BinaryTree *right;
	long height;

	BinaryTree(KEY k = KEY(), BinaryTree *l = nullptr, BinaryTree *r = nullptr) : key(k), left(l), right(r), height(0) {}
	~BinaryTree() {}
};
template <typename KEY>
long getHeight(BinaryTree<KEY> *node)
{
	if (node)
		return (node->height);
	return (-1);
}

// recursion
template <typename KEY>
BinaryTree<KEY> *insert(BinaryTree<KEY> *&root, KEY k)
{
	BinaryTree<KEY> *node;
	if (root == nullptr)
	{
		root = new BinaryTree<KEY>(k);
		return (root);
	}
	if (root->key < k)
		node = insert(root->right, k);
	else if (k < root->key)
		node = insert(root->left, k);
	else
		return (nullptr);
	return node;
}



template <typename KEY>
void printTree(BinaryTree<KEY> *root, int depth = 0, std::string const &dil = "      ")
{
	if (root == nullptr)
		return;
	printTree(root->right, depth + 1);
	for (size_t i = 0; i < depth; i++)
		std::cout << dil;
	std::cout << root->key << "\n";
	printTree(root->left, depth + 1);
}



// finde node with the given key
// if found remove the node and return true (remove successfull)
// else return false (remove failed)
template <typename KEY>
bool remove(BinaryTree<KEY> *&root, KEY const &k)
{
	// if key not foune
	if (!root)
		return false;
	if (k < root->key)
		return (remove(root->left, k));
	if (root->key < k)
		return (remove(root->right, k));
	// if k == node->key
	// if node has no left 
	if (root->left == nullptr)
	{
		BinaryTree<KEY> *tmp = root;
		delete root;
		root = tmp->right;
	}
	// if node has no right
	else if (root->right == nullptr)
	{

		BinaryTree<KEY> *tmp = root;
		delete root;
		root = tmp->left;
	}
	// if node has both children
	else
	{
		BinaryTree<KEY> *succParent = nullptr;
		BinaryTree<KEY> *succ = root->right;
		while (succ->left)
		{
			succParent = succ;
			succ = succParent->left;
		}
		if (succParent)
			succParent->left = succ->right;
		succ->left = root->left;
		root = succ;
		succ->right = succParent;
	}
	return true;
}

template <typename KEY>
BinaryTree<KEY> *findMin(BinaryTree<KEY> *node)
{
	if (node == nullptr)
		return nullptr;
	while (node->left)
	{
		node = node->left;
	}
	return node;
}

template <typename KEY>
BinaryTree<KEY> *next(BinaryTree<KEY> *root, BinaryTree<KEY> *node)
{
	BinaryTree<KEY> *tmp = nullptr;
	BinaryTree<KEY> *parent = nullptr;
	BinaryTree<KEY> *succ = nullptr;
	if (!root || !node)
		return nullptr;
	// if node has right the next seccessor is the min child in the right subtree
	if (node->right != nullptr)
		return (findMin(node->right));
	tmp = root;
	// if node the node dont have a right child the next succ is the smalest parent that have key greater than the node's key if found
	// else return nullptr
	while (tmp->key != node->key)
	{
		parent = tmp;
		if (node->key < tmp->key)
		{
			succ = tmp;
			tmp = tmp->left;
		}
		else if (tmp->key < node->key)
			tmp = tmp->right;
	}
	return succ;
}

template <typename KEY>
BinaryTree<KEY> *findMax(BinaryTree<KEY> *node)
{
	if (node == nullptr)
		return nullptr;
	while (node->right)
	{
		node = node->right;
	}
	return node;
}

template <typename KEY>
BinaryTree<KEY> *prev(BinaryTree<KEY> *root, BinaryTree<KEY> *node)
{
	BinaryTree<KEY> *tmp = nullptr;
	BinaryTree<KEY> *parent = nullptr;
	BinaryTree<KEY> *succ = nullptr;
	if (!root || !node)
		return nullptr;
	// if node has left the previous seccessor is the max child in the right subtree
	if (node->left != nullptr)
		return (findMax(node->left));
	// if node the node dont have a left child the prev succ is the bigest parent that have key smaller than the node's key if found
	// else return nullptr
	tmp = root;
	while (node->key != tmp->key)
	{
		if (tmp->key < node->key)
		{
			succ = tmp;
			tmp = tmp->right;
		}
		else if (node->key < tmp->key)
			tmp = tmp->left;
	}
	return (succ);
}

template <typename KEY>
void ll_rotate(BinaryTree<KEY> *&node)
{
	BinaryTree<KEY> *tmp = node->left->right;
	BinaryTree<KEY> *left = node->left;
	left->right = node;
	node->left = tmp;
	node = left;
}

template <typename KEY>
void rr_rotate(BinaryTree<KEY> *&node)
{
	BinaryTree<KEY> *tmp = node->right->left;
	BinaryTree<KEY> *right = node->right;
	right->left = node;
	node->right = tmp;
	node = right;
}
template <typename KEY>
void rl_rotate(BinaryTree<KEY> *&node)
{
	ll_rotate(node->right);
	rr_rotate(node);
}

template <typename KEY>
void lr_rotate(BinaryTree<KEY> *&node)
{
	rr_rotate(node->left);
	ll_rotate(node);
}


template <typename KEY>
BinaryTree<KEY> *find(BinaryTree<KEY> *root, KEY const &key)
{
	if (root == nullptr)
		return nullptr;
	if (key < root->key)
		return find(root->left, key);
	if (root->key < key)
		return find(root->right, key);
	return root;
}

// template <typename KEY>
// BinaryTree *remove_rec(BinaryTree *root, BinaryTree *p, KEY key)
// {
// 	if (root == nullptr)
// 		return nullptr;
// 	if (root->key == k)
// 	{
// 		if (root->left == nullptr && root->rigth == nullptr)
// 		{
// 			BinaryTree *tmp;
// 			if (p->left == root)
// 				p->left = nullptr;
// 			else
// 				p->right = nullptr;
// 			delete (root);
// 		}
// 		else if (root->left == nullptr)
// 		{
// 			if (p->left == root)
// 				p->left = root->rigth;
// 			else
// 				p->right = root->rigth;
// 			delete (root);
// 		}
// 		else if (root->rigth == nullptr)
// 		{
// 			if (p->left == root)
// 				p->left = root->left;
// 			else
// 				p->right = root->left;
// 			delete (root);
// 		}
// 		else
// 		{

// 		}
// 	}
// 	else if (root->key < key)
// 		remove_rec(root->right, root, key);
// 	else
// 		remove_rec(root->left, root, key);
// }

// iterative insertion
// template <typename KEY>
// BinaryTree<KEY> *insert(BinaryTree<KEY> *&root, KEY const &k)
// {
// 	if (root == nullptr)
// 	{
// 		root = new BinaryTree<KEY>(k);
// 		return (root);
// 	}
// 	BinaryTree<KEY> *tmp = root;
// 	BinaryTree<KEY> *p;
// 	while (tmp != NULL)
// 	{
// 		p = tmp;
// 		if (tmp->key < k)
// 			tmp = tmp->right;
// 		else if (k < tmp->key)
// 			tmp = tmp->left;
// 		else
// 			return (nullptr);
// 	}
// 	tmp = new BinaryTree<KEY>(k);
// 	if (k < p->key)
// 		p->left = tmp;
// 	else
// 		p->right = tmp;
// 	return (tmp);
// }