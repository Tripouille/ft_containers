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
	_construct_vector_with_val(n, val);
}

/** range		(3) **/
template <class T, class Alloc>
template <class InputIterator>
ft::vector<T, Alloc>::vector(InputIterator first, InputIterator last,
												const allocator_type & alloc)
					 : _alloc(alloc)
{
	_construct_vector_dispatch(first, last, typename is_integer<InputIterator>::type());
}

/** copy		(4) **/
template <class T, class Alloc>
ft::vector<T, Alloc>::vector(vector const & other) : _alloc(other._alloc)
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
	if (this != &other)
	{
		clear();
		_copy(other);
	}
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

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::size(void) const
{
	return (static_cast<size_type>(_end - _start));
}


/** Element access **/

/** Modifiers **/

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::push_back(const value_type & val)
{
	if (_end == _limit)
		_reallocate();
	_alloc.construct(_end, val);
	++_end;
}

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
	_start = _alloc.allocate(other.size());
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
	_construct_vector_with_val(static_cast<size_type>(n), val);
}

template <class T, class Alloc>
template <class InputIterator>
void
ft::vector<T, Alloc>::_construct_vector_dispatch(InputIterator & first, InputIterator & last, NO_INT_TYPE)
{
	_start = _alloc.allocate(static_cast<size_type>(last - first));
	int i = 0;
	while (first != last)
	{
		_alloc.construct(_start + i, *first);
		++first;
		++i;
	}
	_end = _limit = _start + i;
}

template <class T, class Alloc>
void
ft::vector<T, Alloc>::_construct_vector_with_val(size_type n, const value_type & val)
{
	_start = _alloc.allocate(n);
	for (size_type i = 0; i < n; ++i)
		_alloc.construct(_start + i, val);
	_end = _limit = _start + n;
}

template <class T, class Alloc>
void
ft::vector<T, Alloc>::_reallocate(void)
{
	//pointer tmp = _alloc.allocate(static_cast<size_type>())
}

/** Non-member function overloads **/

/* BaseIterator */
template <class T, class Alloc>
ft::vector<T, Alloc>::BaseIterator::BaseIterator(T * t)
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
ft::vector<T, Alloc>::Iterator::Iterator(T * t)
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