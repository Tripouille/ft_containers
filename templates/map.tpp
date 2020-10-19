#include "map.hpp"

/* Constructor */
/** empty (1) **/
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::map(const key_compare & comp,
            						const allocator_type & alloc)
								: _compare(comp), _alloc(alloc), _root(NULL), _size(0)
{

}

/** range (2) **/
/** copy (3) **/


/* Destructor */
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::~map(void)
{
	_deallocate_btree(_root);
}

/* Operator */


/* Public functions */
/** Iterators **/


/** Capacity **/


/** Element access **/
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::mapped_type & 
ft::map<Key, T, Compare, Alloc>::operator[](const key_type & k)
{
	node * n = _find_node(k);

	if (n == NULL)
	{
		n = _node_alloc.allocate(1);
		_node_alloc.construct(n, node(k, mapped_type()));
		_insert_node(n);
	}
	return (n->value);
}

/** Modifiers **/


/** Observers **/


/** Operations **/


/** Allocator **/


/** Private functions **/
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::node *
ft::map<Key, T, Compare, Alloc>::_find_node(const key_type & k)
{
	node * tmp = _root;
	while (tmp)
		if (!_compare(k, tmp->key) && !_compare(tmp->key, k))
			return (tmp);
		else if (_compare(k, tmp->key))
			tmp = tmp->left;
		else
			tmp = tmp->right;
	return (NULL);
}

template <class Key, class T, class Compare, class Alloc>
void
ft::map<Key, T, Compare, Alloc>::_insert_node(node * n)
{
	node *		current_node = _root;
	node * *	next_node = NULL;

	if (_root == NULL)
		_root = n;
	while (current_node)
	{
		if (_compare(n->key, current_node->key))
			next_node = &(current_node->left);
		else
			next_node = &(current_node->right);
		if (*next_node == NULL)
		{
			*next_node = n;
			n->parent = current_node;
			return ;
		}
		current_node = *next_node;	
	}
}

template <class Key, class T, class Compare, class Alloc>
void
ft::map<Key, T, Compare, Alloc>::_deallocate_btree(node * & n)
{
	if (n->left)
		_deallocate_btree(n->left);
	if (n->right)
		_deallocate_btree(n->right);
	_node_alloc.destroy(n);
	_node_alloc.deallocate(n, 1);
	n = NULL;
}