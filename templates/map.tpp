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


/* Operator */


/* Public functions */
/** Iterators **/


/** Capacity **/


/** Element access **/
template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::mapped_type & 
ft::map<Key, T, Compare, Alloc>::operator[](const key_type & k)
{
	node * newNode = _node_alloc.allocate(1);
	_node_alloc.construct(newNode, node(k, mapped_type()));
	if (_root == NULL)
		_root = newNode;
	return (_root->value);
}

/** Modifiers **/


/** Observers **/


/** Operations **/


/** Allocator **/


/** Private functions **/