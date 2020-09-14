#include "List.hpp"

/* Constructor */
/** default	(1) **/
template <typename T, class Alloc>
ft::List<T, Alloc>::List(const allocator_type & alloc)
									 : _alloc(alloc), _size(0), _head(NULL), _tail(NULL)
{
}

/** fill		(2) **/
template <typename T, class Alloc>
ft::List<T, Alloc>::List(size_type n, const value_type & val,
												const allocator_type & alloc)
					 				 : _alloc(alloc), _size(0), _head(NULL), _tail(NULL)
{
	for (; n; --n)
		push_front(val);
}

/** range		(3) **/

/** copy		(4) **/
template <class T, class Alloc>
ft::List<T, Alloc>::List(List const & other)
{
	_copy(other);
}

/* Node */

template <class T, class Alloc>
typename ft::List<T, Alloc>::node *
ft::List<T, Alloc>::_new_node(const T & v, node * p, node * n)
{
	node * _n = _node_alloc.allocate(1);
	_node_alloc.construct(_n, node(v, p, n));
	return (_n);
}

/* Iterator */
template <class T, class Alloc>
ft::List<T, Alloc>::Iterator::Iterator(node * t)
														 : ft::List<T, Alloc>::Iterator::AIterator(t)
{
}


/* Destructor */
template <class T, class Alloc>
ft::List<T, Alloc>::~List(void)
{
	clear();
}

/* Operator */
template <class T, class Alloc>
ft::List<T, Alloc> &
ft::List<T, Alloc>::operator=(List const & other)
{
	if (this != &other)
		_copy(other);
	return (*this);
}

/* Public functions */
/** Iterator **/
template <class T, class Alloc>
typename ft::List<T, Alloc>::iterator
ft::List<T, Alloc>::begin(void)
{
	return (Iterator(_head));
}

/** Capacity **/
template <class T, class Alloc>
bool
ft::List<T, Alloc>::empty(void) const
{
	return (_head == NULL);
}

template <class T, class Alloc>
typename ft::List<T, Alloc>::size_type
ft::List<T, Alloc>::size(void) const
{
	return (_size);
}

template <class T, class Alloc>
typename ft::List<T, Alloc>::size_type
ft::List<T, Alloc>::max_size(void) const
{
	return (std::numeric_limits<size_type>::max() / sizeof(node));
}

/** Element access **/

/** Modifiers **/

template <class T, class Alloc>
void
ft::List<T, Alloc>::push_front(const value_type & val)
{
	if (empty())
		_head = _tail = _new_node(val, NULL, NULL);
	else
	{
		node * n = _new_node(val, NULL, _head);
		_head = n;
	}
	++_size;
}

template <class T, class Alloc>
void
ft::List<T, Alloc>::pop_front(void)
{
	if (!empty())
	{
		node * d = _head;
		_head = _head->next;
		delete d;
		--_size;
		if (!empty())
			_head->prev = NULL;
	}
}

template <class T, class Alloc>
void
ft::List<T, Alloc>::push_back(const value_type & val)
{
	if (empty())
		_head = _tail = _new_node(val, NULL, NULL);
	else
	{
		node * n = _new_node(val, _tail, NULL);
		_tail->next = n;
		_tail = n;
	}
	++_size;
}

template <class T, class Alloc>
void
ft::List<T, Alloc>::pop_back(void)
{
	if (!empty())
	{
		node * d = _tail;
		_tail = _tail->prev;
		delete d;
		--_size;
		if (!empty())
			_tail->next = NULL;
	}
}

template <class T, class Alloc>
void
ft::List<T, Alloc>::clear(void)
{
	while (!empty())
	{
		_tail = _head;
		_head = _head->next;
		delete _tail;
	}
	_tail = NULL;
	_size = 0;
}

/** Operations **/

/* Private functions */
template <class T, class Alloc>
void
ft::List<T, Alloc>::_copy(List const & other)
{
	(void)other;
}

template <class T, class Alloc>
void
ft::List<T, Alloc>::_debug(void) const
{
	node * tmp = _head;
	std::cout << "Head = " << _head << " Tail = " << _tail << std::endl;
	std::cout << "List: [ ";
	while (tmp != NULL)
	{
		std::cout << tmp->value << " ";
		tmp = tmp->next;
	}
	std::cout << "]" << std::endl;
}