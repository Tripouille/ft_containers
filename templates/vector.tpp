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
	_start = _alloc.allocate(other.size());
	_copy(other);
	_limit = _end;
}

/* Destructor */
template <class T, class Alloc>
ft::vector<T, Alloc>::~vector(void)
{
	clear();
	_alloc.deallocate(_start, capacity());
}

/* Operator */
template <class T, class Alloc>
ft::vector<T, Alloc> &
ft::vector<T, Alloc>::operator=(vector const & other)
{
	if (this != &other)
	{
		if (other.size() > capacity())
			_reallocate(other.size());
		else
			clear();
		_copy(other);
	}
	return (*this);
}

/* Public functions */
/** Iterators **/
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

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator
ft::vector<T, Alloc>::rbegin(void)
{
	return (reverse_iterator(_end - 1));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator
ft::vector<T, Alloc>::rbegin(void) const
{
	return (const_reverse_iterator(_end - 1));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator
ft::vector<T, Alloc>::rend(void)
{
	return (reverse_iterator(_start - 1));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator
ft::vector<T, Alloc>::rend(void) const
{
	return (const_reverse_iterator(_start - 1));
}

/** Capacity **/

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

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::resize(size_type n, value_type val)
{
	if (n > capacity())
		_reallocate(n, true);
	while (n > size())
	{
		_alloc.construct(_end, val);
		++_end;
	}
	while (n < size())
	{
		--_end;
		_alloc.destroy(_end);
	}
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::size_type
ft::vector<T, Alloc>::capacity(void) const
{
	return (static_cast<size_type>(_limit - _start));
}

template <typename T, class Alloc>
bool
ft::vector<T, Alloc>::empty(void) const
{
	return (_start == _end);
}

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::reserve(size_type n)
{
	if (n > capacity())
		_reallocate(n);
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

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::reference
ft::vector<T, Alloc>::front(void)
{
	return (*_start);
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::const_reference
ft::vector<T, Alloc>::front(void) const
{
	return (*_start);
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::reference
ft::vector<T, Alloc>::back(void)
{
	return (_end[-1]);
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::const_reference
ft::vector<T, Alloc>::back(void) const
{
	return (_end[-1]);
}

/** Modifiers **/

/*** range (1) ***/
template <typename T, class Alloc>
template <class InputIterator>
void
ft::vector<T, Alloc>::assign(InputIterator first, InputIterator last)
{
	vector tmp(first, last);
	*this = tmp; //ou swap(tmp) ?
}

/*** fill (2) ***/
template <typename T, class Alloc>
void
ft::vector<T, Alloc>::assign(size_type n, const value_type & val)
{
	vector tmp(n, val);
	*this = tmp;
}

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::push_back(const value_type & val)
{
	if (_end == _limit)
		_reallocate(size() + 1, true);
	_alloc.construct(_end, val);
	++_end;
}

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::pop_back(void)
{
	--_end;
	_alloc.destroy(_end);
}

/*** single element (1) ***/
template <typename T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::insert(iterator position, const value_type & val)
{
	difference_type position_index = position.get_target() - _start;
	if (_limit == _end)
	{
		_reallocate(size() + 1, true);
		position = iterator(_start + position_index);
	}
	memmove(position.get_target() + 1, position.get_target(),
		static_cast<unsigned long>((_end - position.get_target())) * sizeof(T));
	_alloc.construct(position.get_target(), val);
	++_end;
	return (position);
}

/*** fill (2) ***/
template <typename T, class Alloc>
void
ft::vector<T, Alloc>::insert(iterator position, size_type n, const value_type & val)
{
	difference_type position_index = position.get_target() - _start;
	if (size() + n > capacity())
	{
		_reallocate(size() + n, true);
		position = iterator(_start + position_index);
	}
	memmove(position.get_target() + n, position.get_target(),
		static_cast<unsigned long>((_end - position.get_target())) * sizeof(T));
	for (size_type i = 0; i < n; i++)
		_alloc.construct(position.get_target() + i, val);
	_end += n;
}

/*** range (3) ***/
template <typename T, class Alloc>
template <class InputIterator>
void
ft::vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
{
	vector tmp(first, last);
	size_type n = tmp.size();
	difference_type position_index = position.get_target() - _start;
	if (size() + n > capacity())
	{
		_reallocate(size() + n, true);
		position = iterator(_start + position_index);
	}
	memmove(position.get_target() + n, position.get_target(),
		static_cast<unsigned long>((_end - position.get_target())) * sizeof(T));
	const_iterator it = tmp.begin();
	const_iterator ite = tmp.end();
	size_type i = 0;
	while (it != ite)
	{
		_alloc.construct(position.get_target() + i, *it);
		++i;
		++it;
	}
	_end += n;
}

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::swap(vector & x)
{
	if (this != &x)
	{
		std::swap(_start, x._start);
		std::swap(_end, x._end);
		std::swap(_limit, x._limit);
	}
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::erase(iterator position)
{
	return (erase(position, position + 1));
}

template <typename T, class Alloc>
typename ft::vector<T, Alloc>::iterator
ft::vector<T, Alloc>::erase(iterator first, iterator last)
{
	ptrdiff_t delta = last - first;
	iterator start = first;
	while (first != last)
	{
		_alloc.destroy(&*first);
		if (first + delta < _end)
			_alloc.construct(&*first, first[delta]);
		++first;
	}
	if (_end - &*last - delta > 0)
		memmove(&*last, &last[delta], static_cast<size_t>(_end - &*last - delta) * sizeof(value_type));
	_end -= delta;
	return (start);
}

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::clear(void)
{
	for (pointer tmp = _start; tmp != _end; ++tmp)
		_alloc.destroy(tmp);
	_end = _start;
}

/** Observers **/

template <class T, class Alloc>
typename ft::vector<T, Alloc>::allocator_type
ft::vector<T, Alloc>::get_allocator(void) const
{
	return (_alloc);
}


/** Private functions **/

template <typename T, class Alloc>
void
ft::vector<T, Alloc>::_copy(vector const & other)
{
	pointer this_ptr = _start;
	pointer other_ptr = other._start;
	while (other_ptr != other._end)
	{
		_alloc.construct(this_ptr, *other_ptr);
		++this_ptr;
		++other_ptr;
	}
	_end = this_ptr;
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
ft::vector<T, Alloc>::_reallocate(size_type n, bool anticipate_place)
{
	size_type vec_size = size();
	size_type new_capacity = n;
	if (anticipate_place && 2 * vec_size >= n && 2 * vec_size >= vec_size)
		new_capacity = 2 * vec_size;
	pointer new_start = _alloc.allocate(new_capacity);
	for (size_type i = 0; i < vec_size; ++i)
		_alloc.construct(new_start + i, _start[i]);
	clear();
	_alloc.deallocate(_start, capacity());
	_start = new_start;
	_end = _start + vec_size;
	_limit = _start + new_capacity;
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

/* Non-member function overloads */

template <class T, class Alloc>
bool
ft::operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	typename ft::vector<T, Alloc>::const_iterator lhs_it = lhs.begin();
	typename ft::vector<T, Alloc>::const_iterator lhs_ite = lhs.end();
	typename ft::vector<T, Alloc>::const_iterator rhs_it = rhs.begin();
	while (lhs_it != lhs_ite)
	{
		if (!(*lhs_it == *rhs_it))
			return (false);
		++lhs_it;
		++rhs_it;
	}
	return (true);
}

template <class T, class Alloc>
bool
ft::operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool
ft::operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
	typename ft::vector<T, Alloc>::const_iterator lhs_it = lhs.begin();
	typename ft::vector<T, Alloc>::const_iterator lhs_ite = lhs.end();
	typename ft::vector<T, Alloc>::const_iterator rhs_it = rhs.begin();
	typename ft::vector<T, Alloc>::const_iterator rhs_ite = rhs.end();
	while (lhs_it != lhs_ite)
	{
		if (rhs_it == rhs_ite || *rhs_it < *lhs_it)
			return (false);
		else if (*lhs_it < *rhs_it)
			return (true);
		++lhs_it;
		++rhs_it;
	}
	return (rhs_it != rhs_ite);
}

template <class T, class Alloc>
bool
ft::operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool
ft::operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool
ft::operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
	return (!(lhs < rhs));
}

template <class T, class Alloc>
void
ft::swap(ft::vector<T, Alloc> & x, ft::vector<T, Alloc> & y)
{
	x.swap(y);
}


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
	_target = other.get_target();
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator==(BaseIterator const & other) const
{
	return (_target == other.get_target());
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator!=(BaseIterator const & other) const
{
	return (_target != other.get_target());
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator<(BaseIterator const & other) const
{
	return (_target < other.get_target());
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator>(BaseIterator const & other) const
{
	return (_target > other.get_target());
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator<=(BaseIterator const & other) const
{
	return (_target <= other.get_target());
}

template <class T, class Alloc>
bool
ft::vector<T, Alloc>::BaseIterator::operator>=(BaseIterator const & other) const
{
	return (_target >= other.get_target());
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
	return (this->_target - other.get_target());
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
	return (this->_target[i]);
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
	return (this->_target - other.get_target());
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
	return (this->_target[i]);
}

/* RIterator */
template <class T, class Alloc>
ft::vector<T, Alloc>::RIterator::RIterator(T * t)
						: BaseIterator(t)
{
}

template <class T, class Alloc>
ft::vector<T, Alloc>::RIterator::~RIterator(void)
{
}


template <class T, class Alloc>
ft::vector<T, Alloc>::RIterator::RIterator(RIterator const & other)
						 : BaseIterator(other)
{
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator &
ft::vector<T, Alloc>::RIterator::operator=(RIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T, class Alloc>
T &
ft::vector<T, Alloc>::RIterator::operator*(void) const
{
	return (*(this->_target));
}

template <class T, class Alloc>
T *
ft::vector<T, Alloc>::RIterator::operator->(void) const
{
	return (this->_target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator &
ft::vector<T, Alloc>::RIterator::operator++(void)
{
	--this->_target;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator
ft::vector<T, Alloc>::RIterator::operator++(int)
{
	RIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator &
ft::vector<T, Alloc>::RIterator::operator--(void)
{
	++this->_target;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator
ft::vector<T, Alloc>::RIterator::operator--(int)
{
	RIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator
ft::vector<T, Alloc>::RIterator::operator+(typename RIterator::difference_type i) const
{
	return (RIterator(this->_target - i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator
ft::vector<T, Alloc>::RIterator::operator-(typename RIterator::difference_type i) const
{
	return (RIterator(this->_target + i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator::difference_type
ft::vector<T, Alloc>::RIterator::operator-(RIterator const & other) const
{
	return (other.get_target() - this->_target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator &
ft::vector<T, Alloc>::RIterator::operator+=(typename RIterator::difference_type i)
{
	this->_target -= i;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::RIterator &
ft::vector<T, Alloc>::RIterator::operator-=(typename RIterator::difference_type i)
{
	this->_target += i;
	return (*this);
}

template <class T, class Alloc>
T &
ft::vector<T, Alloc>::RIterator::operator[](typename RIterator::difference_type i) const
{
	return (this->_target[-i]);
}

/* CRIterator */
template <class T, class Alloc>
ft::vector<T, Alloc>::CRIterator::CRIterator(T * t)
						: BaseIterator(t)
{
}

template <class T, class Alloc>
ft::vector<T, Alloc>::CRIterator::CRIterator(RIterator const & rit)
					 : BaseIterator(rit)
{
}

template <class T, class Alloc>
ft::vector<T, Alloc>::CRIterator::~CRIterator(void)
{
}


template <class T, class Alloc>
ft::vector<T, Alloc>::CRIterator::CRIterator(CRIterator const & other)
						 : BaseIterator(other)
{
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator &
ft::vector<T, Alloc>::CRIterator::operator=(CRIterator const & other)
{
	if (this != &other)
		BaseIterator::operator=(other);
	return (*this);
}

template <class T, class Alloc>
T const &
ft::vector<T, Alloc>::CRIterator::operator*(void) const
{
	return (*(this->_target));
}

template <class T, class Alloc>
T const *
ft::vector<T, Alloc>::CRIterator::operator->(void) const
{
	return (this->_target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator &
ft::vector<T, Alloc>::CRIterator::operator++(void)
{
	--this->_target;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator
ft::vector<T, Alloc>::CRIterator::operator++(int)
{
	CRIterator tmp(*this);
	++*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator &
ft::vector<T, Alloc>::CRIterator::operator--(void)
{
	++this->_target;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator
ft::vector<T, Alloc>::CRIterator::operator--(int)
{
	CRIterator tmp(*this);
	--*this;
	return (tmp);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator
ft::vector<T, Alloc>::CRIterator::operator+(typename CRIterator::difference_type i) const
{
	return (CRIterator(this->_target - i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator
ft::vector<T, Alloc>::CRIterator::operator-(typename CRIterator::difference_type i) const
{
	return (CRIterator(this->_target + i));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator::difference_type
ft::vector<T, Alloc>::CRIterator::operator-(CRIterator const & other) const
{
	return (other.get_target() - this->_target);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator &
ft::vector<T, Alloc>::CRIterator::operator+=(typename CRIterator::difference_type i)
{
	this->_target -= i;
	return (*this);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::CRIterator &
ft::vector<T, Alloc>::CRIterator::operator-=(typename CRIterator::difference_type i)
{
	this->_target += i;
	return (*this);
}

template <class T, class Alloc>
T const &
ft::vector<T, Alloc>::CRIterator::operator[](typename CRIterator::difference_type i) const
{
	return (this->_target[-i]);
}