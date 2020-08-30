#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class List
	{
		public:
			/* Typedef */
			typedef T value_type;
			typedef std::allocator<value_type> allocator_type;
			typedef value_type & reference;
			typedef const value_type & const_reference;
			typedef value_type * pointer;
			typedef const value_type * const_pointer;
			typedef size_t size_type;

		public:
			/* Constructor */
			/** default	(1) **/	explicit List(const allocator_type & alloc = allocator_type());
			/** fill	(2) **/	explicit List(size_type n, const value_type & val = value_type(),
                							const allocator_type & alloc = allocator_type());			
			/** range	(3) **/	template <class InputIterator>
  								List(InputIterator first, InputIterator last,
         								const allocator_type & alloc = allocator_type());
			/** copy	(4) **/	List(List const & other);

			/* Destructor */
			virtual ~List(void);

			/* Operator */
			List<T, Alloc> &	operator=(List const & other);

			/* Public Functions */

		private:
			struct node
			{
				value_type		value;
				struct node *	next;
				node(void) : value(value_type()), node(NULL) {}
			};

			/* Private Functions */
			void						_copy(List const & other);

			allocator_type				_alloc;
			size_type					_size;
			node *						_head;
			node *						_tail;
			

	};
}

# include "List.tpp"
#endif