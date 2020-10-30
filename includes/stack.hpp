#ifndef STACK_HPP
# define STACK_HPP
# include <iostream>
# include <limits>
# include <exception>
# include <cstddef>
# include <cstring>
# include <deque>
# include "types.hpp"

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:
		/* Typedef */
			typedef T value_type;
			typedef Container container_type;
			//typedef value_type & reference;
			//typedef const value_type & const_reference;
			//typedef value_type * pointer;
			//typedef const value_type * const_pointer;
			//typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		public:
		/* Constructor */

		/* Member functions */

		private:
		/* Private Functions */

		/* Private variables */
	};

	/* Non-member function overloads */
		/** Relational operators **/

		/** swap **/
	
	/* Non-member class specializations */
}

# include "stack.tpp"
#endif