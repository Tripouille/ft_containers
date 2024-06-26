#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <sstream>
# include <limits>
# include <exception>
# include <cstddef>
# include <cstring>
# include "types.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
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

				T *					get_target(void) const {return (_target);}

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
				T const &			operator[](typename CIterator::difference_type i) const;
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

		class CRIterator : public BaseIterator
		{
			public:
				CRIterator(T * t = NULL);
				CRIterator(RIterator const & rit);
				~CRIterator(void);
				CRIterator(CRIterator const & other);

				CRIterator &		operator=(CRIterator const & other);
				T const &			operator*(void) const;
				T const *			operator->(void) const;
				CRIterator &		operator++(void);
				CRIterator			operator++(int);
				CRIterator &		operator--(void);
				CRIterator			operator--(int);
				CRIterator 			operator+(typename CRIterator::difference_type i) const;
		 friend CRIterator			operator+(typename CRIterator::difference_type i, CRIterator const & it)
									{return (CRIterator(it._target - i));}
				CRIterator 			operator-(typename CRIterator::difference_type i) const;
				typename CRIterator::difference_type
									operator-(CRIterator const & other) const;
				CRIterator &		operator+=(typename CRIterator::difference_type i);
				CRIterator &		operator-=(typename CRIterator::difference_type i);
				T const &			operator[](typename CRIterator::difference_type i) const;
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
			typedef typename ft::vector<T, Alloc>::CRIterator const_reverse_iterator;
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
			~vector(void);

		/* Operator */
			vector<T, Alloc> &			operator=(vector const & other);

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
				reference front(void);
				const_reference front(void) const;
				reference back(void);
				const_reference back(void) const;

			/** Modifiers **/
				/*** range (1) ***/	template <class InputIterator>
				 					void assign(InputIterator first, InputIterator last);
				/*** fill (2) ***/	void assign(size_type n, const value_type & val);
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
				void swap(vector & x);
				void clear(void);

			/** Observers **/
				allocator_type get_allocator(void) const;

		private:
		/* Private Functions */
			void _copy(vector const & other);
			template <class Integer>
			void _construct_vector_dispatch(Integer & first, Integer & last, INT_TYPE);
			template <class InputIterator>
			void _construct_vector_dispatch(InputIterator & first, InputIterator & last, NO_INT_TYPE);
			void _construct_vector_with_val(size_type n, value_type const & val);
			template <class InputIterator>
			void _construct_vector_from_range(InputIterator & first, InputIterator & last);
			void _reallocate(size_type n, bool anticipate_place = false);
			void _range_check(size_type n) const throw(std::out_of_range);

		/* Private variables */
			allocator_type			_alloc;
			pointer					_start;
			pointer					_end;
			pointer					_limit;
	};

	/* Non-member function overloads */
		/** Relational operators **/
			template <class T, class Alloc>
			bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);
			template <class T, class Alloc>
			bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs);

		/** swap **/
			template <class T, class Alloc>
			void swap(vector<T, Alloc> & x, vector<T, Alloc> & y);
}

# include "vector.tpp"
#endif