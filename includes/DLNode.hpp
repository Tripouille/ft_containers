#ifndef DLNODE_HPP
# define DLNODE_HPP

namespace ft
{
	template <class T>
	struct DLNode
	{
		class Iterator
		{
			public:
				Iterator(DLNode<T> * t = NULL);
				virtual ~Iterator(void);
				Iterator(Iterator const & other);

				Iterator &		operator=(Iterator const & other);
				bool			operator==(Iterator const & other) const;
				bool			operator!=(Iterator const & other) const;
				Iterator &		operator++(void);
				Iterator		operator++(int);
				Iterator &		operator--(void);
				Iterator		operator--(int);
				T &				operator*(void) const;
				T *				operator->(void) const;
			protected:
				void			_copy(Iterator const & other);
				DLNode<T> *		_target;
		};

		class CIterator : public Iterator
		{
			public:
				CIterator(DLNode<T> * t = NULL);
				CIterator(Iterator const & it);
				~CIterator(void);
				CIterator(CIterator const & other);

				CIterator &		operator=(CIterator const & other);
				T const &		operator*(void) const;
				T const *		operator->(void) const;
		};

		class RIterator : public Iterator
		{
			public:
				RIterator(DLNode<T> * t = NULL);
				virtual ~RIterator(void);
				RIterator(RIterator const & other);

				RIterator &		operator=(RIterator const & other);
				RIterator &		operator++(void);
				RIterator		operator++(int);
				RIterator &		operator--(void);
				RIterator		operator--(int);
		};

		typedef typename ft::DLNode<T>::Iterator iterator;
		typedef typename ft::DLNode<const T>::Iterator const_iterator;
		typedef RIterator reverse_iterator;
		typedef const reverse_iterator const_reverse_iterator;

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
