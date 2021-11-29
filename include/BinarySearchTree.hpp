
#include "main.hpp"

#define DUBUG() std::cout << __FUNCTION__ << ", " << __LINE__ << std::endl

template <typename Key, typename Comparator = std::less<Key>>
class BinarySearchTree
{
public:
	BinarySearchTree() : root(nullptr) , _size(0){}

	BinarySearchTree(const BinarySearchTree &rhs) : root(clone(rhs->root)) {}

	~BinarySearchTree() { makeEmpty(root); }

	const Key &findMin() const
	{
		BinaryNode &min = findMin(root);
		if (min)
			return (min->key);
		return (Key());
	}



	void insert(const Key &x) { insert(x, root); }

	void printTree(std::ostream &out = std::cout) const
	{
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			printTree(root, out);
	}

private:
	struct BinaryNode
	{
		Key key;
		BinaryNode *parent;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(const Key &key, BinaryNode *p = nullptr, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
			: key{key}, left{lt}, right{rt}, parent(p) {}
	};

	BinaryNode *root;
	size_t _size;
	Comparator cmp;

	void insert(const Key &key, BinaryNode *&t, BinaryNode *p = nullptr)
	{
		if (t == nullptr)
			t = new BinaryNode(key, p);
		else if (cmp(key, t->key)) // (key < t->key)
			insert(key, t->left, t);
		else if (cmp(t->key, key)) // (t->key < key)
			insert(key, t->right, t);
	}

	void printTree(BinaryNode const *t, std::ostream &out = std::cout)
	{
		if (t == nullptr)
			return;
		printTree(t->left, out);
		out << t->key << " ";
		printTree(t->right, out);
	}
	void remove(const Key &key, BinaryNode *&t)
	{
		if (t == nullptr)
			return;

		if (cmp(key, t->key)) // (key < t->key)
			remove(key, t->left);

		else if (cmp(t->key, key)) // (t->key < key)
			remove(key, t->right);

		else
		{
			if (t->left == nullptr && t->right == nullptr)
			{
				delete (t);
				t = nullptr;
			}

			else if (t->right == nullptr)
			{
				BinaryNode *tmp = t;
				t->left->parent = t->parent;
				t = t->left;
				delete (tmp);
			}

			else if (t->left == nullptr)
			{
				BinaryNode *tmp = t;
				t->right->parent = t->parent;
				t = t->right;
				delete (tmp);
			}
			else
			{
				BinaryNode *tmp = t;
				BinaryNode *prevAscendent = t->left;
				BinaryNode *father = t;
				while (prevAscendent->right)
				{
					father = prevAscendent;
					prevAscendent = prevAscendent->right;
				}
				prevAscendent->right = t->right;
				if (father != t)
				{
					father->right = prevAscendent->left;
					prevAscendent->left = t->left;
				}
				prevAscendent->parent = t->parent;
				t = prevAscendent;
				delete tmp;
			}
		}
	}
	BinaryNode *findMin(BinaryNode *t)
	{
		if (t == nullptr)
			return (nullptr);
		if (t->left == nullptr)
			return (t);
		return (findMin(t->left));
	}
	BinaryNode *findMax(BinaryNode *t)
	{
		if (t == nullptr)
			return (nullptr);
		if (t->right == nullptr)
			return (t);
		return (findMax(t->right));
	}
	bool contains(const Key &key, BinaryNode *t)
	{
		if (t == nullptr)
			return (false);
		if (cmp(key, t->key)) // (key < t->key)
			return (contains(key, t->left));
		if (cmp(t->key, key)) // (t->key < key)
			return (contains(key, t->right));
		return (true);
	}
	void makeEmpty(BinaryNode *&t)
	{
		if (t == nullptr)
			return;
		if (t->left)
			makeEmpty(t->left);
		if (t->right)
			makeEmpty(t->right);
		delete (t);
		t = nullptr;
	}
	BinaryNode *clone(BinaryNode *t, BinaryNode *p = nullptr)
	{
		if (t == nullptr)
			return nullptr;
		return new BinaryNode(t->key, p, clone(t->left, t), clone(t->right, t));
	}
};
