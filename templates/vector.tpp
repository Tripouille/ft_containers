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
	_copy(other);
}

/* Destructor */
template <class T, class Alloc>
ft::vector<T, Alloc>::~vector(void)
{
	_alloc.deallocate(_start, static_cast<size_type>(_end - _start));
}

/* Operator */
template <class T, class Alloc>
ft::vector<T, Alloc> &
ft::vector<T, Alloc>::operator=(vector const & other)
{
	if (this == &other)
	{
		clear();
		_copy(other);
	}
	return (*this);
}

/* Public functions */
/** Iterator **/

/** Capacity **/

/** Element access **/

/** Modifiers **/

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::clear(void)
{
	delete[] _start;
	_start = NULL;
	_end = NULL;
	_limit = NULL;
}

/** Operations **/

/** Observers **/

/** Private functions **/

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::_copy(vector const & other)
{
	_start = _alloc.allocate(other._end - other._start);
	pointer this_ptr = _start;
	pointer other_ptr = other._start;
	while (other_ptr != other._end)
	{
		_alloc.construct(this_ptr, *other_ptr);
		++this_ptr;
		++other_ptr;
	}
	_end = _limit = this_ptr;
}

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