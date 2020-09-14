#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <limits>
# include <list>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class List
	{
		private:
		/* Private struct */
			struct node
			{
				T		value;
				node *	prev;
				node *	next;
				node(const T & v, node * p, node * n)
						: value(v), prev(p), next(n) {}
			};

		public:
		/* Typedef */
			typedef T value_type;
			typedef std::allocator<value_type> allocator_type;
			typedef std::allocator<node> node_allocator_type;
			typedef value_type & reference;
			typedef const value_type & const_reference;
			typedef value_type * pointer;
			typedef const value_type * const_pointer;
			typedef unsigned long size_type;

		public:

		/* Constructor */
			/** default	(1) **/	explicit List(const allocator_type & alloc = allocator_type());
			/** fill	(2) **/	explicit List(size_type n, const value_type & val = value_type(),
                											const allocator_type & alloc = allocator_type());
			/** range	(3) **/	/*template <class InputIterator>
												List(InputIterator first, InputIterator last,
														const allocator_type & alloc = allocator_type());*/
			/** copy	(4) **/	List(List const & other);

		/* Destructor */
			virtual ~List(void);

		/* Operator */
			List<T, Alloc> &			operator=(List const & other);

		/* Public functions */
			/** Iterator **/
			/** Capacity **/
				bool empty(void) const;
				size_type size(void) const;
				size_type max_size(void) const;
			/** Element access **/

			/** Modifiers **/
				/*** range (1) ***/	template <class InputIterator>
				 										void assign(InputIterator first, InputIterator last);
				/*** fill (2) ***/	void assign (size_type n, const value_type & val);
				void push_front(const value_type & val);
				void pop_front(void);
				void push_back(const value_type & val);
				void pop_back(void);

				void clear(void);
			/** Operations **/

		private:
		/* Private Functions */
			void _copy(List const & other);
			void _debug(void) const;
			node * _new_node(const T & v, node * p, node * n);

		/* Private variables */
			allocator_type					_alloc;
			node_allocator_type				_node_alloc;
			size_type						_size;
			node *							_head;
			node *							_tail;
	};
}

# include "List.tpp"
#endif