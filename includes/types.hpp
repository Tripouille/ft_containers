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
template<> struct is_integer<char> {typedef INT_TYPE type;};
template<> struct is_integer<signed char> {typedef INT_TYPE type;};
template<> struct is_integer<unsigned char> {typedef INT_TYPE type;};
template<> struct is_integer<wchar_t> {typedef INT_TYPE type;};
template<> struct is_integer<short> {typedef INT_TYPE type;};
template<> struct is_integer<unsigned short> {typedef INT_TYPE type;};
template<> struct is_integer<int> {typedef INT_TYPE type;};
template<> struct is_integer<unsigned int> {typedef INT_TYPE type;};
template<> struct is_integer<long> {typedef INT_TYPE type;};
template<> struct is_integer<unsigned long> {typedef INT_TYPE type;};
template<> struct is_integer<long long> {typedef INT_TYPE type;};
template<> struct is_integer<unsigned long long> {typedef INT_TYPE type;};

#endif // TYPES_HPP