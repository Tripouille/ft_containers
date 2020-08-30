#include "List.hpp"

/* Constructor */
/** default	(1) **/
template <class T, class Alloc>
ft::List<T, Alloc>::List(const allocator_type & alloc)
				   : _alloc(alloc), _head(NULL), _tail(NULL)
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

/* Public Functions */

/* Private Functions */
template <class T, class Alloc>
void
ft::List<T, Alloc>::_copy(List const & other)
{
	(void)other;
}