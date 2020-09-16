#ifndef DLNODE_HPP
# define DLNODE_HPP
# include "AIterator.hpp"

namespace ft
{
	template <class T>
	struct DLNode
	{
		class Iterator : public AIterator<DLNode<T> >
		{
			public:
				Iterator(DLNode<T> * t = NULL);
				~Iterator(void);
				Iterator(Iterator const & other);

				Iterator &		operator=(DLNode const & other);
				Iterator &		operator++(void);
				Iterator		operator++(int);
				Iterator &		operator--(void);
				Iterator		operator--(int);
				T &				operator*(void);
				T &				operator*(void) const;
				T *				operator->(void);
				T *				operator->(void) const;
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
