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
	DLNode<T> * n = _new_node(val, position._target->prev, position._target);
	position._target->prev->next = n;
	position._target->prev = n;
	_actualize_head_tail();
	++_size;
	return (iterator(n));
}

/*** fill (2) ***/
template <class T, class Alloc>
void
ft::list<T, Alloc>::insert(iterator position, size_type n, const value_type & val)
{
	for (; n; --n)
		insert(position, val);
}

/*** range (3) ***/
template <class T, class Alloc>
template <class InputIterator>
void
ft::list<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
{
	list tmp(first, last);
	splice(position, tmp);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator
ft::list<T, Alloc>::erase(iterator position)
{
	iterator ret(position._target->next);
	
	position._target->prev->next = position._target->next;
	position._target->next->prev = position._target->prev;
	_actualize_head_tail();

	delete position._target;
	--_size;

	return (ret);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator
ft::list<T, Alloc>::erase(iterator first, iterator last)
{
	first._target->prev->next = last._target;
	last._target->prev = first._target->prev;
	_actualize_head_tail();

	DLNode<T> * to_del;
	while (first != last)
	{
		to_del = first._target;
		++first;
		delete to_del;
		--_size;
	}
	return (last);
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
ft::list<T, Alloc>::resize(size_type n, value_type val)
{
	while (n > _size)
		push_back(val);
	while (n < _size)
		pop_back();
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
/*** entire list (1) ***/
template <class T, class Alloc>
void
ft::list<T, Alloc>::splice(iterator position, list & x)
{
	if (x.empty())
		return ;
	x._head->prev = position._target->prev;
	x._tail->next = position._target;
	position._target->prev->next = x._head;
	position._target->prev = x._tail;
	_size += x._size;
	_actualize_head_tail();
	x._size = 0;
	x._head = x._tail = x._end;
}

/*** single element (2)	***/
template <class T, class Alloc>
void
ft::list<T, Alloc>::splice(iterator position, list & x, iterator i)
{
	if (x.empty() || i._target == x._end)
		return ;
	i._target->next->prev = i._target->prev;
	i._target->prev->next = i._target->next;

	i._target->prev = position._target->prev;
	i._target->next = position._target;

	position._target->prev->next = i._target;
	position._target->prev = i._target;

	++_size;
	--x._size;

	_actualize_head_tail();
	x._actualize_head_tail();
}

/*** element range (3) ***/
template <class T, class Alloc>
void
ft::list<T, Alloc>::splice(iterator position, list & x, iterator first, iterator last)
{
	unsigned long size = static_cast<unsigned long>(std::distance(first, last));

	if (x.empty() || size == 0)
		return ;
	first._target->prev->next = last._target;
	DLNode<T> * before_last = last._target->prev;
	last._target->prev = first._target->prev;

	position._target->prev->next = first._target;
	first._target->prev = position._target->prev;

	before_last->next = position._target;
	position._target->prev = before_last;

	x._size -= size;
	_size += size;

	_actualize_head_tail();
	x._actualize_head_tail();
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::remove(const value_type & val)
{
	iterator it = begin();
	iterator ite = end();

	while (it != ite)
	{
		if (*it == val)
			it = erase(it);
		else
			++it;
	}
}

template <class T, class Alloc>
template <class Predicate>
void
ft::list<T, Alloc>::remove_if(Predicate pred)
{
	iterator it = begin();
	iterator ite = end();

	while (it != ite)
	{
		if (pred(*it))
			it = erase(it);
		else
			++it;
	}
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::unique(void)
{
	unique(std::equal_to<T>());
}


template <class T, class Alloc>
template <class BinaryPredicate>
void
ft::list<T, Alloc>::unique(BinaryPredicate binary_pred)
{
	iterator it = begin();
	iterator it2 = ++begin();
	iterator ite = end();

	while (it2 != ite)
	{
		if (binary_pred(*it, *it2))
			it2 = erase(it2);
		else
		{
			++it;
			++it2;
		}
	}
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::merge(list & x)
{
	merge(x, std::less<T>());
}


template <class T, class Alloc>
template <class Compare>
void
ft::list<T, Alloc>::merge(list & x, Compare comp)
{
	if (&x == this)
		return ;
	
	iterator x_it_first = x.begin();
	iterator x_ite = x.end();
	iterator it = begin();
	iterator ite = end();
	iterator tmp;
	while (x_it_first != x_ite)
	{
		while (it != ite && !comp(*x_it_first, *it))
			++it;
		iterator x_it_last = ++iterator(x_it_first);
		while (x_it_last != x_ite && (it == ite || !comp(*it, *x_it_last)))
			++x_it_last;
		splice(it, x, x_it_first, x_it_last);
		x_it_first = x_it_last;
	}
}

/*** (1) ***/
template <class T, class Alloc>
void
ft::list<T, Alloc>::sort(void)
{
	sort(std::less<T>());
}

/*** (2) ***/
template <class T, class Alloc>
template <class Compare>
void
ft::list<T, Alloc>::sort(Compare comp)
{
	list<T, Alloc> tmp, result;
	iterator tmp_ite(tmp.end());

	while (!empty())
	{
		tmp.splice(tmp_ite, *this, --this->end());
		result.merge(tmp, comp);
	}
	splice(end(), result);	
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::reverse(void)
{
	while (_head != _end)
	{
		std::swap(_head->prev, _head->next);
		_head = _head->prev;
	}
	std::swap(_end->prev, _end->next);
	_actualize_head_tail();
}

/** Observers **/
template <class T, class Alloc>
typename ft::list<T, Alloc>::allocator_type
ft::list<T, Alloc>::get_allocator(void) const
{
	return (_alloc);
}


/** Private functions **/
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
void ft::list<T, Alloc>::_fill_with_value(size_type n, value_type const & val)
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
ft::list<T, Alloc>::_actualize_head_tail(void)
{
	_head = _end->next;
	_tail = _end->prev;
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::_debug(void) const
{
	DLNode<T> * tmp = _head;
	std::cout << "Head = " << _head << " Tail = " << _tail << " End = " << _end << std::endl;
	std::cout << "List: [ ";
	int i = 0;
	while (tmp != _end && i++ < 100)
	{
		std::cout << tmp->value << " ";
		tmp = tmp->next;
	}
	std::cout << "]" << std::endl;
}

template <class T, class Alloc>
void
ft::list<T, Alloc>::_swap(const_iterator a, const_iterator b)
{
	if (a == b)
		return ;
	std::swap(a._target->prev, b._target->prev);
	std::swap(a._target->next, b._target->next);
	a._target->prev->next = a._target;
	a._target->next->prev = a._target;
	b._target->prev->next = b._target;
	b._target->next->prev = b._target;
	_actualize_head_tail();
}

/** Non-member function overloads **/

template <class T, class Alloc>
bool
ft::operator==(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	
	typename ft::list<T, Alloc>::iterator lhs_it = lhs.begin();
	typename ft::list<T, Alloc>::iterator lhs_ite = lhs.end();
	typename ft::list<T, Alloc>::iterator rhs_it = rhs.begin();
	while (lhs_it != lhs_ite)
	{
		if (*lhs_it != *rhs_it)
			return (false);
		++lhs_it;
		++rhs_it;
	}
	return (true);
}

template <class T, class Alloc>
bool
ft::operator!=(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
void
ft::swap(ft::list<T, Alloc> & x, ft::list<T, Alloc> & y)
{
	x.swap(y);
}
