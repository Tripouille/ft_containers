#include "list.hpp"

/* Constructor */
/** default	(1) **/
template <typename T, class Alloc>
ft::list<T, Alloc>::list(const allocator_type & alloc)
									 : _alloc(alloc), _size(0), _head(&_end), _tail(&_end)
{
}

/** fill		(2) **/
template <typename T, class Alloc>
ft::list<T, Alloc>::list(size_type n, const value_type & val,
												const allocator_type & alloc)
					 				 : _alloc(alloc), _size(0), _head(&_end), _tail(&_end)
{
	for (; n; --n)
		push_front(val);
}

/** range		(3) **/

/** copy		(4) **/
template <class T, class Alloc>
ft::list<T, Alloc>::list(list const & other) : _alloc(other._alloc), _size(0), _head(&_end), _tail(&_end)
{
	_copy(other);
}

/* Destructor */
template <class T, class Alloc>
ft::list<T, Alloc>::~list(void)
{
	clear();
}

/* Operator */
template <class T, class Alloc>
ft::list<T, Alloc> &
ft::list<T, Alloc>::operator=(list const & other)
{
	if (this != &other)
	{
		clear();
		_copy(other);
	}
	return (*this);
}

/* Public functions */
/** Iterator **/
template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator
ft::list<T, Alloc>::begin(void)
{
	return (iterator(_head));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_iterator
ft::list<T, Alloc>::begin(void) const
{
	return (iterator(_head));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator
ft::list<T, Alloc>::end(void)
{
	return (iterator(&_end));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_iterator
ft::list<T, Alloc>::end(void) const
{
	return (iterator(&_end));
}

/** Capacity **/
template <class T, class Alloc>
bool
ft::list<T, Alloc>::empty(void) const
{
	return (_size == 0);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::size_type
ft::list<T, Alloc>::size(void) const
{
	return (_size);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::size_type
ft::list<T, Alloc>::max_size(void) const
{
	return (std::numeric_limits<size_type>::max() / sizeof(DLNode<T>));
}

/** Element access **/

template <class T, class Alloc>
typename ft::list<T, Alloc>::reference
ft::list<T, Alloc>::front(void)
{
	static	value_type default_value;
	if (empty())
		return (default_value);
	return (_head->value);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reference
ft::list<T, Alloc>::front(void) const
{
	static	value_type default_value;
	if (empty())
		return (default_value);
	return (_head->value);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::reference
ft::list<T, Alloc>::back(void)
{
	static	value_type default_value;
	if (empty())
		return (default_value);
	return (_tail->value);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reference
ft::list<T, Alloc>::back(void) const
{
	static	value_type default_value;
	if (empty())
		return (default_value);
	return (_tail->value);
}

/** Modifiers **/

/** fill	(2) **/
template <class T, class Alloc>
void
ft::list<T, Alloc>::assign(size_type n, const value_type & val)
{
	clear();
	for (; n; --n)
		push_back(val);
	_actualize_end();
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::push_front(const value_type & val)
{
	if (empty())
		_head = _tail = _new_node(val, NULL, NULL);
	else
	{
		DLNode<T> * n = _new_node(val, NULL, _head);
		_head = n;
	}
	++_size;
	_actualize_end();
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::pop_front(void)
{
	if (!empty())
	{
		DLNode<T> * d = _head;
		_head = _head->next;
		delete d;
		--_size;
		_actualize_end();
	}
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::push_back(const value_type & val)
{
	if (empty())
		_head = _tail = _new_node(val, NULL, NULL);
	else
	{
		DLNode<T> * n = _new_node(val, _tail, NULL);
		_tail->next = n;
		_tail = n;
	}
	++_size;
	_actualize_end();
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::pop_back(void)
{
	if (!empty())
	{
		DLNode<T> * d = _tail;
		_tail = _tail->prev;
		delete d;
		--_size;
		_actualize_end();
	}
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::swap(list & x)
{
	if (this != &x)
	{
		std::swap(_alloc, x._alloc);
		std::swap(_node_alloc, x._node_alloc);
		std::swap(_size, x._size);
		std::swap(_head, x._head);
		std::swap(_tail, x._tail);
		_actualize_end();
		x._actualize_end();
	}
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::clear(void)
{
	while (_head != &_end)
	{
		_tail = _head;
		_head = _head->next;
		delete _tail;
	}
	_tail = &_end;
	_size = 0;
	_actualize_end();
}

/** Operations **/

/* Private functions */
template <class T, class Alloc>
void
ft::list<T, Alloc>::_copy(list const & other)
{
	_alloc = other._alloc;
	_node_alloc = other._node_alloc;

	DLNode<T> * tmp = other._head;
	while (tmp != &other._end)
	{
		push_back(tmp->value);
		tmp = tmp->next;
	}
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::_debug(void) const
{
	DLNode<T> * tmp = _head;
	std::cout << "Head = " << _head << " Tail = " << _tail << std::endl;
	std::cout << "list: [ ";
	while (tmp != &_end)
	{
		std::cout << tmp->value << " ";
		tmp = tmp->next;
	}
	std::cout << "]" << std::endl;
}

template <class T, class Alloc>
typename ft::DLNode<T> *
ft::list<T, Alloc>::_new_node(const T & v, DLNode<T> * p, DLNode<T> * n)
{
	DLNode<T> * _n = _node_alloc.allocate(1);
	try
	{
		_node_alloc.construct(_n, DLNode<T>(v, p, n));
	}
	catch(std::exception & e)
	{
		_node_alloc.deallocate(_n, 1);
		throw;
	}
	return (_n);
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::_actualize_end(void)
{
	_end.next = _head;
	_end.prev = _tail;
	if (!empty())
	{
		_head->prev = &_end;
		_tail->next = &_end;
	}
	else
		_head = _tail = &_end;
}
