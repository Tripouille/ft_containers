#include "DLNode.hpp"

template <class T>
ft::DLNode<T>::DLNode(void) : prev(NULL), next(NULL)
{
}

template <class T>
ft::DLNode<T>::DLNode(const T & v, DLNode * p, DLNode * n)
		  	  : value(v), prev(p), next(n)
{
}

template <class T>
ft::DLNode<T>::~DLNode(void)
{
}

template <class T>
ft::DLNode<T>::DLNode(DLNode const & other)
			  : value(other.value)
{
	DLNode<T>::_copy(other);
}

template <class T>
ft::DLNode<T> &
ft::DLNode<T>::operator=(DLNode const & other)
{
	if (this != &other)
		DLNode<T>::_copy(other);
	return (*this);
}

template <class T>
void
ft::DLNode<T>::_copy(DLNode const & other)
{
	value = other.value;
	prev = other.prev;
	next = other.next;
}

/* Iterator */
template <class T>
ft::DLNode<T>::Iterator::Iterator(DLNode<T> * t)
						: _target(t)
{
}

template <class T>
ft::DLNode<T>::Iterator::~Iterator(void)
{
}


template <class T>
ft::DLNode<T>::Iterator::Iterator(Iterator const & other)
{
	_copy(other);
}

template <class T>
typename ft::DLNode<T>::Iterator &
ft::DLNode<T>::Iterator::operator=(Iterator const & other)
{
	if (this != &other)
		_copy(other);
	return (*this);
}

template <class T>
void
ft::DLNode<T>::Iterator::_copy(Iterator const & other)
{
	_target = other._target;
}

template <class T>
bool
ft::DLNode<T>::Iterator::operator==(Iterator const & other) const
{
	return (_target == other._target);
}

template <class T>
bool
ft::DLNode<T>::Iterator::operator!=(Iterator const & other) const
{
	return (_target != other._target);
}

template <class T>
typename ft::DLNode<T>::Iterator &
ft::DLNode<T>::Iterator::operator++(void)
{
	Iterator::_target = Iterator::_target->next;
	return (*this);
}

template <class T>
typename ft::DLNode<T>::Iterator
ft::DLNode<T>::Iterator::operator++(int)
{
	Iterator tmp(*this);
	Iterator::_target = Iterator::_target->next;
	return (tmp);
}

template <class T>
typename ft::DLNode<T>::Iterator &
ft::DLNode<T>::Iterator::operator--(void)
{
	Iterator::_target = Iterator::_target->prev;
	return (*this);
}

template <class T>
typename ft::DLNode<T>::Iterator
ft::DLNode<T>::Iterator::operator--(int)
{
	Iterator tmp(*this);
	Iterator::_target = Iterator::_target->prev;
	return (tmp);
}

template <class T>
T &
ft::DLNode<T>::Iterator::operator*(void)
{
	return (Iterator::_target->value);
}

template <class T>
T &
ft::DLNode<T>::Iterator::operator*(void) const
{
	return (Iterator::_target->value);
}

template <class T>
T *
ft::DLNode<T>::Iterator::operator->(void)
{
	return (&(Iterator::_target->value));
}

template <class T>
T *
ft::DLNode<T>::Iterator::operator->(void) const
{
	return (&(Iterator::_target->value));
}

/* RIterator */
template <class T>
ft::DLNode<T>::RIterator::RIterator(DLNode<T> * t)
						 : iterator(t)
{
}

template <class T>
ft::DLNode<T>::RIterator::~RIterator(void)
{
}


template <class T>
ft::DLNode<T>::RIterator::RIterator(RIterator const & other)
						: iterator(other)
{
}

template <class T>
typename ft::DLNode<T>::RIterator &
ft::DLNode<T>::RIterator::operator=(RIterator const & other)
{
	if (this != &other)
		iterator::operator=(other);
	return (*this);
}

template <class T>
typename ft::DLNode<T>::RIterator &
ft::DLNode<T>::RIterator::operator++(void)
{
	RIterator::_target = RIterator::_target->prev;
	return (*this);
}

template <class T>
typename ft::DLNode<T>::RIterator
ft::DLNode<T>::RIterator::operator++(int)
{
	RIterator tmp(*this);
	RIterator::_target = RIterator::_target->prev;
	return (tmp);
}

template <class T>
typename ft::DLNode<T>::RIterator &
ft::DLNode<T>::RIterator::operator--(void)
{
	RIterator::_target = RIterator::_target->next;
	return (*this);
}

template <class T>
typename ft::DLNode<T>::RIterator
ft::DLNode<T>::RIterator::operator--(int)
{
	RIterator tmp(*this);
	RIterator::_target = RIterator::_target->next;
	return (tmp);
}