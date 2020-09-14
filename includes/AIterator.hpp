#ifndef AITERATOR_HPP
# define AITERATOR_HPP

namespace ft
{
	template <class T>
	class AIterator
	{
		public:
			AIterator(T * t = NULL);
			virtual ~AIterator(void);
			AIterator(AIterator const & other);

			AIterator &				operator=(AIterator const & other);
			bool					operator==(AIterator const & other);
			//AIterator &				operator++(AIterator const & other) = 0;
			//AIterator &				operator--(AIterator const & other) = 0;

		public:
			void					_copy(AIterator const & other);
			T *						_target;
	};
}

# include "AIterator.tpp"
#endif