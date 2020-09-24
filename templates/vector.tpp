#include "vector.hpp"

/* Constructor */
/** default	(1) **/
template <typename T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type & alloc)
					 : _alloc(alloc), _start(NULL), _end(NULL), _limit(NULL)
{
}

/** fill		(2) **/
template <typename T, class Alloc>
ft::vector<T, Alloc>::vector(size_type n, const value_type & val,
										const allocator_type & alloc)
					 : _alloc(alloc), _start(NULL), _end(NULL), _limit(NULL)
{
	_start = _alloc.allocate(n);
	_construct_vector_with_val(n, val);
}

/** range		(3) **/
/*template <typename T, class Alloc>
template <class InputIterator>
ft::vector<T, Alloc>::vector(InputIterator first, InputIterator last,
												const allocator_type & alloc)
					 : _alloc(alloc)
{
	_start = _alloc.allocate(last - first);
	_construct_vector_dispatch(first, last, typename is_integer<InputIterator>::type());
}*/

/** copy		(4) **/
template <class T, class Alloc>
ft::vector<T, Alloc>::vector(vector const & other)
{
	(void)other;
}

/* Destructor */
template <class T, class Alloc>
ft::vector<T, Alloc>::~vector(void)
{
	delete[] _start;
}

/* Operator */
template <class T, class Alloc>
ft::vector<T, Alloc> &
ft::vector<T, Alloc>::operator=(vector const & other)
{
	(void)other;
	return (*this);
}

/* Public functions */
/** Iterator **/

/** Capacity **/

/** Element access **/

/** Modifiers **/

/** Operations **/

/** Observers **/

/** Private functions **/

template <typename T, class Alloc>
template <class Integer>
void
ft::vector<T, Alloc>::_construct_vector_dispatch(Integer & n, Integer & val, INT_TYPE)
{
	_construct_vector_with_val(n, val);
}

template <typename T, class Alloc>
template <class InputIterator>
void
ft::vector<T, Alloc>::_construct_vector_dispatch(InputIterator & first, InputIterator & last, NO_INT_TYPE)
{
	int i = 0;
	while (first != last)
	{
		_alloc.construct(_start + i, *first);
		++first;
		++i;
	}
}

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::_construct_vector_with_val(size_type n, const value_type & val)
{
	for (size_type i = 0; i < n; ++i)
		_alloc.construct(_start + i, val);
}

/** Non-member function overloads **/