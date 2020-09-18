#include "list.hpp"

/* Constructor */
/** default	(1) **/
template <typename T, class Alloc>
ft::list<T, Alloc>::list(const allocator_type & alloc)
				: _alloc(alloc), _size(0), _end(_node_alloc.allocate(1))
{
	_head = _tail = _end;
	_actualize_end();
}

/** fill		(2) **/
template <typename T, class Alloc>
ft::list<T, Alloc>::list(size_type n, const value_type & val,
										const allocator_type & alloc)
				   : _alloc(alloc), _size(0), _end(_node_alloc.allocate(1))
{
	_head = _tail = _end;
	_actualize_end();
	_fill_with_value(n, val);
}

/** range		(3) **/
template <typename T, class Alloc>
template <class InputIterator>
ft::list<T, Alloc>::list(InputIterator first, InputIterator last,
												const allocator_type & alloc)
				  : _alloc(alloc), _size(0), _end(_node_alloc.allocate(1))
{
	_head = _tail = _end;
	_actualize_end();
	_fill_list_dispatch(first, last, typename is_integer<InputIterator>::type());
}

/** copy		(4) **/
template <class T, class Alloc>
ft::list<T, Alloc>::list(list const & other)
				   : _alloc(other._alloc), _size(0), _end(_node_alloc.allocate(1))
{
	_head = _tail = _end;
	_actualize_end();
	_copy(other);
}

/* Destructor */
template <class T, class Alloc>
ft::list<T, Alloc>::~list(void)
{
	clear();
	_node_alloc.deallocate(_end, 1);
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
	return (const_iterator(_head));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator
ft::list<T, Alloc>::end(void)
{
	return (iterator(_end));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_iterator
ft::list<T, Alloc>::end(void) const
{
	return (iterator(_end));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::reverse_iterator
ft::list<T, Alloc>::rbegin(void)
{
	return (reverse_iterator(_tail));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reverse_iterator
ft::list<T, Alloc>::rbegin(void) const
{
	return (reverse_iterator(_tail));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::reverse_iterator
ft::list<T, Alloc>::rend(void)
{
	return (reverse_iterator(_end));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reverse_iterator
ft::list<T, Alloc>::rend(void) const
{
	return (reverse_iterator(_end));
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
	if (empty())
		return (_end->value);
	return (_head->value);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reference
ft::list<T, Alloc>::front(void) const
{
	if (empty())
		return (_end->value);
	return (_head->value);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::reference
ft::list<T, Alloc>::back(void)
{
	if (empty())
		return (_end->value);
	return (_tail->value);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reference
ft::list<T, Alloc>::back(void) const
{
	if (empty())
		return (_end->value);
	return (_tail->value);
}

/** Modifiers **/

/** range	(1) **/
template <class T, class Alloc>
template <class InputIterator>
void
ft::list<T, Alloc>::assign(InputIterator first, InputIterator last)
{
	clear();
	_fill_list_dispatch(first, last, typename is_integer<InputIterator>::type());
}

/** fill	(2) **/
template <class T, class Alloc>
void
ft::list<T, Alloc>::assign(size_type n, const value_type & val)
{
	clear();
	_fill_with_value(n, val);
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
		_head->prev = n;
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

/*** single element (1) ***/
template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator
ft::list<T, Alloc>::insert(iterator position, const value_type & val)
{
	(void)val;
	return (position);
}

/*** fill (2) ***/
template <class T, class Alloc>
void
ft::list<T, Alloc>::insert(iterator position, size_type n, const value_type & val)
{
	(void)val;
	(void)n;
	(void)position;
}

/*** range (3) ***/
template <class T, class Alloc>
template <class InputIterator>
typename ft::list<T, Alloc>::iterator
ft::list<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
{
	(void)first;
	(void)last;
	return (position);
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
		std::swap(_end, x._end);
	}
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::clear(void)
{
	while (_head != _end)
	{
		_tail = _head;
		_head = _head->next;
		delete _tail;
	}
	_tail = _end;
	_size = 0;
	_actualize_end();
}

/** Operations **/
/*** entire list (1) ***/ template <class T, class Alloc>
void
ft::list<T, Alloc>::splice(iterator position, list & x)
{
	if (x.empty())
		return ;
	if (position._target == _head)
		_head = x._head;
	if (position._target == _tail)
		_tail = x._tail;
	x._head->prev = position._target->prev;
	x._tail->next = position._target;
	position._target->prev->next = x._head;
	position._target->prev = x._tail;
	_size += x._size;
	x._size = 0;
	x._head = x._tail = x._end;
}

/* Private functions */
template <class T, class Alloc>
void
ft::list<T, Alloc>::_copy(list const & other)
{
	_alloc = other._alloc;
	_node_alloc = other._node_alloc;

	DLNode<T> * tmp = other._head;
	while (tmp != other._end)
	{
		push_back(tmp->value);
		tmp = tmp->next;
	}
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

template <typename T, class Alloc>
void ft::list<T, Alloc>::_fill_with_value(size_type n, T const & val)
{
	for (; n; --n)
		push_front(val);
}

template <typename T, class Alloc>
template <class InputIterator>
void ft::list<T, Alloc>::_fill_from_iterators(InputIterator & first, InputIterator & last)
{
	while (first != last)
	{
		push_back(*first);
		++first;
	}
}

template <typename T, class Alloc>
template <class Integer>
void ft::list<T, Alloc>::_fill_list_dispatch(Integer & n, Integer & val, INT_TYPE)
{
	_fill_with_value(static_cast<size_type>(n), val);
}

template <typename T, class Alloc>
template <class InputIterator>
void ft::list<T, Alloc>::_fill_list_dispatch(InputIterator & first, InputIterator & last, NO_INT_TYPE)
{
	_fill_from_iterators(first, last);
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::_actualize_end(void)
{
	_end->next = _head;
	_end->prev = _tail; 
	if (!empty())
	{
		_head->prev = _end;
		_tail->next = _end;
	}
	else
		_head = _tail = _end;
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::_debug(void) const
{
	DLNode<T> * tmp = _head;
	std::cout << "Head = " << _head << " Tail = " << _tail << std::endl;
	std::cout << "List: [ ";
	int i = 0;
	while (tmp != _end && i++ < 100)
	{
		std::cout << tmp->value << " ";
		tmp = tmp->next;
	}
	std::cout << "]" << std::endl;
}