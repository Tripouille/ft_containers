#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <limits>
# include "DLNode.hpp"
# include "types.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class list
	{
		public:
		/* Typedef */
			typedef T value_type;
			typedef std::allocator<value_type> allocator_type;
			typedef std::allocator<DLNode<T> > node_allocator_type;
			typedef value_type & reference;
			typedef const value_type & const_reference;
			typedef value_type * pointer;
			typedef const value_type * const_pointer;
			typedef unsigned long size_type;
			typedef typename ft::DLNode<T>::iterator iterator;
			typedef typename ft::DLNode<T>::const_iterator const_iterator;
			typedef typename ft::DLNode<T>::reverse_iterator reverse_iterator;
			typedef typename ft::DLNode<T>::const_reverse_iterator const_reverse_iterator;

		public:
		/* Constructor */
			/** default	(1) **/	explicit list(const allocator_type & alloc = allocator_type());
			/** fill	(2) **/	explicit list(size_type n, const value_type & val = value_type(),
															const allocator_type & alloc = allocator_type());
			/** range	(3) **/	template <class InputIterator>
								list(InputIterator first, InputIterator last,
															const allocator_type & alloc = allocator_type());
			/** copy	(4) **/	list(list const & other);

		/* Destructor */
			virtual ~list(void);

		/* Operator */
			list<T, Alloc> &			operator=(list const & other);

		/* Public functions */
			/** Iterator **/
				iterator begin(void);
				const_iterator begin(void) const;
				iterator end(void);
				const_iterator end(void) const;
				reverse_iterator rbegin(void);
				const_reverse_iterator rbegin(void) const;
				reverse_iterator rend(void);
				const_reverse_iterator rend(void) const;
			/** Capacity **/
				bool empty(void) const;
				size_type size(void) const;
				size_type max_size(void) const;
			/** Element access **/
				reference front(void);
				const_reference front(void) const;
				reference back(void);
				const_reference back(void) const;

			/** Modifiers **/
				/*** range (1) ***/	template <class InputIterator>
				 					void assign(InputIterator first, InputIterator last);
				/*** fill (2) ***/	void assign (size_type n, const value_type & val);
				void push_front(const value_type & val);
				void pop_front(void);
				void push_back(const value_type & val);
				void pop_back(void);
				/*** single element (1) ***/iterator insert(iterator position,
															const value_type & val);
				/*** fill (2) ***/			void insert(iterator position,
														size_type n,
														const value_type & val);
				/*** range (3) ***/			template <class InputIterator>
											iterator insert(iterator position,
															InputIterator first,
															InputIterator last);

				void swap(list & x);

				void clear(void);
			/** Operations **/

		private:
		/* Private Functions */
			void _copy(list const & other);
			void _debug(void) const;
			DLNode<T> * _new_node(const T & v, DLNode<T> * p, DLNode<T> * n);
			template <class Integer>
			void _fill_list_dispatch(Integer & first, Integer & last, INT_TYPE);
			template <class InputIterator>
			void _fill_list_dispatch(InputIterator & first, InputIterator & last, NO_INT_TYPE);
			void _fill_with_value(size_type n, T const & val);
			template <class InputIterator>
			void _fill_from_iterators(InputIterator & first, InputIterator & last);
			void _actualize_end(void);


		/* Private variables */
			allocator_type			_alloc;
			node_allocator_type		_node_alloc;
			size_type				_size;
			DLNode<T> *				_head;
			DLNode<T> *				_tail;
			DLNode<T> *				_end;
	};
}

# include "list.tpp"
#endif