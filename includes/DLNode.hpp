#ifndef DLNODE_HPP
# define DLNODE_HPP

namespace ft
{
	template <class T>
	struct DLNode
	{
		DLNode(const T & v = T(), DLNode * p = NULL, DLNode * n = NULL);
		virtual ~DLNode(void);
		DLNode(DLNode const & other);

		DLNode &				operator=(DLNode const & other);
		void					_copy(DLNode const & other);

		T						value;
		DLNode<T> *				prev;
		DLNode<T> *				next;
	};
}

# include "DLNode.tpp"
#endif
