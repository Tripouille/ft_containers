#include "vector.hpp"

/* Constructor */
/** default	(1) **/
template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type & alloc)
					 : _alloc(alloc), _start(NULL), _end(NULL), _limit(NULL)
{
}

/** fill		(2) **/
template <class T, class Alloc>
ft::vector<T, Alloc>::vector(size_type n, const value_type & val,
										const allocator_type & alloc)
					 : _alloc(alloc), _start(NULL), _end(NULL), _limit(NULL)
{
	_start = _alloc.allocate(n);
	_construct_vector_with_val(n, val);
}

/** range		(3) **/
/*template <class T, class Alloc>
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
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::begin(void)
{
	return (iterator(_start));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::end(void)
{
	return (iterator(_end));
}

/** Capacity **/

/** Element access **/

/** Modifiers **/

/** Operations **/

/** Observers **/

/** Private functions **/

template <class T, class Alloc>
template <class Integer>
void
ft::vector<T, Alloc>::_construct_vector_dispatch(Integer & n, Integer & val, INT_TYPE)
{
	_construct_vector_with_val(n, val);
}

template <class T, class Alloc>
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

template <class T, class Alloc>
void
ft::vector<T, Alloc>::_construct_vector_with_val(size_type n, const value_type & val)
{
	for (size_type i = 0; i < n; ++i)
		_alloc.construct(_start + i, val);
}

/** Non-member function overloads **/

/* BaseIterator */
template <class T, class Alloc>

ft::vector<T, Alloc>::BaseIterator::BaseIterator(vector<T, Alloc> * t)
					 : _target(t)
{
}

template <class T, class Alloc>
ft::vector<T, Alloc>::BaseIterator::~BaseIterator(void)
{
}


template <class T, class Alloc>
ft::vector<T, Alloc>::BaseIterator::BaseIterator(BaseIterator const & other)
{
	_copy(other);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::BaseIterator &
ft::vector<T, Alloc>::BaseIterator::operator=(BaseIterator const & other)
{
	if (this != &other)
		_copy(other);
	return (*this);
}

template <class T, class Alloc>
void
ft::vector<T, Alloc>::BaseIterator::_copy(BaseIterator const & other)
{
	_target = other._target;
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator==(BaseIterator const & other) const
{
	return (_target == other._target);
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator!=(BaseIterator const & other) const
{
	return (_target != other._target);
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator<(BaseIterator const & other) const
{
	return (_target < other._target);
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator>(BaseIterator const & other) const
{
	return (_target > other._target);
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator<=(BaseIterator const & other) const
{
	return (_target <= other._target);
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator>=(BaseIterator const & other) const
{
	return (_target >= other._target);
}

/* Iterator */
template <class T, class Alloc>
ft::vector<T, Alloc>::Iterator::Iterator(vector<T, Alloc> * t)
						: BaseIterator(t)
{
}

template <class T, class Alloc>
ft::vector<T, Alloc>::Iterator::~Iterator(void)
{
}


template <class T, class Alloc>
ft::vector<T, Alloc>::Iterator::Iterator(Iterator const & other)
						 : BaseIterator(other)
{
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator &
ft::vector<T, Alloc>::Iterator::operator=(Iterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T, class Alloc>
T &
ft::vector<T, Alloc>::Iterator::operator*(void) const
{
	return (*(Iterator::_target));
}

template <class T, class Alloc>
T *
ft::vector<T, Alloc>::Iterator::operator->(void) const
{
	return (Iterator::_target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator &
ft::vector<T, Alloc>::Iterator::operator++(void)
{
	++BaseIterator::_target;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator
ft::vector<T, Alloc>::Iterator::operator++(int)
{
	Iterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator &
ft::vector<T, Alloc>::Iterator::operator--(void)
{
	--BaseIterator::_target;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator
ft::vector<T, Alloc>::Iterator::operator--(int)
{
	Iterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator
ft::vector<T, Alloc>::Iterator::operator+(typename BaseIterator::difference_type i) const
{
	return (Iterator(BaseIterator::_target + i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator
ft::vector<T, Alloc>::Iterator::operator-(typename BaseIterator::difference_type i) const
{
	return (Iterator(BaseIterator::_target - i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::BaseIterator::difference_type
ft::vector<T, Alloc>::Iterator::operator-(Iterator const & other) const
{
	return ((BaseIterator::_target - other._target) / sizeof(*BaseIterator::_target));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator &
ft::vector<T, Alloc>::Iterator::operator+=(typename BaseIterator::difference_type i)
{
	BaseIterator::_target += i;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator &
ft::vector<T, Alloc>::Iterator::operator-=(typename BaseIterator::difference_type i)
{
	BaseIterator::_target -= i;
	return (*this);
}

template <class T, class Alloc>
T &
ft::vector<T, Alloc>::Iterator::operator[](typename BaseIterator::difference_type i) const
{
	return (*(BaseIterator::_target + i));
}