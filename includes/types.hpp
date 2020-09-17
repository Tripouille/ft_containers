#ifndef TYPES_HPP
#define TYPES_HPP

#define INT_TYPE int
#define NO_INT_TYPE void*

template<class T>
struct is_integer
{
	typedef NO_INT_TYPE type;
};

template<> struct is_integer<bool> {typedef INT_TYPE type;};
template<> struct is_integer<int> {typedef INT_TYPE type;};

#endif // TYPES_HPP