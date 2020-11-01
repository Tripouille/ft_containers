#ifndef QUEUE_HPP
# define QUEUE_HPP
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
	class queue
	{
		public:
		/* Typedef */
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

		public:
		/* Constructor */
			explicit queue(const container_type & ctnr = container_type());
			queue(const queue & other);
		
		/* Destructor */
			~queue(void);
		
		/* Operator */
			queue & operator=(const queue & other);

		/* Member functions */
			bool empty(void) const;
			size_type size(void) const;
			value_type & front(void);
			value_type const & front(void) const;
			value_type & back(void);
			value_type const & back(void) const;
			void push(const value_type & val);
			void pop(void);

			/** Relational operators **/
			bool operator==(const queue & rhs) const;
			bool operator!=(const queue & rhs) const;
			bool operator<(const queue & rhs) const;
			bool operator<=(const queue & rhs) const;
			bool operator>(const queue & rhs) const;
			bool operator>=(const queue & rhs) const;

		private:
		/* Private variables */
			Container _c;
	};

	/* Non-member function overloads */
		/** Relational operators **/
		template<class T, class Container>
		bool operator==(const queue<T, Container> & lhs, const queue<T, Container> & rhs);
		template<class T, class Container>
		bool operator!=(const queue<T, Container> & lhs, const queue<T, Container> & rhs);
		template<class T, class Container>
		bool operator<(const queue<T, Container> & lhs, const queue<T, Container> & rhs);
		template<class T, class Container>
		bool operator<=(const queue<T, Container> & lhs, const queue<T, Container> & rhs);
		template<class T, class Container>
		bool operator>(const queue<T, Container> & lhs, const queue<T, Container> & rhs);
		template<class T, class Container>
		bool operator>=(const queue<T, Container> & lhs, const queue<T, Container> & rhs);
}

# include "queue.tpp"
#endif