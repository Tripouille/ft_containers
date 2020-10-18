#include "BTNode.hpp"

template <class Key, class T>
ft::BTNode<Key, T>::BTNode(void)
				   : parent(NULL), left(NULL), right(NULL)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::BTNode(const Key & k, const T & v,
							BTNode * p, BTNode * l, BTNode * r)
		  	  	   : key(k), value(v), parent(p), left(l), right(r)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::~BTNode(void)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::BTNode(BTNode const & other)
{
	BTNode<Key, T>::_copy(other);
}

template <class Key, class T>
ft::BTNode<Key, T> &
ft::BTNode<Key, T>::operator=(BTNode const & other)
{
	if (this != &other)
		BTNode<Key, T>::_copy(other);
	return (*this);
}

template <class Key, class T>
void
ft::BTNode<Key, T>::_copy(BTNode const & other)
{
	key = other.key;
	value = other.value;
	parent = other.parent;
	left = other.left;
	right = other.right;
}

/*
//BaseIterator
template <class Key, class T>
ft::BTNode<Key, T>::BaseIterator::BaseIterator(BTNode<Key, T> * t)
						: _target(t)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::BaseIterator::~BaseIterator(void)
{
}


template <class Key, class T>
ft::BTNode<Key, T>::BaseIterator::BaseIterator(BaseIterator const & other)
{
	_copy(other);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::BaseIterator &
ft::BTNode<Key, T>::BaseIterator::operator=(BaseIterator const & other)
{
	if (this != &other)
		_copy(other);
	return (*this);
}

template <class Key, class T>
void
ft::BTNode<Key, T>::BaseIterator::_copy(BaseIterator const & other)
{
	_target = other._target;
}

template <class Key, class T>
bool
ft::BTNode<Key, T>::BaseIterator::operator==(BaseIterator const & other) const
{
	return (_target == other._target);
}

template <class Key, class T>
bool
ft::BTNode<Key, T>::BaseIterator::operator!=(BaseIterator const & other) const
{
	return (_target != other._target);
}

//Iterator
template <class Key, class T>
ft::BTNode<Key, T>::Iterator::Iterator(BTNode<Key, T> * t)
						: BaseIterator(t)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::Iterator::~Iterator(void)
{
}


template <class Key, class T>
ft::BTNode<Key, T>::Iterator::Iterator(Iterator const & other)
						 : BaseIterator(other)
{
}

template <class Key, class T>
typename ft::BTNode<Key, T>::Iterator &
ft::BTNode<Key, T>::Iterator::operator=(Iterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::Iterator &
ft::BTNode<Key, T>::Iterator::operator++(void)
{
	Iterator::_target = Iterator::_target->next;
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::Iterator
ft::BTNode<Key, T>::Iterator::operator++(int)
{
	Iterator tmp(*this);
	++*this;
	return (tmp);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::Iterator &
ft::BTNode<Key, T>::Iterator::operator--(void)
{
	Iterator::_target = Iterator::_target->prev;
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::Iterator
ft::BTNode<Key, T>::Iterator::operator--(int)
{
	Iterator tmp(*this);
	--*this;
	return (tmp);
}

template <class Key, class T>
T &
ft::BTNode<Key, T>::Iterator::operator*(void) const
{
	return (Iterator::_target->value);
}

template <class Key, class T>
T *
ft::BTNode<Key, T>::Iterator::operator->(void) const
{
	return (&(Iterator::_target->value));
}

//CIterator
template <class Key, class T>
ft::BTNode<Key, T>::CIterator::CIterator(BTNode<Key, T> * t)
						: BaseIterator(t)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::CIterator::CIterator(Iterator const & it)
						: BaseIterator(it)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::CIterator::~CIterator(void)
{
}


template <class Key, class T>
ft::BTNode<Key, T>::CIterator::CIterator(CIterator const & other)
						 : BaseIterator(other)
{
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CIterator &
ft::BTNode<Key, T>::CIterator::operator=(CIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CIterator &
ft::BTNode<Key, T>::CIterator::operator++(void)
{
	CIterator::_target = CIterator::_target->next;
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CIterator
ft::BTNode<Key, T>::CIterator::operator++(int)
{
	CIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CIterator &
ft::BTNode<Key, T>::CIterator::operator--(void)
{
	CIterator::_target = CIterator::_target->prev;
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CIterator
ft::BTNode<Key, T>::CIterator::operator--(int)
{
	CIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class Key, class T>
T const &
ft::BTNode<Key, T>::CIterator::operator*(void) const
{
	return (CIterator::_target->value);
}

template <class Key, class T>
T const *
ft::BTNode<Key, T>::CIterator::operator->(void) const
{
	return (&(CIterator::_target->value));
}

//RIterator
template <class Key, class T>
ft::BTNode<Key, T>::RIterator::RIterator(BTNode<Key, T> * t)
						 : BaseIterator(t)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::RIterator::~RIterator(void)
{
}


template <class Key, class T>
ft::BTNode<Key, T>::RIterator::RIterator(RIterator const & other)
						: BaseIterator(other)
{
}

template <class Key, class T>
typename ft::BTNode<Key, T>::RIterator &
ft::BTNode<Key, T>::RIterator::operator=(RIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::RIterator &
ft::BTNode<Key, T>::RIterator::operator++(void)
{
	RIterator::_target = RIterator::_target->prev;
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::RIterator
ft::BTNode<Key, T>::RIterator::operator++(int)
{
	RIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::RIterator &
ft::BTNode<Key, T>::RIterator::operator--(void)
{
	RIterator::_target = RIterator::_target->next;
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::RIterator
ft::BTNode<Key, T>::RIterator::operator--(int)
{
	RIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class Key, class T>
T &
ft::BTNode<Key, T>::RIterator::operator*(void) const
{
	return (RIterator::_target->value);
}

template <class Key, class T>
T *
ft::BTNode<Key, T>::RIterator::operator->(void) const
{
	return (&(RIterator::_target->value));
}

//CRIterator
template <class Key, class T>
ft::BTNode<Key, T>::CRIterator::CRIterator(BTNode<Key, T> * t)
						 : BaseIterator(t)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::CRIterator::CRIterator(RIterator const & rit)
						 : BaseIterator(rit)
{
}

template <class Key, class T>
ft::BTNode<Key, T>::CRIterator::~CRIterator(void)
{
}


template <class Key, class T>
ft::BTNode<Key, T>::CRIterator::CRIterator(CRIterator const & other)
						: BaseIterator(other)
{
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CRIterator &
ft::BTNode<Key, T>::CRIterator::operator=(CRIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CRIterator &
ft::BTNode<Key, T>::CRIterator::operator++(void)
{
	CRIterator::_target = CRIterator::_target->prev;
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CRIterator
ft::BTNode<Key, T>::CRIterator::operator++(int)
{
	CRIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CRIterator &
ft::BTNode<Key, T>::CRIterator::operator--(void)
{
	CRIterator::_target = CRIterator::_target->next;
	return (*this);
}

template <class Key, class T>
typename ft::BTNode<Key, T>::CRIterator
ft::BTNode<Key, T>::CRIterator::operator--(int)
{
	CRIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class Key, class T>
T const &
ft::BTNode<Key, T>::CRIterator::operator*(void) const
{
	return (CRIterator::_target->value);
}

template <class Key, class T>
T const *
ft::BTNode<Key, T>::CRIterator::operator->(void) const
{
	return (&(CRIterator::_target->value));
}
*/