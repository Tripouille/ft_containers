#include "List.hpp"

/* Constructor */
/** default	(1) **/
template <class T, class Alloc>
ft::List<T, Alloc>::List(const allocator_type & alloc)
				   : _alloc(alloc), _size(0), _head(NULL), _tail(NULL)
{
}

/** fill		(2) **/
template <class T, class Alloc>
ft::List<T, Alloc>::List (size_type n, const value_type & val,
							const allocator_type & alloc)
				   : _alloc(alloc), _size(n), _head(NULL), _tail(NULL)
{
	while (n--)
		;
	(void)val;
}

/** range		(3) **/

/** copy		(4) **/
template <class T, class Alloc>
ft::List<T, Alloc>::List(List const & other)
{
	_copy(other);
}

/* Destructor */
template <class T, class Alloc>
ft::List<T, Alloc>::~List(void)
{
}

/* Operator */
template <class T, class Alloc>
ft::List<T, Alloc> &
ft::List<T, Alloc>::operator=(List const & other)
{
	if (this != &other)
		_copy(other);
	return (*this);
}

/* Public functions */
/** Iterator **/

/** Capacity **/
template <class T, class Alloc>
bool
ft::List<T, Alloc>::empty(void) const
{
	return (_head == NULL);
}

template <class T, class Alloc>
typename ft::List<T, Alloc>::size_type
ft::List<T, Alloc>::size(void) const
{
	return (_size);
}

template <class T, class Alloc>
typename ft::List<T, Alloc>::size_type
ft::List<T, Alloc>::max_size(void) const
{
	return (std::numeric_limits<size_type>::max() / sizeof(node));
}

/** Element access **/

/** Modifiers **/

/** Operations **/

/* Private functions */
template <class T, class Alloc>
void
ft::List<T, Alloc>::_copy(List const & other)
{
	(void)other;
}