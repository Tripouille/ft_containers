#include "DLNode.hpp" 

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
						: ft::DLNode<T>::Iterator::AIterator(t)
{
}

template <class T>
ft::DLNode<T>::Iterator::~Iterator(void)
{
}


template <class T>
ft::DLNode<T>::Iterator::Iterator(Iterator const & other)
						: ft::DLNode<T>::Iterator::AIterator(other)
{
}

template <class T>
typename ft::DLNode<T>::Iterator &
ft::DLNode<T>::Iterator::operator=(DLNode const & other)
{
	if (this != &other)
		ft::DLNode<T>::Iterator::AIterator::_copy(other);
	return (*this);
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
T &
ft::DLNode<T>::Iterator::operator->(void)
{
	return (*Iterator::_target->value);

}

template <class T>
T &
ft::DLNode<T>::Iterator::operator->(void) const
{
	return (*Iterator::_target->value);
}
