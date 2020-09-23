#include "vector.hpp"

/* Constructor */
/** default	(1) **/
template <typename T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type & alloc)
{
	(void)alloc;
}

/** fill		(2) **/
template <typename T, class Alloc>
ft::vector<T, Alloc>::vector(size_type n, const value_type & val,
										const allocator_type & alloc)
{
	(void)n;
	(void)val;
	(void)alloc;
}

/** range		(3) **/
template <typename T, class Alloc>
template <class InputIterator>
ft::vector<T, Alloc>::vector(InputIterator first, InputIterator last,
												const allocator_type & alloc)
{
	(void)first;
	(void)last;
	(void)alloc;
}

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

/** Non-member function overloads **/