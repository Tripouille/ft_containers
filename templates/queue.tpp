#include "queue.hpp"

/* Constructor */
template <class T, class Container>
ft::queue<T, Container>::queue(const container_type & ctnr) : _c(ctnr)
{
}

template <class T, class Container>
ft::queue<T, Container>::queue(const queue & other) : _c(other._c)
{
}


/* Destructor */
template <class T, class Container>
ft::queue<T, Container>::~queue(void)
{
}


/* Operator */
template <class T, class Container>
typename ft::queue<T, Container> &
ft::queue<T, Container>::operator=(const queue & other)
{
	if (this != &other)
		_c = other._c;
	return (*this);
}


/* Member functions */
template <class T, class Container>
bool
ft::queue<T, Container>::empty(void) const
{
	return (_c.empty());
}

template <class T, class Container>
typename ft::queue<T, Container>::size_type
ft::queue<T, Container>::size(void) const
{
	return (_c.size());
}

template <class T, class Container>
typename ft::queue<T, Container>::value_type &
ft::queue<T, Container>::front(void)
{
	return (_c.front());
}

template <class T, class Container>
typename ft::queue<T, Container>::value_type const &
ft::queue<T, Container>::front(void) const
{
	return (_c.front());
}

template <class T, class Container>
typename ft::queue<T, Container>::value_type &
ft::queue<T, Container>::back(void)
{
	return (_c.back());
}

template <class T, class Container>
typename ft::queue<T, Container>::value_type const &
ft::queue<T, Container>::back(void) const
{
	return (_c.back());
}

template <class T, class Container>
void
ft::queue<T, Container>::push(const value_type & val) 
{
	_c.push_back(val);
}

template <class T, class Container>
void
ft::queue<T, Container>::pop(void) 
{
	_c.pop_front();
}


/** Relational operators **/
template <class T, class Container>
bool
ft::queue<T, Container>::operator==(const queue<T, Container> & rhs) const
{
	return (_c == rhs._c);
}

template <class T, class Container>
bool
ft::queue<T, Container>::operator!=(const queue<T, Container> & rhs) const
{
	return (_c != rhs._c);
}

template <class T, class Container>
bool
ft::queue<T, Container>::operator<(const queue<T, Container> & rhs) const
{
	return (_c < rhs._c);
}

template <class T, class Container>
bool
ft::queue<T, Container>::operator<=(const queue<T, Container> & rhs) const
{
	return (_c <= rhs._c);
}

template <class T, class Container>
bool
ft::queue<T, Container>::operator>(const queue<T, Container> & rhs) const
{
	return (_c > rhs._c);
}

template <class T, class Container>
bool
ft::queue<T, Container>::operator>=(const queue<T, Container> & rhs) const
{
	return (_c >= rhs._c);
}


/* Non-member function overloads */
/** Relational operators **/
template<class T, class Container>
bool
ft::operator==(const queue<T, Container> & lhs, const queue<T, Container> & rhs)
{
	return (lhs.operator==(rhs));
}

template<class T, class Container>
bool
ft::operator!=(const queue<T, Container> & lhs, const queue<T, Container> & rhs)
{
	return (lhs._c.operator!=(rhs));
}

template<class T, class Container>
bool
ft::operator<(const queue<T, Container> & lhs, const queue<T, Container> & rhs)
{
	return (lhs._c.operator<(rhs));
}

template<class T, class Container>
bool
ft::operator<=(const queue<T, Container> & lhs, const queue<T, Container> & rhs)
{
	return (lhs._c.operator<=(rhs));
}

template<class T, class Container>
bool
ft::operator>(const queue<T, Container> & lhs, const queue<T, Container> & rhs)
{
	return (lhs._c.operator>(rhs));
}

template<class T, class Container>
bool
ft::operator>=(const queue<T, Container> & lhs, const queue<T, Container> & rhs)
{
	return (lhs._c.operator>=(rhs));
}