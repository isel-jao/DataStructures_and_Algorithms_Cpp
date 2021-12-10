#include "main.hpp"

namespace ft
{

	template <typename KEY>
	struct BinaryTree
	{
		KEY key;
		BinaryTree *parent;
		BinaryTree *left;
		BinaryTree *right;
		long height;

		BinaryTree(KEY k = KEY(), BinaryTree *p = nullptr, BinaryTree *l = nullptr, BinaryTree *r = nullptr)
			: key(k), parent(p), left(l), right(r), height(0) {}
		~BinaryTree() {}
	};

	template <typename KEY>
	long getHeight(BinaryTree<KEY> *node)
	{
		if (node == nullptr)
			return (-1);
		return node->height;
	}

	template <typename KEY>
	long getBalence(BinaryTree<KEY> *node) { return (getHeight(node->right) - getHeight(node->left)); }

	// recursion insertion
	template <typename KEY>
	BinaryTree<KEY> *insert(BinaryTree<KEY> *&root, KEY k, BinaryTree<KEY> *parent = nullptr)
	{
		BinaryTree<KEY> *node;
		if (root == nullptr)
		{
			root = new BinaryTree<KEY>(k, parent);
			return (root);
		}
		if (root->key < k)
			node = insert(root->right, k, root);
		else if (k < root->key)
			node = insert(root->left, k, root);
		else
			return (nullptr);
		return node;
	}

	template <typename KEY>
	void printTree(BinaryTree<KEY> *root, size_t depth = 0, std::string const &dil = "      ")
	{
		if (root == nullptr)
			return;
		long long balence = getBalence(root);
		printTree(root->right, depth + 1);
		for (size_t i = 0; i < depth; i++)
			std::cout << dil;
		std::cout << BOLDCYAN << root->key << RESET
				  << "/" << getHeight(root)
				  << "/" << ((balence < 2 && balence > -2) ? GREEN : RED) << balence << RESET
				  << std::endl;
		std::cout << RESET;
		printTree(root->left, depth + 1);
	}

	template <typename KEY>
	void balenceTree(BinaryTree<KEY> *&root, KEY key)
	{
		long balence = getBalence(root);
		if (balence <= 1 && balence >= -1)
			return;
		if (key < root->key)
		{
			if (key < root->left->key)
				ll_rotate(root);
			else
				lr_rotate(root);
		}
		else
		{
			if (key < root->right->key)
				rl_rotate(root);
			else
				rr_rotate(root);
		}
	}

	template <typename KEY>
	bool remove(BinaryTree<KEY> *&root, KEY const &key)
	{
		// base case (node not found)
		if (root == nullptr)
			return false;

		if (key < root->key)
			return (remove(root->left, key));
		if (root->key < key)
			return (remove(root->right, key));

		// if root->key == key
		BinaryTree<KEY> *tmp = root;

		// if node has only the right child or no children
		if (root->left == nullptr)
		{
			debug();
			if (root->right)
				root->right->parent = root->parent;
			root = root->right;
		}

		// if node has only the left child
		else if (root->right == nullptr)
		{
			debug();
			root->left->parent = root->parent;
			root = root->left;
		}

		// if node has both children
		else
		{
			DEBUG();
			BinaryTree<KEY> *succParent = nullptr;
			BinaryTree<KEY> *succ = root->right;
			while (succ->left)
			{
				succParent = succ;
				succ = succ->left;
			}
			if (succParent)
			{
				succParent->left = succ->right;
				if (succ->right)
					succ->right->parent = succParent;
				succ->right = root->right;
				root->right->parent = succ;
			}
			root->left->parent = succ;
			succ->left = root->left;

			succ->parent = root->parent;
			root = succ;
		}

		delete tmp;
		return true;
	}

	// finde node with the given key
	// if found remove the node and return true (remove successfull)
	// else return false (remove failed)
	// template <typename KEY>
	// bool remove(BinaryTree<KEY> *&root, KEY const &k)
	// {
	// 	// if key not foune
	// 	if (!root)
	// 		return false;
	// 	if (k < root->key)
	// 		return (remove(root->left, k));
	// 	if (root->key < k)
	// 		return (remove(root->right, k));
	// 	// if k == node->key
	// 	// if node has no left
	// 	if (root->left == nullptr)
	// 	{
	// 		BinaryTree<KEY> *tmp = root;
	// 		delete root;
	// 		root = tmp->right;
	// 	}
	// 	// if node has no right
	// 	else if (root->right == nullptr)
	// 	{

	// 		BinaryTree<KEY> *tmp = root;
	// 		delete root;
	// 		root = tmp->left;
	// 	}
	// 	// if node has both children
	// 	else
	// 	{
	// 		BinaryTree<KEY> *succParent = nullptr;
	// 		BinaryTree<KEY> *succ = root->right;
	// 		while (succ->left)
	// 		{
	// 			succParent = succ;
	// 			succ = succParent->left;
	// 		}
	// 		if (succParent)
	// 			succParent->left = succ->right;
	// 		succ->left = root->left;
	// 		root = succ;
	// 		succ->right = succParent;
	// 	}
	// 	return true;
	// }

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

	template <typename KEY>
	void makeEmpty(BinaryTree<KEY> *&root)
	{
		if (root == nullptr)
			return;
		makeEmpty(root->left);
		makeEmpty(root->right);
		delete root;
		root = nullptr;
	}

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
}