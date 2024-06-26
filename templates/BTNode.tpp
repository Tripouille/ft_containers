#include "BTNode.hpp"

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BTNode(void)
				   : parent(NULL), left(NULL), right(NULL)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BTNode(const Key & k, const T & v,
							BTNode * p, BTNode * l, BTNode * r)
		  	  	   : pair(std::pair<Key const, T>(k, v)), parent(p), left(l), right(r)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::~BTNode(void)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BTNode(BTNode const & other) : pair(other.pair)
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
	parent = other.parent;
	left = other.left;
	right = other.right;
}


//BaseIterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::BaseIterator(node * n, node * const * root)
						: _node(n), _root_ptr(root)
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
	_root_ptr = other._root_ptr;
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::node *
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::_get_first_node(void)
{
	node * tmp = *_root_ptr;

	if (tmp != NULL)
		while (tmp->left != NULL)
			tmp = tmp->left;
	return (tmp);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::BTNode<Key, T, Compare, Alloc>::node *
ft::BTNode<Key, T, Compare, Alloc>::BaseIterator::_get_last_node(void)
{
	node * tmp = *_root_ptr;

	if (tmp != NULL)
		while (tmp->right != NULL)
			tmp = tmp->right;
	return (tmp);
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
ft::BTNode<Key, T, Compare, Alloc>::Iterator::Iterator(node * n, node * const * root)
						: BaseIterator(n, root)
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
	{
		Iterator::_node = Iterator::_get_first_node();
		return (*this);
	}

	if (Iterator::_node->right)
	{
		Iterator::_node = Iterator::_node->right;
		while (Iterator::_node->left)
			Iterator::_node = Iterator::_node->left;
	}
	else if (Iterator::_node->parent
	&& Iterator::_node == Iterator::_node->parent->left)
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
	{
		Iterator::_node = Iterator::_get_last_node();
		return (*this);
	}

	if (Iterator::_node->left)
	{
		Iterator::_node = Iterator::_node->left;
		while (Iterator::_node->right)
			Iterator::_node = Iterator::_node->right;
	}
	else if (Iterator::_node->parent
	&& Iterator::_node == Iterator::_node->parent->right)
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
std::pair<Key const, T> &
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator*(void) const
{
	return (Iterator::_node->pair);
}

template <class Key, class T, class Compare, class Alloc>
std::pair<Key const, T> *
ft::BTNode<Key, T, Compare, Alloc>::Iterator::operator->(void) const
{
	return (&Iterator::_node->pair);
}


//CIterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CIterator::CIterator(node * n, node * const * root)
						: BaseIterator(n, root)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CIterator::CIterator(Iterator const & it)
						: BaseIterator(it)
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
	if (CIterator::_node == NULL)
	{
		CIterator::_node = CIterator::_get_first_node();
		return (*this);
	}

	if (CIterator::_node->right)
	{
		CIterator::_node = CIterator::_node->right;
		while (CIterator::_node->left)
			CIterator::_node = CIterator::_node->left;
	}
	else if (CIterator::_node->parent
	&& CIterator::_node == CIterator::_node->parent->left)
		CIterator::_node = CIterator::_node->parent;
	else
	{
		while (CIterator::_node->parent
		&& CIterator::_node == CIterator::_node->parent->right)
			CIterator::_node = CIterator::_node->parent;
		CIterator::_node = CIterator::_node->parent;
	}
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
	if (CIterator::_node == NULL)
	{
		CIterator::_node = CIterator::_get_last_node();
		return (*this);
	}

	if (CIterator::_node->left)
	{
		CIterator::_node = CIterator::_node->left;
		while (CIterator::_node->right)
			CIterator::_node = CIterator::_node->right;
	}
	else if (CIterator::_node->parent
	&& CIterator::_node == CIterator::_node->parent->right)
		CIterator::_node = CIterator::_node->parent;
	else
	{
		while (CIterator::_node->parent
		&& CIterator::_node == CIterator::_node->parent->left)
			CIterator::_node = CIterator::_node->parent;
		CIterator::_node = CIterator::_node->parent;
	}
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
std::pair<Key const, T> const &
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator*(void) const
{
	return (CIterator::_node->pair);
}

template <class Key, class T, class Compare, class Alloc>
std::pair<Key const, T> const *
ft::BTNode<Key, T, Compare, Alloc>::CIterator::operator->(void) const
{
	return (&(CIterator::_node->pair));
}

//RIterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::RIterator::RIterator(node * n, node * const * root)
						 : BaseIterator(n, root)
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
	if (RIterator::_node == NULL)
	{
		RIterator::_node = RIterator::_get_last_node();
		return (*this);
	}

	if (RIterator::_node->left)
	{
		RIterator::_node = RIterator::_node->left;
		while (RIterator::_node->right)
			RIterator::_node = RIterator::_node->right;
	}
	else if (RIterator::_node->parent
	&& RIterator::_node == RIterator::_node->parent->right)
		RIterator::_node = RIterator::_node->parent;
	else
	{
		while (RIterator::_node->parent
		&& RIterator::_node == RIterator::_node->parent->left)
			RIterator::_node = RIterator::_node->parent;
		RIterator::_node = RIterator::_node->parent;
	}
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
	if (RIterator::_node == NULL)
	{
		RIterator::_node = RIterator::_get_first_node();
		return (*this);
	}

	if (RIterator::_node->right)
	{
		RIterator::_node = RIterator::_node->right;
		while (RIterator::_node->left)
			RIterator::_node = RIterator::_node->left;
	}
	else if (RIterator::_node->parent
	&& RIterator::_node == RIterator::_node->parent->left)
		RIterator::_node = RIterator::_node->parent;
	else
	{
		while (RIterator::_node->parent
		&& RIterator::_node == RIterator::_node->parent->right)
			RIterator::_node = RIterator::_node->parent;
		RIterator::_node = RIterator::_node->parent;
	}
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
std::pair<Key const, T> &
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator*(void) const
{
	return (RIterator::_node->pair);
}

template <class Key, class T, class Compare, class Alloc>
std::pair<Key const, T> *
ft::BTNode<Key, T, Compare, Alloc>::RIterator::operator->(void) const
{
	return (&(RIterator::_node->pair));
}

//CRIterator
template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::CRIterator(node * n, node * const * root)
						 : BaseIterator(n, root)
{
}

template <class Key, class T, class Compare, class Alloc>
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::CRIterator(RIterator const & rit)
						 : BaseIterator(rit)
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
	if (CRIterator::_node == NULL)
	{
		CRIterator::_node = CRIterator::_get_last_node();
		return (*this);
	}

	if (CRIterator::_node->left)
	{
		CRIterator::_node = CRIterator::_node->left;
		while (CRIterator::_node->right)
			CRIterator::_node = CRIterator::_node->right;
	}
	else if (CRIterator::_node->parent
	&& CRIterator::_node == CRIterator::_node->parent->right)
		CRIterator::_node = CRIterator::_node->parent;
	else
	{
		while (CRIterator::_node->parent
		&& CRIterator::_node == CRIterator::_node->parent->left)
			CRIterator::_node = CRIterator::_node->parent;
		CRIterator::_node = CRIterator::_node->parent;
	}
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
	if (CRIterator::_node == NULL)
	{
		CRIterator::_node = CRIterator::_get_first_node();
		return (*this);
	}

	if (CRIterator::_node->right)
	{
		CRIterator::_node = CRIterator::_node->right;
		while (CRIterator::_node->left)
			CRIterator::_node = CRIterator::_node->left;
	}
	else if (CRIterator::_node->parent
	&& CRIterator::_node == CRIterator::_node->parent->left)
		CRIterator::_node = CRIterator::_node->parent;
	else
	{
		while (CRIterator::_node->parent
		&& CRIterator::_node == CRIterator::_node->parent->right)
			CRIterator::_node = CRIterator::_node->parent;
		CRIterator::_node = CRIterator::_node->parent;
	}
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
std::pair<Key const, T> const &
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator*(void) const
{
	return (CRIterator::_node->pair);
}

template <class Key, class T, class Compare, class Alloc>
std::pair<Key const, T> const *
ft::BTNode<Key, T, Compare, Alloc>::CRIterator::operator->(void) const
{
	return (&(CRIterator::_node->pair));
}