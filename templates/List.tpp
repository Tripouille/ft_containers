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
ft::List<T, Alloc>::List(List const & other) : _alloc(other._alloc), _size(0), _head(NULL), _tail(NULL)
{
	_copy(other);
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
	{
		clear();
		_copy(other);
	}
	return (*this);
}

/* Public functions */
/** Iterator **/
template <class T, class Alloc>
typename ft::List<T, Alloc>::iterator
ft::List<T, Alloc>::begin(void)
{
	return (iterator(_head));
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
	return (std::numeric_limits<size_type>::max() / sizeof(DLNode<T>));
}

/** Element access **/

template <class T, class Alloc>
typename ft::List<T, Alloc>::reference
ft::List<T, Alloc>::front(void)
{
	static	value_type default_value;
	if (empty())
		return (default_value);
	return (_head->value);
}

template <class T, class Alloc>
typename ft::List<T, Alloc>::const_reference
ft::List<T, Alloc>::front(void) const
{
	static	value_type default_value;
	if (empty())
		return (default_value);
	return (_head->value);
}

template <class T, class Alloc>
typename ft::List<T, Alloc>::reference
ft::List<T, Alloc>::back(void)
{
	static	value_type default_value;
	if (empty())
		return (default_value);
	return (_tail->value);
}

template <class T, class Alloc>
typename ft::List<T, Alloc>::const_reference
ft::List<T, Alloc>::back(void) const
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
ft::List<T, Alloc>::assign(size_type n, const value_type & val)
{
	clear();
	for (; n; --n)
		push_back(val);
}

template <class T, class Alloc>
void
ft::List<T, Alloc>::push_front(const value_type & val)
{
	if (empty())
		_head = _tail = _new_node(val, NULL, NULL);
	else
	{
		DLNode<T> * n = _new_node(val, NULL, _head);
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
		DLNode<T> * d = _head;
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
		DLNode<T> * n = _new_node(val, _tail, NULL);
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
		DLNode<T> * d = _tail;
		_tail = _tail->prev;
		delete d;
		--_size;
		if (!empty())
			_tail->next = NULL;
	}
}

template <class T, class Alloc>
void
ft::List<T, Alloc>::swap(List & x)
{
	std::swap(_size, x._size);
	std::swap(_head, x._head);
	std::swap(_tail, x._tail);
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
	this->_alloc = other._alloc;
	this->_node_alloc = other._node_alloc;

	DLNode<T> * tmp = other._head;
	while (tmp != NULL)
	{
		this->push_back(tmp->value);
		tmp = tmp->next;
	}
}

template <class T, class Alloc>
void
ft::List<T, Alloc>::_debug(void) const
{
	DLNode<T> * tmp = _head;
	std::cout << "Head = " << _head << " Tail = " << _tail << std::endl;
	std::cout << "List: [ ";
	while (tmp != NULL)
	{
		std::cout << tmp->value << " ";
		tmp = tmp->next;
	}
	std::cout << "]" << std::endl;
}

template <class T, class Alloc>
typename ft::DLNode<T> *
ft::List<T, Alloc>::_new_node(const T & v, DLNode<T> * p, DLNode<T> * n)
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
