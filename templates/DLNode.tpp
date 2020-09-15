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
