#include "BTNode.hpp"

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BTNode(void)
				   : parent(NULL), left(NULL), right(NULL)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BTNode(const Key & k, const T & v,
							BTNode * p, BTNode * l, BTNode * r)
		  	  	   : pair(std::pair<Key, T>(k, v)), parent(p), left(l), right(r)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::~BTNode(void)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BTNode(BTNode const & other)
{
	node::_copy(other);
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc> &
ft::BTNode<Key, T, Compare, Alloc>::operator=(BTNode const & other)
{
	if (this != &other)
		node::_copy(other);
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
void
ft::BTNode<Key, T, Compare, Alloc>::_copy(BTNode const & other)
{
	pair = other.pair;
	parent = other.parent;
	left = other.left;
	right = other.right;
}


//BaseIterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::BaseIterator(node * n)
						: _node(n)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::~BaseIterator(void)
{
}


template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::BaseIterator(BaseIterator const & other)
{
	_copy(other);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::BaseIterator &
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::operator=(BaseIterator const & other)
{
	if (this != &other)
		_copy(other);
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
void
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::_copy(BaseIterator const & other)
{
	_node = other._node;
}

template <class Key, class T, class Compare, class Alloc>
bool
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::operator==(BaseIterator const & other) const
{
	return (_node == other._node);
}

template <class Key, class T, class Compare, class Alloc>
bool
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::operator!=(BaseIterator const & other) const
{
	return (_node != other._node);
}

//Iterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::Iterator::Iterator(node * n)
						: BaseIterator(n)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::Iterator::~Iterator(void)
{
}


template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::Iterator::Iterator(Iterator const & other)
						 : BaseIterator(other)
{
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::Iterator &
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator=(Iterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::Iterator &
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator++(void)
{
	if (Iterator::_node == NULL)
		return (*this);

	bool left_child = Iterator::_node->parent
					  && Iterator::_node == Iterator::_node->parent->left;

	if (Iterator::_node->right)
	{
		Iterator::_node = Iterator::_node->right;
		while (Iterator::_node->left)
			Iterator::_node = Iterator::_node->left;
	}
	else if (left_child)
		Iterator::_node = Iterator::_node->parent;
	else
	{
		while (Iterator::_node->parent
		&& Iterator::_node == Iterator::_node->parent->right)
			Iterator::_node = Iterator::_node->parent;
		Iterator::_node = Iterator::_node->parent;
	}
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::Iterator
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator++(int)
{
	Iterator tmp(*this);
	++*this;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::Iterator &
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator--(void)
{
	if (Iterator::_node == NULL)
		return (*this);

	bool right_child = Iterator::_node->parent
					  && Iterator::_node == Iterator::_node->parent->right;

	if (Iterator::_node->left)
	{
		Iterator::_node = Iterator::_node->left;
		while (Iterator::_node->right)
			Iterator::_node = Iterator::_node->right;
	}
	else if (right_child)
		Iterator::_node = Iterator::_node->parent;
	else
	{
		while (Iterator::_node->parent
		&& Iterator::_node == Iterator::_node->parent->left)
			Iterator::_node = Iterator::_node->parent;
		Iterator::_node = Iterator::_node->parent;
	}
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::Iterator
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator--(int)
{
	Iterator tmp(*this);
	--*this;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
std::pair<Key, T> &
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator*(void) const
{
	return (Iterator::_node->pair);
}

template <class Key, class T, class Compare, class Alloc>
std::pair<Key, T> *
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator->(void) const
{
	return (&Iterator::_node->pair);
}

/*
//CIterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CIterator::CIterator(BTNode<Key, T, Compare, Alloc> * n)
						: BaseIterator(n)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CIterator::CIterator(Iterator const & in)
						: BaseIterator(in)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CIterator::~CIterator(void)
{
}


template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CIterator::CIterator(CIterator const & other)
						 : BaseIterator(other)
{
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CIterator &
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator=(CIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CIterator &
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator++(void)
{
	CIterator::_node = CIterator::_node->next;
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CIterator
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator++(int)
{
	CIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CIterator &
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator--(void)
{
	CIterator::_node = CIterator::_node->prev;
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CIterator
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator--(int)
{
	CIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
T const &
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator*(void) const
{
	return (CIterator::_node->value);
}

template <class Key, class T, class Compare, class Alloc>
T const *
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator->(void) const
{
	return (&(CIterator::_node->value));
}

//RIterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::RIterator::RIterator(BTNode<Key, T, Compare, Alloc> * n)
						 : BaseIterator(n)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::RIterator::~RIterator(void)
{
}


template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::RIterator::RIterator(RIterator const & other)
						: BaseIterator(other)
{
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::RIterator &
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator=(RIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::RIterator &
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator++(void)
{
	RIterator::_node = RIterator::_node->prev;
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::RIterator
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator++(int)
{
	RIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::RIterator &
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator--(void)
{
	RIterator::_node = RIterator::_node->next;
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::RIterator
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator--(int)
{
	RIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
T &
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator*(void) const
{
	return (RIterator::_node->value);
}

template <class Key, class T, class Compare, class Alloc>
T *
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator->(void) const
{
	return (&(RIterator::_node->value));
}

//CRIterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::CRIterator(BTNode<Key, T, Compare, Alloc> * n)
						 : BaseIterator(n)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::CRIterator(RIterator const & rin)
						 : BaseIterator(rin)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::~CRIterator(void)
{
}


template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::CRIterator(CRIterator const & other)
						: BaseIterator(other)
{
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CRIterator &
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator=(CRIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CRIterator &
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator++(void)
{
	CRIterator::_node = CRIterator::_node->prev;
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CRIterator
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator++(int)
{
	CRIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CRIterator &
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator--(void)
{
	CRIterator::_node = CRIterator::_node->next;
	return (*this);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::CRIterator
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator--(int)
{
	CRIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
T const &
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator*(void) const
{
	return (CRIterator::_node->value);
}

template <class Key, class T, class Compare, class Alloc>
T const *
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator->(void) const
{
	return (&(CRIterator::_node->value));
}
*/