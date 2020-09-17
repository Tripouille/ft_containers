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

/* BaseIterator */
template <class T>
ft::DLNode<T>::BaseIterator::BaseIterator(DLNode<T> * t)
						: _target(t)
{
}

template <class T>
ft::DLNode<T>::BaseIterator::~BaseIterator(void)
{
}


template <class T>
ft::DLNode<T>::BaseIterator::BaseIterator(BaseIterator const & other)
{
	_copy(other);
}

template <class T>
typename ft::DLNode<T>::BaseIterator &
ft::DLNode<T>::BaseIterator::operator=(BaseIterator const & other)
{
	if (this != &other)
		_copy(other);
	return (*this);
}

template <class T>
void
ft::DLNode<T>::BaseIterator::_copy(BaseIterator const & other)
{
	_target = other._target;
}

template <class T>
bool
ft::DLNode<T>::BaseIterator::operator==(BaseIterator const & other) const
{
	return (_target == other._target);
}

template <class T>
bool
ft::DLNode<T>::BaseIterator::operator!=(BaseIterator const & other) const
{
	return (_target != other._target);
}

template <class T>
typename ft::DLNode<T>::BaseIterator &
ft::DLNode<T>::BaseIterator::operator++(void)
{
	_target = _target->next;
	return (*this);
}

template <class T>
typename ft::DLNode<T>::BaseIterator
ft::DLNode<T>::BaseIterator::operator++(int)
{
	BaseIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T>
typename ft::DLNode<T>::BaseIterator &
ft::DLNode<T>::BaseIterator::operator--(void)
{
	_target = _target->prev;
	return (*this);
}

template <class T>
typename ft::DLNode<T>::BaseIterator
ft::DLNode<T>::BaseIterator::operator--(int)
{
	BaseIterator tmp(*this);
	--*this;
	return (tmp);
}

/* Iterator */
template <class T>
ft::DLNode<T>::Iterator::Iterator(DLNode<T> * t)
						: BaseIterator(t)
{
}

template <class T>
ft::DLNode<T>::Iterator::~Iterator(void)
{
}


template <class T>
ft::DLNode<T>::Iterator::Iterator(Iterator const & other)
						 : BaseIterator(other)
{
}

template <class T>
typename ft::DLNode<T>::Iterator &
ft::DLNode<T>::Iterator::operator=(Iterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T>
T &
ft::DLNode<T>::Iterator::operator*(void) const
{
	return (Iterator::_target->value);
}

template <class T>
T *
ft::DLNode<T>::Iterator::operator->(void) const
{
	return (&(Iterator::_target->value));
}

/* CIterator */
template <class T>
ft::DLNode<T>::CIterator::CIterator(DLNode<T> * t)
						: BaseIterator(t)
{
}

template <class T>
ft::DLNode<T>::CIterator::CIterator(Iterator const & it)
						: BaseIterator(it)
{
}

template <class T>
ft::DLNode<T>::CIterator::~CIterator(void)
{
}


template <class T>
ft::DLNode<T>::CIterator::CIterator(CIterator const & other)
						 : BaseIterator(other)
{
}

template <class T>
typename ft::DLNode<T>::CIterator &
ft::DLNode<T>::CIterator::operator=(CIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T>
T const &
ft::DLNode<T>::CIterator::operator*(void) const
{
	return (CIterator::_target->value);
}

template <class T>
T const *
ft::DLNode<T>::CIterator::operator->(void) const
{
	return (&(CIterator::_target->value));
}

/* RIterator */
template <class T>
ft::DLNode<T>::RIterator::RIterator(DLNode<T> * t)
						 : BaseIterator(t)
{
}

template <class T>
ft::DLNode<T>::RIterator::~RIterator(void)
{
}


template <class T>
ft::DLNode<T>::RIterator::RIterator(RIterator const & other)
						: BaseIterator(other)
{
}

template <class T>
typename ft::DLNode<T>::RIterator &
ft::DLNode<T>::RIterator::operator=(RIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
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
	++*this;
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
	--*this;
	return (tmp);
}

template <class T>
T &
ft::DLNode<T>::RIterator::operator*(void) const
{
	return (RIterator::_target->value);
}

template <class T>
T *
ft::DLNode<T>::RIterator::operator->(void) const
{
	return (&(RIterator::_target->value));
}

/* CRIterator */
template <class T>
ft::DLNode<T>::CRIterator::CRIterator(DLNode<T> * t)
						 : BaseIterator(t)
{
}

template <class T>
ft::DLNode<T>::CRIterator::~CRIterator(void)
{
}


template <class T>
ft::DLNode<T>::CRIterator::CRIterator(CRIterator const & other)
						: BaseIterator(other)
{
}

template <class T>
typename ft::DLNode<T>::CRIterator &
ft::DLNode<T>::CRIterator::operator=(CRIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T>
typename ft::DLNode<T>::CRIterator &
ft::DLNode<T>::CRIterator::operator++(void)
{
	CRIterator::_target = CRIterator::_target->prev;
	return (*this);
}

template <class T>
typename ft::DLNode<T>::CRIterator
ft::DLNode<T>::CRIterator::operator++(int)
{
	CRIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T>
typename ft::DLNode<T>::CRIterator &
ft::DLNode<T>::CRIterator::operator--(void)
{
	CRIterator::_target = CRIterator::_target->next;
	return (*this);
}

template <class T>
typename ft::DLNode<T>::CRIterator
ft::DLNode<T>::CRIterator::operator--(int)
{
	CRIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T>
T const &
ft::DLNode<T>::CRIterator::operator*(void) const
{
	return (CRIterator::_target->value);
}

template <class T>
T const *
ft::DLNode<T>::CRIterator::operator->(void) const
{
	return (&(CRIterator::_target->value));
}