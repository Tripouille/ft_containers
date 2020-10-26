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
template <class Key, class T, class Compare, class Alloc>
template <class InputIterator>
ft::map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last,
									const key_compare & comp , const allocator_type & alloc)
								 : _compare(comp), _alloc(alloc), _root(NULL), _size(0)
{
	for (; first != last; ++first)
		_try_insert_node(first->first, first->second);
}

/** copy (3) **/
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::map(const map & x)
								: _compare(x._compare), _alloc(x._alloc),
								  _root(NULL), _size(x._size)
{
	const_iterator begin = x.begin();
	const_iterator end = x.end();
	for (; begin != end; ++begin)
		_insert_node(_create_node(begin->first, begin->second));
}

/* Destructor */
template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::~map(void)
{
	_deallocate_btree(_root);
	_size = 0;
}

/* Operator */
/** copy (1) **/
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc> &
ft::map<Key, T, Compare, Alloc>::operator=(const map & x)
{
	if (this != &x)
	{
		_deallocate_btree(_root);
		_size = x._size;
		_compare = x._compare;
		const_iterator begin = x.begin();
		const_iterator end = x.end();
		for (; begin != end; ++begin)
			_insert_node(_create_node(begin->first, begin->second));
	}
	return (*this);
}

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
typename ft::map<Key, T, Compare, Alloc>::const_iterator
ft::map<Key, T, Compare, Alloc>::begin(void) const
{
	node * tmp = _root;
	if (tmp)
		while (tmp->left)
			tmp = tmp->left;
	return (const_iterator(tmp, &_root));	
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator
ft::map<Key, T, Compare, Alloc>::end(void)
{
	return (iterator(NULL, &_root));
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_iterator
ft::map<Key, T, Compare, Alloc>::end(void) const
{
	return (const_iterator(NULL, &_root));
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::reverse_iterator
ft::map<Key, T, Compare, Alloc>::rbegin(void)
{
	node * tmp = _root;
	if (tmp)
		while (tmp->right)
			tmp = tmp->right;
	return (reverse_iterator(tmp, &_root));
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator
ft::map<Key, T, Compare, Alloc>::rbegin(void) const
{
	node * tmp = _root;
	if (tmp)
		while (tmp->right)
			tmp = tmp->right;
	return (const_reverse_iterator(tmp, &_root));
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::reverse_iterator
ft::map<Key, T, Compare, Alloc>::rend(void)
{
	return (reverse_iterator(NULL, &_root));
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator
ft::map<Key, T, Compare, Alloc>::rend(void) const
{
	return (const_reverse_iterator(NULL, &_root));
}

/** Capacity **/
template <class Key, class T, class Compare, class Alloc>
bool
ft::map<Key, T, Compare, Alloc>::empty(void) const
{
	return (_size == 0);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type
ft::map<Key, T, Compare, Alloc>::size(void) const
{
	return (_size);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type
ft::map<Key, T, Compare, Alloc>::max_size(void) const
{
	return (_node_alloc.max_size());
}

/** Element access **/
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::mapped_type & 
ft::map<Key, T, Compare, Alloc>::operator[](const key_type & k)
{
	return (_try_insert_node(k, mapped_type()).first->pair.second);
}

/** Modifiers **/
/** single element (1) **/
template <class Key, class T, class Compare, class Alloc>
std::pair<typename ft::map<Key, T, Compare, Alloc>::iterator, bool>
ft::map<Key, T, Compare, Alloc>::insert(const value_type& val)
{
	std::pair<node *, bool> infos = _try_insert_node(val.first, val.second);
	return (std::pair<iterator, bool>(iterator(infos.first, &_root),
										infos.second));
}


template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator
ft::map<Key, T, Compare, Alloc>::insert(iterator position, const value_type & val)
{
	node * * node_ptr_ptr = NULL;
	if (_compare(position._node->pair.first, val.first)
	&& (!position._node->parent || _compare(val.first, position._node->parent->pair.first)))
	{
		node_ptr_ptr = &position._node->right;
		while (*node_ptr_ptr != NULL)
			if (_compare(val.first, (*node_ptr_ptr)->pair.first))
				node_ptr_ptr = &(*node_ptr_ptr)->left;
			else
				node_ptr_ptr = &(*node_ptr_ptr)->right;		
		++_size;
		return (iterator((*node_ptr_ptr = _create_node(val.first, val.second))
							, &_root));
	}
	return (insert(val).first);
}


/** Observers **/


/** Operations **/

/** Allocator **/


/** Private functions **/
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::node *
ft::map<Key, T, Compare, Alloc>::_find_node(const key_type & k) const
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
std::pair<typename ft::map<Key, T, Compare, Alloc>::node *, bool>
ft::map<Key, T, Compare, Alloc>::_try_insert_node(const key_type & k,
												const mapped_type & v)
{
	node * n = _find_node(k);
	bool need_to_create = false;

	if (n == NULL)
	{
		n = _create_node(k, v);
		++_size;
		_insert_node(n);
		need_to_create = true;
	}
	return (std::pair<node *, bool>(n, need_to_create));
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

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::node * 
ft::map<Key, T, Compare, Alloc>::_create_node(const key_type & k,
											const mapped_type & v)
{
	node * n = _node_alloc.allocate(1);
	_node_alloc.construct(n, node(k, v));
	return (n);
}


/* Debug Functions */
template <class Key, class T, class Compare, class Alloc>
void
ft::map<Key, T, Compare, Alloc>::_print_btree(node * n) const
{
	if (n == NULL)
		return ;
	_print_btree(n->left);
	std::cout << "(" << n->pair.first << " : " << n->pair.second << ") ";
	_print_btree(n->right);
}

template <class Key, class T, class Compare, class Alloc>
void
ft::map<Key, T, Compare, Alloc>::_debug(void) const
{
	std::cout << "#[Actual Tree] : ";
	_print_btree(_root);
	std::cout << std::endl;
}