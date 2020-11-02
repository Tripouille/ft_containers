#include "DLNode.hpp"

template <class T, class Alloc>
ft::DLNode<T, Alloc>::DLNode(void) : prev(NULL), next(NULL)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::DLNode(const T & v, DLNode * p, DLNode * n)
		  	  : value(v), prev(p), next(n)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::~DLNode(void)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::DLNode(DLNode const & other)
			  : value(other.value)
{
	DLNode<T, Alloc>::_copy(other);
}

template <class T, class Alloc>
ft::DLNode<T, Alloc> &
ft::DLNode<T, Alloc>::operator=(DLNode const & other)
{
	if (this != &other)
		DLNode<T, Alloc>::_copy(other);
	return (*this);
}

template <class T, class Alloc>
void
ft::DLNode<T, Alloc>::_copy(DLNode const & other)
{
	value = other.value;
	prev = other.prev;
	next = other.next;
}

/* BaseIterator */
template <class T, class Alloc>
ft::DLNode<T, Alloc>::BaseIterator::BaseIterator(DLNode<T, Alloc> * t)
						: _target(t)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::BaseIterator::~BaseIterator(void)
{
}


template <class T, class Alloc>
ft::DLNode<T, Alloc>::BaseIterator::BaseIterator(BaseIterator const & other)
{
	_copy(other);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::BaseIterator &
ft::DLNode<T, Alloc>::BaseIterator::operator=(BaseIterator const & other)
{
	if (this != &other)
		_copy(other);
	return (*this);
}

template <class T, class Alloc>
void
ft::DLNode<T, Alloc>::BaseIterator::_copy(BaseIterator const & other)
{
	_target = other.get_target();
}

template <class T, class Alloc>
bool
ft::DLNode<T, Alloc>::BaseIterator::operator==(BaseIterator const & other) const
{
	return (_target == other.get_target());
}

template <class T, class Alloc>
bool
ft::DLNode<T, Alloc>::BaseIterator::operator!=(BaseIterator const & other) const
{
	return (_target != other.get_target());
}

/* Iterator */
template <class T, class Alloc>
ft::DLNode<T, Alloc>::Iterator::Iterator(DLNode<T, Alloc> * t)
						: BaseIterator(t)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::Iterator::~Iterator(void)
{
}


template <class T, class Alloc>
ft::DLNode<T, Alloc>::Iterator::Iterator(Iterator const & other)
						 : BaseIterator(other)
{
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::Iterator &
ft::DLNode<T, Alloc>::Iterator::operator=(Iterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::Iterator &
ft::DLNode<T, Alloc>::Iterator::operator++(void)
{
	Iterator::_target = Iterator::_target->next;
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::Iterator
ft::DLNode<T, Alloc>::Iterator::operator++(int)
{
	Iterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::Iterator &
ft::DLNode<T, Alloc>::Iterator::operator--(void)
{
	Iterator::_target = Iterator::_target->prev;
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::Iterator
ft::DLNode<T, Alloc>::Iterator::operator--(int)
{
	Iterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T, class Alloc>
T &
ft::DLNode<T, Alloc>::Iterator::operator*(void) const
{
	return (Iterator::_target->value);
}

template <class T, class Alloc>
T *
ft::DLNode<T, Alloc>::Iterator::operator->(void) const
{
	return (&(Iterator::_target->value));
}

/* CIterator */
template <class T, class Alloc>
ft::DLNode<T, Alloc>::CIterator::CIterator(DLNode<T, Alloc> * t)
						: BaseIterator(t)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::CIterator::CIterator(Iterator const & it)
						: BaseIterator(it)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::CIterator::~CIterator(void)
{
}


template <class T, class Alloc>
ft::DLNode<T, Alloc>::CIterator::CIterator(CIterator const & other)
						 : BaseIterator(other)
{
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CIterator &
ft::DLNode<T, Alloc>::CIterator::operator=(CIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CIterator &
ft::DLNode<T, Alloc>::CIterator::operator++(void)
{
	CIterator::_target = CIterator::_target->next;
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CIterator
ft::DLNode<T, Alloc>::CIterator::operator++(int)
{
	CIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CIterator &
ft::DLNode<T, Alloc>::CIterator::operator--(void)
{
	CIterator::_target = CIterator::_target->prev;
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CIterator
ft::DLNode<T, Alloc>::CIterator::operator--(int)
{
	CIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T, class Alloc>
T const &
ft::DLNode<T, Alloc>::CIterator::operator*(void) const
{
	return (CIterator::_target->value);
}

template <class T, class Alloc>
T const *
ft::DLNode<T, Alloc>::CIterator::operator->(void) const
{
	return (&(CIterator::_target->value));
}

/* RIterator */
template <class T, class Alloc>
ft::DLNode<T, Alloc>::RIterator::RIterator(DLNode<T, Alloc> * t)
						 : BaseIterator(t)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::RIterator::~RIterator(void)
{
}


template <class T, class Alloc>
ft::DLNode<T, Alloc>::RIterator::RIterator(RIterator const & other)
						: BaseIterator(other)
{
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::RIterator &
ft::DLNode<T, Alloc>::RIterator::operator=(RIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::RIterator &
ft::DLNode<T, Alloc>::RIterator::operator++(void)
{
	RIterator::_target = RIterator::_target->prev;
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::RIterator
ft::DLNode<T, Alloc>::RIterator::operator++(int)
{
	RIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::RIterator &
ft::DLNode<T, Alloc>::RIterator::operator--(void)
{
	RIterator::_target = RIterator::_target->next;
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::RIterator
ft::DLNode<T, Alloc>::RIterator::operator--(int)
{
	RIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T, class Alloc>
T &
ft::DLNode<T, Alloc>::RIterator::operator*(void) const
{
	return (RIterator::_target->value);
}

template <class T, class Alloc>
T *
ft::DLNode<T, Alloc>::RIterator::operator->(void) const
{
	return (&(RIterator::_target->value));
}

/* CRIterator */
template <class T, class Alloc>
ft::DLNode<T, Alloc>::CRIterator::CRIterator(DLNode<T, Alloc> * t)
						 : BaseIterator(t)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::CRIterator::CRIterator(RIterator const & rit)
						 : BaseIterator(rit)
{
}

template <class T, class Alloc>
ft::DLNode<T, Alloc>::CRIterator::~CRIterator(void)
{
}


template <class T, class Alloc>
ft::DLNode<T, Alloc>::CRIterator::CRIterator(CRIterator const & other)
						: BaseIterator(other)
{
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CRIterator &
ft::DLNode<T, Alloc>::CRIterator::operator=(CRIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CRIterator &
ft::DLNode<T, Alloc>::CRIterator::operator++(void)
{
	CRIterator::_target = CRIterator::_target->prev;
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CRIterator
ft::DLNode<T, Alloc>::CRIterator::operator++(int)
{
	CRIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CRIterator &
ft::DLNode<T, Alloc>::CRIterator::operator--(void)
{
	CRIterator::_target = CRIterator::_target->next;
	return (*this);
}

template <class T, class Alloc>
typename ft::DLNode<T, Alloc>::CRIterator
ft::DLNode<T, Alloc>::CRIterator::operator--(int)
{
	CRIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T, class Alloc>
T const &
ft::DLNode<T, Alloc>::CRIterator::operator*(void) const
{
	return (CRIterator::_target->value);
}

template <class T, class Alloc>
T const *
ft::DLNode<T, Alloc>::CRIterator::operator->(void) const
{
	return (&(CRIterator::_target->value));
}