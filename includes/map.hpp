#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>
# include <limits>
# include <exception>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
		/* Typedef */
			//typedef T value_type;
			//typedef Alloc allocator_type;
			//typedef value_type & reference;
			//typedef const value_type & const_reference;
			//typedef value_type * pointer;
			//typedef const value_type * const_pointer;
			//typedef typename ft::vector<T, Alloc>::Iterator iterator;
			//typedef typename ft::vector<T, Alloc>::CIterator const_iterator;
			//typedef typename ft::vector<T, Alloc>::RIterator reverse_iterator;
			//typedef typename ft::vector<T, Alloc>::CRIterator const_reverse_iterator;
			//typedef ptrdiff_t difference_type;
			//typedef size_t size_type;

		public:
		/* Constructor */
			/** empty	(1) **/
			/** range	(2) **/
			/** copy	(3) **/

		/* Destructor */

		/* Operator */

		/* Member functions */
			/** Iterators **/

			/** Capacity **/

			/** Element access **/

			/** Modifiers **/

			/** Observers **/

			/** Operations **/

			/** Allocator **/

		private:
		/* Private Functions */

		/* Private variables */
	};
}

# include "map.tpp"
#endif