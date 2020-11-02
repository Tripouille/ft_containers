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
				typedef std::pair<Key const, T> value_type;
				typedef ptrdiff_t difference_type;
				typedef std::pair<Key const, T> * pointer;
				typedef std::pair<Key const, T> & reference;
				typedef bidirectional_iterator_tag iterator_category;

				BaseIterator(node * n = NULL, node * const * root = NULL);
				virtual ~BaseIterator(void);
				BaseIterator(BaseIterator const & other);

				node *				get_node(void) const {return (_node);}

				BaseIterator &		operator=(BaseIterator const & other);
				bool				operator==(BaseIterator const & other) const;
				bool				operator!=(BaseIterator const & other) const;

			protected:
				void	_copy(BaseIterator const & other);
				node *	_get_first_node(void);
				node *	_get_last_node(void);

				node *			_node;
				node * const *	_root_ptr;
		};

		class Iterator : public BaseIterator
		{
			public:
				Iterator(node * n = NULL, node * const * root = NULL);
				~Iterator(void);
				Iterator(Iterator const & other);

				Iterator &			operator=(Iterator const & other);
				Iterator &			operator++(void);
				Iterator			operator++(int);
				Iterator &			operator--(void);
				Iterator			operator--(int);
				std::pair<Key const, T> &	operator*(void) const;
				std::pair<Key const, T> *	operator->(void) const;
		};

		class CIterator : public BaseIterator
		{
			public:
				CIterator(node * n = NULL, node * const * root = NULL);
				CIterator(Iterator const & it);
				~CIterator(void);
				CIterator(CIterator const & other);

				CIterator &					operator=(CIterator const & other);
				CIterator &					operator++(void);
				CIterator					operator++(int);
				CIterator &					operator--(void);
				CIterator					operator--(int);
				std::pair<Key const, T> const &	operator*(void) const;
				std::pair<Key const, T> const *	operator->(void) const;
		};
		
		class RIterator : public BaseIterator
		{
			public:
				RIterator(node * n = NULL, node * const * root = NULL);
				~RIterator(void);
				RIterator(RIterator const & other);

				RIterator &					operator=(RIterator const & other);
				RIterator &					operator++(void);
				RIterator					operator++(int);
				RIterator &					operator--(void);
				RIterator 					operator--(int);
				std::pair<Key const, T> &	operator*(void) const;
				std::pair<Key const, T> *	operator->(void) const;
		};

		class CRIterator : public BaseIterator
		{
			public:
				CRIterator(node * n = NULL, node * const * root = NULL);
				CRIterator(RIterator const & rit);
				~CRIterator(void);
				CRIterator(CRIterator const & other);

				CRIterator &						operator=(CRIterator const & other);
				CRIterator &						operator++(void);
				CRIterator							operator++(int);
				CRIterator &						operator--(void);
				CRIterator							operator--(int);
				std::pair<Key const, T> const &		operator*(void) const;
				std::pair<Key const, T> const *		operator->(void) const;
		};

		typedef Iterator iterator;
		typedef CIterator const_iterator;
		typedef RIterator reverse_iterator;
		typedef CRIterator const_reverse_iterator;

		BTNode(void);
		BTNode(const Key & k, const T & v,
				BTNode * p = NULL, BTNode * l = NULL, BTNode * r = NULL);
		~BTNode(void);
		BTNode(BTNode const & other);

		BTNode &				operator=(BTNode const & other);

		std::pair<Key const, T>	pair;
		node *				parent;
		node *				left;
		node *				right;
		bool 				is_black;

		private:
			void					_copy(BTNode const & other);
	};
}

# include "BTNode.tpp"
#endif
