#ifndef SPLAYTREE_HPP
#define SPLAYTREE_HPP

template <typename KEY>
struct SplayTree
{
	KEY _key;
	SplayTree *_parent;
	SplayTree *_left;
	SplayTree *_right;

	SplayTree(KEY const &k = KEY(), SplayTree *p = nullptr, SplayTree *l = nullptr, SplayTree *r = nullptr)
		: _key(k), _parent(p), _left(l), _right(r) {}
	~SplayTree() {}
};

// template <typename KEY>
// SplayTree<KEY> *insert(SplayTree<KEY> *&root, KEY const &k)
// {
// 	SplayTree<KEY> *tmp;
// 	SplayTree<KEY> *parent;

// 	if(root == nullptr)
// 	{
// 		root = new SplayTree<KEY>(k);
// 		return root;
// 	}
// 	tmp = root;
// 	while (tmp)
// 	{
// 		parent = tmp;
// 		if(k > tmp->_key)
// 			tmp = tmp->_right;
// 		else if (k< tmp->_key)
// 			tmp = tmp->_right;
// 		else
// 			return(nullptr);
// 	}
// 	tmp = new SplayTree<KEY>(k);
// 	if (parent->_key < tmp->_key)
// 		parent->_right = tmp;
// 	else
// 		parent->_left = tmp;
// 	return(tmp);
// }

template <typename KEY>
SplayTree<KEY> *insert(SplayTree<KEY> *&root, KEY const &k, SplayTree<KEY> *p = nullptr)
{
	if (root == nullptr)
	{
		root = new SplayTree<KEY>(k, p);
		return root;
	}
	if (root->_key < k)
		return (insert(root->_right, k, root));
	else if (k < root->_key)
		return (insert(root->_left, k, root));
	return nullptr;
}
template <typename KEY>
SplayTree<KEY> *&find(SplayTree<KEY> *&root, KEY const &k)
{
	if (k == root->_key)
		return root;
	if (k < root->_key)
		return (find(root->_left, k));
	else
		return (find(root->_right, k));
}
template <typename KEY>
void right_rotate(SplayTree<KEY> *&x)
{
	SplayTree<KEY> *left = x->_left;
	x->_left = left->_right;
	if (left->_right)
		left->_right->_parent = x;
	left->_parent = x->_parent;
	left->_right = x;
	x->_parent = left;
	x = left;
}
#endif