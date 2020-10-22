#ifndef BTNODE_HPP
# define BTNODE_HPP
# include <cstddef>

namespace ft
{
	template <class Key, class T, class Compare, class Alloc>
	class map;
	template <class Key, class T, class Compare, class Alloc>
	struct BTNode
	{
		/* Typedef */
		typedef BTNode<Key, T, Compare, Alloc> node;

		struct bidirectional_iterator_tag {};
		class BaseIterator
		{
			public:
				typedef std::pair<Key, T> value_type;
				typedef ptrdiff_t difference_type;
				typedef std::pair<Key, T> * pointer;
				typedef std::pair<Key, T> & reference;
				typedef bidirectional_iterator_tag iterator_category;

				BaseIterator(node * n = NULL);
				virtual ~BaseIterator(void);
				BaseIterator(BaseIterator const & other);

				BaseIterator &		operator=(BaseIterator const & other);
				bool				operator==(BaseIterator const & other) const;
				bool				operator!=(BaseIterator const & other) const;

			protected:
				void	_copy(BaseIterator const & other);
				node *	_node;
				//node ** _root_ptr; a faire demain getfirst getlast

			friend class ft::map<Key, T, Compare, Alloc>;
		};

		class Iterator : public BaseIterator
		{
			public:
				Iterator(node * n = NULL);
				~Iterator(void);
				Iterator(Iterator const & other);

				Iterator &			operator=(Iterator const & other);
				Iterator &			operator++(void);
				Iterator			operator++(int);
				Iterator &			operator--(void);
				Iterator			operator--(int);
				std::pair<Key, T> &	operator*(void) const;
				std::pair<Key, T> *	operator->(void) const;
		};
		/*
		class CIterator : public BaseIterator
		{
			public:
				CIterator(BTNode<Key, T, Compare, Alloc> * t = NULL);
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
				RIterator(BTNode<Key, T, Compare, Alloc> * t = NULL);
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
				CRIterator(BTNode<Key, T, Compare, Alloc> * t = NULL);
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

		typedef ft::BTNode<T, Alloc>::CIterator const_iterator;
		typedef ft::BTNode<T, Alloc>::RIterator reverse_iterator;
		typedef ft::BTNode<T, Alloc>::CRIterator const_reverse_iterator;
		*/
		typedef Iterator iterator;

		BTNode(void);
		BTNode(const Key & k, const T & v,
				BTNode * p = NULL, BTNode * l = NULL, BTNode * r = NULL);
		~BTNode(void);
		BTNode(BTNode const & other);

		BTNode &				operator=(BTNode const & other);

		std::pair<Key, T>	pair;
		node *				parent;
		node *				left;
		node *				right;

		private:
			void					_copy(BTNode const & other);
	};
}

# include "BTNode.tpp"
#endif
