#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <limits>
# include <cstddef>
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
			typedef Alloc allocator_type;
			typedef value_type & reference;
			typedef const value_type & const_reference;
			typedef value_type * pointer;
			typedef const value_type * const_pointer;
			typedef typename ft::DLNode<T, Alloc>::iterator iterator;
			typedef typename ft::DLNode<T, Alloc>::const_iterator const_iterator;
			typedef typename ft::DLNode<T, Alloc>::reverse_iterator reverse_iterator;
			typedef typename ft::DLNode<T, Alloc>::const_reverse_iterator const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		private:
		/* Typedef */
			typedef typename Alloc::template rebind<DLNode<T, Alloc> >::other node_allocator_type;

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
			~list(void);

		/* Operator */
			list<T, Alloc> &			operator=(list const & other);

		/* Member functions */
			/** Iterators **/
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
											void insert(iterator position,
															InputIterator first,
															InputIterator last);
				iterator erase(iterator position);
				iterator erase(iterator first, iterator last);
				void swap(list & x);
				void resize(size_type n, value_type val = value_type());
				void clear(void);

			/** Operations **/
				/*** entire list (1) ***/ void splice(iterator position, list & x);
				/*** single element (2)	***/ void splice(iterator position, list & x, iterator i);
				/*** element range (3) ***/ void splice(iterator position, list & x, iterator first, iterator last);
				void remove(const value_type & val);
				template <class Predicate>
				void remove_if(Predicate pred);
				void unique();
				template <class BinaryPredicate>
				void unique(BinaryPredicate binary_pred);
				void merge(list & x);
				template <class Compare>
				void merge(list & x, Compare comp);
				/*** (1) ***/ void sort(void);
				/*** (2) ***/ template <class Compare>
							  void sort(Compare comp);
				void reverse(void);

			/** Observers **/
				allocator_type get_allocator(void) const;

		private:
		/* Private Functions */
			void _copy(list const & other);
			DLNode<T, Alloc> * _new_node(const T & v, DLNode<T, Alloc> * p, DLNode<T, Alloc> * n);
			template <class Integer>
			void _fill_list_dispatch(Integer & first, Integer & last, INT_TYPE);
			template <class InputIterator>
			void _fill_list_dispatch(InputIterator & first, InputIterator & last, NO_INT_TYPE);
			void _fill_with_value(size_type n, value_type const & val);
			template <class InputIterator>
			void _fill_from_iterators(InputIterator & first, InputIterator & last);
			void _actualize_end(void);
			void _actualize_head_tail(void);
			void _swap(const_iterator a, const_iterator b);
			/** Iterator utils **/
			static typename ft::list<T, Alloc>::const_iterator::difference_type _distance(const_iterator first, const_iterator last);

		/* Private variables */
			allocator_type					_alloc;
			node_allocator_type				_node_alloc;
			size_type						_size;
			DLNode<T, Alloc> *				_head;
			DLNode<T, Alloc> *				_tail;
			DLNode<T, Alloc> *				_end;
	};

	/* Non-member function overloads */
		/** Relational operators **/
			template <class T, class Alloc>
			bool operator==(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator!=(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator<(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator<=(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator>(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator>=(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs);

		/** swap **/
			template <class T, class Alloc>
			void swap(list<T, Alloc> & x, list<T, Alloc> & y);
}

# include "list.tpp"
#endif