#ifndef AVL_HPP
#define AVL_HPP

#include "main.hpp"

template <typename Key, typename Comparator = std::less<Key>>
class AVL
{
public:
	AVL() : root_(nullptr), size_(0) {}

	~AVL() {}
	void insert(Key const &k)
	{
		if (!insert(root_, k))
			return;
		balanceTree(root_, k);
		size_++;
	}

	void print()
	{
		if (root_)
			print(root_);
		else
			std::cout << "tree is empty";
		std::cout << std::endl;
	}

private:
	struct BinaryNode
	{
		Key key_;
		BinaryNode *left_;
		BinaryNode *right_;
		BinaryNode *parent_;
		size_t height_;

		BinaryNode(Key const &k, BinaryNode *l = nullptr, BinaryNode *r = nullptr, BinaryNode *p = nullptr)
			: key_(k), left_(l), right_(r), parent_(p), height_(1) {}

		BinaryNode(BinaryNode const &obj) { *this = obj; }

		BinaryNode &operator=(BinaryNode const &rhs)
		{
			if (this == &rhs)
				return *this;
			key_ = rhs.key_;
			parent_ = rhs.parent_;
			left_ = clone(rhs.left_, this);
			right_ = clone(rhs.right_, this);
		}
		~BinaryNode()
		{
			delete (this->_left);
			delete (this->right);
		}

		BinaryNode *clone(BinaryNode *node, BinaryNode *p = nullptr)
		{
			if (node == nullptr)
				return (nullptr);
			return new BinaryNode(node->key_, clone(node->left_, node), clone(node->right, node), p);
		}
	};

	size_t height(BinaryNode *node) const
	{
		if (node)
			return node->height_;
		return 0;
	}

	long long int getBalance(BinaryNode *node) const
	{
		if (!node)
			return 0;
		return (height(node->right_) - height(node->left_));
	}

	BinaryNode *insert(BinaryNode *&node, Key const &k, BinaryNode *p = nullptr)
	{
		if (node == nullptr)
		{
			node = new BinaryNode(k, nullptr, nullptr, p);
			inc_height(p);
			return node;
		}
		if (cmp(k, node->key_))
			return insert(node->left_, k, node);
		if (cmp(node->key_, k))
			return insert(node->right_, k, node);
		return nullptr;
	}
	void print(BinaryNode *root, std::string const &dil = "      ")
	{
		if (root == nullptr)
			return;
		size_t depth = getDepth(root);
		print(root->right_);
		for (size_t i = 0; i < depth; i++)
			std::cout << dil;
		std::cout << root->key_ << "/" << root->height_ << "/" << getBalance(root) << "\n\n";
		print(root->left_);
	}
	BinaryNode *clone(BinaryNode *node, BinaryNode *p = nullptr)
	{
		BinaryNode::clone(node, p);
	}
	void inc_height(BinaryNode *node)
	{
		if (!node)
			return;
		node->height_ = 1 + std::max(height(node->left_), height(node->right_));
		inc_height(node->parent_);
	}

	size_t getDepth(BinaryNode const *node) const
	{
		if (!node->parent_)
			return 0;
		return (1 + getDepth(node->parent_));
	}
	void balanceTree(BinaryNode *&root, Key const &k)
	{
		long long int balance = getBalance(root);
		if (balance > 1)
		{
			if (cmp(k, root->right_->key_))
				rl_rotate(root);
			else
				rr_rotate(root);
		}
		else if (balance < -1)
		{
			if (cmp(k, root->left_->key_))
				ll_rotate(root);
			else
				lr_rotate(root);
		}
	}
	void ll_rotate(BinaryNode *&grandParent)
	{
		BinaryNode *p = grandParent->left_;

		p->parent_ = grandParent->parent_;
		grandParent->parent_ = p;

		grandParent->left_ = p->right_;
		p->right_->parent_ = grandParent;

		p->right_ = grandParent;



		print(p);
	}
	void rr_rotate(BinaryNode *&grandParent)
	{
	}
	void rl_rotate(BinaryNode *&grandParent)
	{
	}
	void lr_rotate(BinaryNode *&grandParent)
	{
	}

protected:
	BinaryNode *root_;
	size_t size_;
	Comparator cmp;
};

#endif