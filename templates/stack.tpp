#include "stack.hpp"

/* Constructor */
template <class T, class Container>
ft::stack<T, Container>::stack(const container_type & ctnr) : _c(ctnr)
{
}

template <class T, class Container>
ft::stack<T, Container>::stack(const stack & other) : _c(other._c)
{
}


/* Destructor */
template <class T, class Container>
ft::stack<T, Container>::~stack(void)
{
}


/* Operator */
template <class T, class Container>
typename ft::stack<T, Container> &
ft::stack<T, Container>::operator=(const stack & other)
{
	if (this != &other)
		_c = other._c;
	return (*this);
}


/* Member functions */
template <class T, class Container>
bool
ft::stack<T, Container>::empty(void) const
{
	return (_c.empty());
}

template <class T, class Container>
typename ft::stack<T, Container>::size_type
ft::stack<T, Container>::size(void) const
{
	return (_c.size());
}

template <class T, class Container>
typename ft::stack<T, Container>::value_type &
ft::stack<T, Container>::top(void)
{
	return (_c.back());
}

template <class T, class Container>
typename ft::stack<T, Container>::value_type const &
ft::stack<T, Container>::top(void) const
{
	return (_c.back());
}

template <class T, class Container>
void
ft::stack<T, Container>::push(const value_type & val) 
{
	_c.push_back(val);
}

template <class T, class Container>
void
ft::stack<T, Container>::pop(void) 
{
	_c.pop_back();
}


/** Relational operators **/
template <class T, class Container>
bool
ft::stack<T, Container>::operator==(const stack<T, Container> & rhs) const
{
	return (_c == rhs._c);
}

template <class T, class Container>
bool
ft::stack<T, Container>::operator!=(const stack<T, Container> & rhs) const
{
	return (_c != rhs._c);
}

template <class T, class Container>
bool
ft::stack<T, Container>::operator<(const stack<T, Container> & rhs) const
{
	return (_c < rhs._c);
}

template <class T, class Container>
bool
ft::stack<T, Container>::operator<=(const stack<T, Container> & rhs) const
{
	return (_c <= rhs._c);
}

template <class T, class Container>
bool
ft::stack<T, Container>::operator>(const stack<T, Container> & rhs) const
{
	return (_c > rhs._c);
}

template <class T, class Container>
bool
ft::stack<T, Container>::operator>=(const stack<T, Container> & rhs) const
{
	return (_c >= rhs._c);
}


/* Non-member function overloads */
/** Relational operators **/
template<class T, class Container>
bool
ft::operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (lhs.operator==(rhs));
}

template<class T, class Container>
bool
ft::operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (lhs._c.operator!=(rhs));
}

template<class T, class Container>
bool
ft::operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (lhs._c.operator<(rhs));
}

template<class T, class Container>
bool
ft::operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (lhs._c.operator<=(rhs));
}

template<class T, class Container>
bool
ft::operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (lhs._c.operator>(rhs));
}

template<class T, class Container>
bool
ft::operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (lhs._c.operator>=(rhs));
}