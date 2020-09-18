#ifndef DLNODE_HPP
# define DLNODE_HPP

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class list;
	template <class T>
	struct DLNode
	{
		class BaseIterator
		{
			public:
				BaseIterator(DLNode<T> * t = NULL);
				virtual ~BaseIterator(void);
				BaseIterator(BaseIterator const & other);

				BaseIterator &		operator=(BaseIterator const & other);
				bool				operator==(BaseIterator const & other) const;
				bool				operator!=(BaseIterator const & other) const;

			protected:
				void				_copy(BaseIterator const & other);
				DLNode<T> *			_target;
			friend class ft::list<T>;
		};

		class Iterator : public BaseIterator
		{
			public:
				Iterator(DLNode<T> * t = NULL);
				~Iterator(void);
				Iterator(Iterator const & other);

				Iterator &			operator=(Iterator const & other);
				Iterator &			operator++(void);
				Iterator			operator++(int);
				Iterator &			operator--(void);
				Iterator			operator--(int);
				T &					operator*(void) const;
				T *					operator->(void) const;
		};

		class CIterator : public BaseIterator
		{
			public:
				CIterator(DLNode<T> * t = NULL);
				CIterator(Iterator const & it);
				~CIterator(void);
				CIterator(CIterator const & other);

				CIterator &			operator=(CIterator const & other);
				CIterator &			operator++(void);
				CIterator			operator++(int);
				CIterator &			operator--(void);
				CIterator			operator--(int);
				T const &			operator*(void) const;
				T const *			operator->(void) const;
		};

		class RIterator : public BaseIterator
		{
			public:
				RIterator(DLNode<T> * t = NULL);
				~RIterator(void);
				RIterator(RIterator const & other);

				RIterator &		operator=(RIterator const & other);
				RIterator &		operator++(void);
				RIterator		operator++(int);
				RIterator &		operator--(void);
				RIterator 		operator--(int);
				T &				operator*(void) const;
				T *				operator->(void) const;
		};

		class CRIterator : public BaseIterator
		{
			public:
				CRIterator(DLNode<T> * t = NULL);
				CRIterator(RIterator const & rit);
				~CRIterator(void);
				CRIterator(CRIterator const & other);

				CRIterator &	operator=(CRIterator const & other);
				CRIterator &	operator++(void);
				CRIterator		operator++(int);
				CRIterator &	operator--(void);
				CRIterator		operator--(int);
				T const &		operator*(void) const;
				T const *		operator->(void) const;
		};

		typedef ft::DLNode<T>::Iterator iterator;
		typedef ft::DLNode<T>::CIterator const_iterator;
		typedef ft::DLNode<T>::RIterator reverse_iterator;
		typedef ft::DLNode<T>::CRIterator const_reverse_iterator;

		DLNode(void);
		DLNode(const T & v, DLNode * p = NULL, DLNode * n = NULL);
		~DLNode(void);
		DLNode(DLNode const & other);

		DLNode &				operator=(DLNode const & other);

		T						value;
		DLNode<T> *				prev;
		DLNode<T> *				next;

		private:
			void					_copy(DLNode const & other);
	};
}

# include "DLNode.tpp"
#endif
