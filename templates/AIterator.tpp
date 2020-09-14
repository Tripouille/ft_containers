#include "AIterator.hpp" 

template <class T>
ft::AIterator<T>::AIterator(T * t)
				 : _target(t)
{
}

template <class T>
ft::AIterator<T>::~AIterator(void)
{
}

template <class T>
ft::AIterator<T>::AIterator(AIterator const & other)
{
	ft::AIterator<T>::_copy(other);
}

template <class T>
ft::AIterator<T> &
ft::AIterator<T>::operator=(AIterator const & other)
{
	if (this != &other)
		ft::AIterator<T>::_copy(other);
	return (*this);
}

template <class T>
bool
ft::AIterator<T>::operator==(AIterator const & other)
{
	return (_target == other._target);
}

template <class T>
void
ft::AIterator<T>::_copy(AIterator const & other)
{
	_target = other._target;
}
