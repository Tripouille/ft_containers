#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <sstream>
# include <limits>
# include <exception>
# include <cstddef>
# include "types.hpp"

namespace ft
{
	template <class T, class Alloc>
	class vector
	{

		struct random_access_iterator_tag {};
		class BaseIterator
		{
			public:
				typedef T value_type;
				typedef ptrdiff_t difference_type;
				typedef T * pointer;
				typedef T & reference;
				typedef random_access_iterator_tag iterator_category;

				BaseIterator(T * t = NULL);
				virtual ~BaseIterator(void);
				BaseIterator(BaseIterator const & other);

				BaseIterator &		operator=(BaseIterator const & other);
				bool				operator==(BaseIterator const & other) const;
				bool				operator!=(BaseIterator const & other) const;
				bool				operator<(BaseIterator const & other) const;
				bool				operator>(BaseIterator const & other) const;
				bool				operator<=(BaseIterator const & other) const;
				bool				operator>=(BaseIterator const & other) const;

			protected:
				void				_copy(BaseIterator const & other);
				T *					_target;
		};

		class Iterator : public BaseIterator
		{
			public:
				Iterator(T * t = NULL);
				~Iterator(void);
				Iterator(Iterator const & other);

				Iterator &			operator=(Iterator const & other);
				T &					operator*(void) const;
				T *					operator->(void) const;
				Iterator &			operator++(void);
				Iterator			operator++(int);
				Iterator &			operator--(void);
				Iterator			operator--(int);
				Iterator 			operator+(typename Iterator::difference_type i) const;
		 friend Iterator			operator+(typename Iterator::difference_type i, Iterator const & it)
									{return (Iterator(it._target + i));}
				Iterator 			operator-(typename Iterator::difference_type i) const;
				typename Iterator::difference_type
									operator-(Iterator const & other) const;
				Iterator &			operator+=(typename Iterator::difference_type i);
				Iterator &			operator-=(typename Iterator::difference_type i);
				T &					operator[](typename Iterator::difference_type i) const;
		};

		class CIterator : public BaseIterator
		{
			public:
				CIterator(T * t = NULL);
				CIterator(Iterator const & it);
				~CIterator(void);
				CIterator(CIterator const & other);

				CIterator &			operator=(CIterator const & other);
				T const &			operator*(void) const;
				T const *			operator->(void) const;
				CIterator &			operator++(void);
				CIterator			operator++(int);
				CIterator &			operator--(void);
				CIterator			operator--(int);
				CIterator 			operator+(typename CIterator::difference_type i) const;
		 friend CIterator			operator+(typename CIterator::difference_type i, CIterator const & cit)
									{return (CIterator(cit._target + i));}
				CIterator 			operator-(typename CIterator::difference_type i) const;
				typename CIterator::difference_type
									operator-(CIterator const & other) const;
				CIterator &			operator+=(typename CIterator::difference_type i);
				CIterator &			operator-=(typename CIterator::difference_type i);
				T const &					operator[](typename CIterator::difference_type i) const;
		};

		class RIterator : public BaseIterator
		{
			public:
				RIterator(T * t = NULL);
				~RIterator(void);
				RIterator(RIterator const & other);

				RIterator &			operator=(RIterator const & other);
				T &					operator*(void) const;
				T *					operator->(void) const;
				RIterator &			operator++(void);
				RIterator			operator++(int);
				RIterator &			operator--(void);
				RIterator			operator--(int);
				RIterator 			operator+(typename RIterator::difference_type i) const;
		 friend RIterator			operator+(typename RIterator::difference_type i, RIterator const & it)
									{return (RIterator(it._target - i));}
				RIterator 			operator-(typename RIterator::difference_type i) const;
				typename RIterator::difference_type
									operator-(RIterator const & other) const;
				RIterator &			operator+=(typename RIterator::difference_type i);
				RIterator &			operator-=(typename RIterator::difference_type i);
				T &					operator[](typename RIterator::difference_type i) const;
		};

		public:
		/* Typedef */
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type & reference;
			typedef const value_type & const_reference;
			typedef value_type * pointer;
			typedef const value_type * const_pointer;
			typedef typename ft::vector<T, Alloc>::Iterator iterator;
			typedef typename ft::vector<T, Alloc>::CIterator const_iterator;
			typedef typename ft::vector<T, Alloc>::RIterator reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		public:
		/* Constructor */
			/** default	(1) **/	explicit vector(const allocator_type & alloc = allocator_type());
			/** fill	(2) **/	explicit vector(size_type n, const value_type & val = value_type(),
															const allocator_type & alloc = allocator_type());
			/** range	(3) **/	template <class InputIterator>
								vector(InputIterator first, InputIterator last,
															const allocator_type & alloc = allocator_type());
			/** copy	(4) **/	vector(vector const & other);

		/* Destructor */
			virtual ~vector(void);

		/* Operator */
			vector<T, Alloc> &			operator=(vector const & other);

		/* Member functions */
			/** Iterators **/
				iterator begin(void);
				const_iterator begin(void) const;
				iterator end(void);
				const_iterator end(void) const;
				reverse_iterator rbegin(void);
				reverse_iterator rend(void);
				/*
				const_reverse_iterator rbegin(void) const;
				const_reverse_iterator rend(void) const;*/

			/** Capacity **/
				size_type size(void) const;
				size_type max_size(void) const;
				void resize(size_type n, value_type val = value_type());
				size_type capacity(void) const;
				bool empty(void) const;
				void reserve(size_type n);

			/** Element access **/
			 	reference operator[](size_type n);
				const_reference operator[] (size_type n) const;
				reference at(size_type n);
				const_reference at(size_type n) const;
				/*reference front(void);
				const_reference front(void) const;
				reference back(void);
				const_reference back(void) const;*/

			/** Modifiers **/
				/*** range (1) ***/	/*template <class InputIterator>
				 					void assign(InputIterator first, InputIterator last);*/
				/*** fill (2) ***/	//void assign (size_type n, const value_type & val);
				//void push_front(const value_type & val);
				//void pop_front(void);
				void push_back(const value_type & val);
				//void pop_back(void);
				/*** single element (1) ***//*iterator insert(iterator position,
															const value_type & val);*/
				/*** fill (2) ***/			/*void insert(iterator position,
														size_type n,
														const value_type & val);*/
				/*** range (3) ***/			/*template <class InputIterator>
											void insert(iterator position,
															InputIterator first,
															InputIterator last);*/
				//iterator erase(iterator position);
				//iterator erase(iterator first, iterator last);
				//void swap(list & x);
				//void resize(size_type n, value_type val = value_type());
				void clear(void);

			/** Operations **/
				/*** entire list (1) ***/ //void splice(iterator position, list & x);
				/*** single element (2)	***/ //void splice(iterator position, list & x, iterator i);
				/*** element range (3) ***/ //void splice(iterator position, list & x, iterator first, iterator last);
				/*void remove(const value_type & val);
				template <class Predicate>
				void remove_if(Predicate pred);
				void unique();
				template <class BinaryPredicate>
				void unique(BinaryPredicate binary_pred);
				void merge(list & x);
				template <class Compare>
				void merge(list & x, Compare comp);*/
				/*** (1) ***/ //void sort(void);
				/*** (2) ***/ /*template <class Compare>
							  void sort(Compare comp);
				void reverse(void);*/

			/** Observers **/
				allocator_type get_allocator(void) const;

		private:
		/* Private Functions */
			void _copy(vector const & other);
			//void _debug(void) const;
			//DLNode<T> * _new_node(const T & v, DLNode<T> * p, DLNode<T> * n);
			template <class Integer>
			void _construct_vector_dispatch(Integer & first, Integer & last, INT_TYPE);
			template <class InputIterator>
			void _construct_vector_dispatch(InputIterator & first, InputIterator & last, NO_INT_TYPE);
			void _construct_vector_with_val(size_type n, value_type const & val);
			template <class InputIterator>
			void _construct_vector_from_range(InputIterator & first, InputIterator & last);
			void _reallocate(size_type n);
			void _range_check(size_type n) const throw(std::out_of_range);
			//template <class InputIterator>
			//void _fill_from_iterators(InputIterator & first, InputIterator & last);
			//void _actualize_end(void);
			//void _actualize_head_tail(void);
			//void _swap(const_iterator a, const_iterator b);

		/* Private variables */
			allocator_type			_alloc;
			pointer					_start;
			pointer					_end;
			pointer					_limit;
	};

	/* Non-member function overloads */
		/** Relational operators **/
			/*template <class T, class Alloc>
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
			bool operator>=(const list<T, Alloc> & lhs, const list<T, Alloc> & rhs);*/

		/** swap **/
			/*template <class T, class Alloc>
			void swap(list<T, Alloc> & x, list<T, Alloc> & y);*/

	/* Non-member function for iterator */
		/*template <class T, class Alloc>
		typename ft::vector<T, Alloc>::Iterator::difference_type
		operator+(typename ft::vector<T, Alloc>::Iterator::difference_type i,
					typename ft::vector<T, Alloc>::Iterator const & it);*/
}

# include "vector.tpp"
#endif