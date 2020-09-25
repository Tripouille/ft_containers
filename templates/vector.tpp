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
	_alloc.deallocate(_start, size());
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
typename ft::vector<T, Alloc>::const_iterator
ft::vector<T, Alloc>::begin(void) const
{
	return (const_iterator(_start));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::end(void)
{
	return (iterator(_end));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator
ft::vector<T, Alloc>::end(void) const
{
	return (const_iterator(_end));
}

/** Capacity **/

template <typename T, class Alloc>
bool
ft::vector<T, Alloc>::empty(void) const
{
	return (_start == _end);
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::size(void) const
{
	return (static_cast<size_type>(_end - _start));
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::max_size(void) const
{
	return (_alloc.max_size());
}


/** Element access **/
template <typename T, class Alloc>
typename ft::vector<T, Alloc>::reference
ft::vector<T, Alloc>::operator[](size_type n)
{
	return (_start[n]);
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::const_reference
ft::vector<T, Alloc>::operator[] (size_type n) const
{
	return (_start[n]);
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::reference
ft::vector<T, Alloc>::at(size_type n)
{
	_range_check(n);
	return (_start[n]);
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::const_reference
ft::vector<T, Alloc>::at(size_type n) const
{
	_range_check(n);
	return (_start[n]);
}

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
	_alloc.deallocate(_start, size());
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
	_construct_vector_from_range(first, last);
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
template <class InputIterator>
void
ft::vector<T, Alloc>::_construct_vector_from_range(InputIterator & first, InputIterator & last)
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
ft::vector<T, Alloc>::_reallocate(void)
{
	pointer tmp = _start;
	size_type prev_size = size();
	size_type new_size = prev_size + 10;
	_start = _alloc.allocate(new_size);
	for (size_type i = 0; i < prev_size; ++i)
		_alloc.construct(_start + i, tmp[i]);
	_end = _start + prev_size;
	_limit = _start + new_size;
	_alloc.deallocate(tmp, prev_size);
}

template <class T, class Alloc>
void
ft::vector<T, Alloc>::_range_check(size_type n) const
throw(std::out_of_range)
{
	if (n < size())
		return ;
	std::stringstream msg;
	msg << "vector::_M_range_check: __n (which is " << n
		<< ") >= this->size() (which is " << size() << ")";
	throw std::out_of_range(msg.str());
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
	return (*(this->_target));
}

template <class T, class Alloc>
T *
ft::vector<T, Alloc>::Iterator::operator->(void) const
{
	return (this->_target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator &
ft::vector<T, Alloc>::Iterator::operator++(void)
{
	++this->_target;
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
	--this->_target;
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
ft::vector<T, Alloc>::Iterator::operator+(typename Iterator::difference_type i) const
{
	return (Iterator(this->_target + i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator
ft::vector<T, Alloc>::Iterator::operator-(typename Iterator::difference_type i) const
{
	return (Iterator(this->_target - i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator::difference_type
ft::vector<T, Alloc>::Iterator::operator-(Iterator const & other) const
{
	return (this->_target - other._target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator &
ft::vector<T, Alloc>::Iterator::operator+=(typename Iterator::difference_type i)
{
	this->_target += i;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::Iterator &
ft::vector<T, Alloc>::Iterator::operator-=(typename Iterator::difference_type i)
{
	this->_target -= i;
	return (*this);
}

template <class T, class Alloc>
T &
ft::vector<T, Alloc>::Iterator::operator[](typename Iterator::difference_type i) const
{
	return (*(this->_target + i));
}


/* CIterator */
template <class T, class Alloc>
ft::vector<T, Alloc>::CIterator::CIterator(T * t)
						: BaseIterator(t)
{
}

template <class T, class Alloc>
ft::vector<T, Alloc>::CIterator::CIterator(Iterator const & it)
						 : BaseIterator(it)
{
}

template <class T, class Alloc>
ft::vector<T, Alloc>::CIterator::~CIterator(void)
{
}

template <class T, class Alloc>
ft::vector<T, Alloc>::CIterator::CIterator(CIterator const & other)
						 : BaseIterator(other)
{
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator &
ft::vector<T, Alloc>::CIterator::operator=(CIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T, class Alloc>
T const &
ft::vector<T, Alloc>::CIterator::operator*(void) const
{
	return (*(this->_target));
}

template <class T, class Alloc>
T const *
ft::vector<T, Alloc>::CIterator::operator->(void) const
{
	return (this->_target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator &
ft::vector<T, Alloc>::CIterator::operator++(void)
{
	++this->_target;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator
ft::vector<T, Alloc>::CIterator::operator++(int)
{
	CIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator &
ft::vector<T, Alloc>::CIterator::operator--(void)
{
	--this->_target;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator
ft::vector<T, Alloc>::CIterator::operator--(int)
{
	CIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator
ft::vector<T, Alloc>::CIterator::operator+(typename CIterator::difference_type i) const
{
	return (CIterator(this->_target + i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator
ft::vector<T, Alloc>::CIterator::operator-(typename CIterator::difference_type i) const
{
	return (CIterator(this->_target - i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator::difference_type
ft::vector<T, Alloc>::CIterator::operator-(CIterator const & other) const
{
	return (this->_target - other._target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator &
ft::vector<T, Alloc>::CIterator::operator+=(typename CIterator::difference_type i)
{
	this->_target += i;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CIterator &
ft::vector<T, Alloc>::CIterator::operator-=(typename CIterator::difference_type i)
{
	this->_target -= i;
	return (*this);
}

template <class T, class Alloc>
T const &
ft::vector<T, Alloc>::CIterator::operator[](typename CIterator::difference_type i) const
{
	return (*(this->_target + i));
}

