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
			typedef size_t size_type;

		public:
		/* Constructor */
			explicit stack(const container_type & ctnr = container_type());
			stack(const stack & other);
		
		/* Destructor */
			~stack(void);
		
		/* Operator */
			stack & operator=(const stack & other);

		/* Member functions */
			bool empty(void) const;
			size_type size(void) const;
			value_type & top(void);
			value_type const & top(void) const;
			void push(const value_type & val);
			void pop(void);

			/** Relational operators **/
			bool operator==(const stack & rhs) const;
			bool operator!=(const stack & rhs) const;
			bool operator<(const stack & rhs) const;
			bool operator<=(const stack & rhs) const;
			bool operator>(const stack & rhs) const;
			bool operator>=(const stack & rhs) const;

		private:
		/* Private variables */
			Container _c;
	};

	/* Non-member function overloads */
		/** Relational operators **/
		template<class T, class Container>
		bool operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs);
		template<class T, class Container>
		bool operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs);
		template<class T, class Container>
		bool operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs);
		template<class T, class Container>
		bool operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs);
		template<class T, class Container>
		bool operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs);
		template<class T, class Container>
		bool operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs);
}

# include "stack.tpp"
#endif