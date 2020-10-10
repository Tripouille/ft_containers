#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>
# include <limits>
# include <exception>
# include <cstddef>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
		
		public:
		/* Typedef */
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;

			typedef value_type & reference;
			typedef const value_type & const_reference;
			typedef value_type * pointer;
			typedef const value_type * const_pointer;
			
			class value_compare
			{
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

				protected:
					value_compare(Compare c = std::less<Key>()) : comp(c) {}
					~value_compare(void) {}
					value_compare(value_compare const & other) {static_cast<void>(other);}
					value_compare & operator=(value_compare const & other) {static_cast<void>(other); return (*this);}

					Compare comp;

				public:
					bool operator()(const value_type & x, const value_type & y) const {return comp(x.first, y.first);}
					
				friend class map;
			};

			//typedef typename ft::vector<T, Alloc>::Iterator iterator;
			//typedef typename ft::vector<T, Alloc>::CIterator const_iterator;
			//typedef typename ft::vector<T, Alloc>::RIterator reverse_iterator;
			//typedef typename ft::vector<T, Alloc>::CRIterator const_reverse_iterator;

			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

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