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
				~Iterator(void);
				Iterator(Iterator const & other);

				Iterator &		operator=(Iterator const & other);
				bool			operator==(Iterator const & other) const;
				bool			operator!=(Iterator const & other) const;
				Iterator &		operator++(void);
				Iterator		operator++(int);
				Iterator &		operator--(void);
				Iterator		operator--(int);
				T &				operator*(void);
				T &				operator*(void) const;
				T *				operator->(void);
				T *				operator->(void) const;
			private:
				void			_copy(Iterator const & other);
				DLNode<T> *		_target;
		};

		typedef Iterator iterator;
		typedef const iterator const_iterator;

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
