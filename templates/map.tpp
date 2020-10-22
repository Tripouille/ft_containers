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
	_debug();
	_deallocate_btree(_root);
	_size = 0;
}

/* Operator */


/* Public functions */
/** Iterators **/
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator
ft::map<Key, T, Compare, Alloc>::begin(void)
{
	node * tmp = _root;
	if (tmp)
		while (tmp->left)
			tmp = tmp->left;
	return (iterator(tmp, &_root));	
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator
ft::map<Key, T, Compare, Alloc>::end(void)
{
	return (iterator(NULL, &_root));
}

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
		++_size;
	}
	return (n->pair.second);
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
		if (!_compare(k, tmp->pair.first) && !_compare(tmp->pair.first, k))
			return (tmp);
		else if (_compare(k, tmp->pair.first))
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
		if (_compare(n->pair.first, current_node->pair.first))
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
	if (n != NULL)
	{
		if (n->left)
			_deallocate_btree(n->left);
		if (n->right)
			_deallocate_btree(n->right);
		_node_alloc.destroy(n);
		_node_alloc.deallocate(n, 1);
		n = NULL;
	}
}


/* Debug Functions */
template <class Key, class T, class Compare, class Alloc>
void
ft::map<Key, T, Compare, Alloc>::_print_btree(node * n)
{
	if (n == NULL)
		return ;
	_print_btree(n->left);
	std::cout << "(" << n->pair.first << " : " << n->pair.second << ") ";
	_print_btree(n->right);
}

template <class Key, class T, class Compare, class Alloc>
void
ft::map<Key, T, Compare, Alloc>::_debug(void)
{
	std::cout << "#[Actual Tree] : ";
	_print_btree(_root);
	std::cout << std::endl;
}