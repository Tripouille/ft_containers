#include "map.hpp"
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Color.hpp"
#define TITLE FG_CYAN << BOLD
#define SUBTITLE FG_RED << BOLD
#define CATEGORY FG_DGRAY << BOLD
#define SUBCATEGORY FG_DGRAY
#define OUTPUT FG_GREEN << UNDERLINED
#define FILE std::cout << RESET_ALL

template<class T>
void
print_map(T const & map, std::string const & name)
{
	typename T::const_iterator begin = map.begin();
	typename T::const_iterator end = map.end();
	std::cout << OUTPUT << name << " = [ ";
	while (begin != end)
	{
		std::cout << "(" << begin->first << " : " << begin->second << ") ";
		++begin;
	}
	std::cout /*<< "] Size : " << map.size()*/ << ENDL;
}

template <template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > > class map>
void
test_map(void)
{
	FILE << TITLE << std::endl << "=> STARTING map tests" << ENDL;

	map<int, std::string> m2;
	m2[10] = "";
	m2[7] = "";
	m2[7] = "";
	m2[9] = "";
	m2[8] = "";
	m2[20] = "";
	m2[30] = "";
	m2[21] = "";
	m2[22] = "";
	m2[23] = "";
	m2[33] = "";
	m2[32] = "";
	m2[31] = "";
	print_map(m2, "m2");

	/*begin = m2.begin();
	end = m2.end();
	while (end != begin)
	{
		--end;
		std::cout << "reverse(" << end->first << " : " << end->second << ") ";
	}*/

	typename map<int, std::string>::reverse_iterator rbegin = m2.rbegin();
	typename map<int, std::string>::reverse_iterator rend = m2.rend();
	while (rbegin != rend)
	{
		std::cout << "reverse(" << rbegin->first << " : " << rbegin->second << ") ";
		++rbegin;
	}

	typename map<int, std::string>::const_reverse_iterator crbegin = m2.rbegin();
	typename map<int, std::string>::const_reverse_iterator crend = m2.rend();
	while (crbegin != crend)
	{
		std::cout << "reverse(" << crbegin->first << " : " << crbegin->second << ") ";
		++crbegin;
	}
	//(--crbegin)->second = "A";

	//begin->first = 1;

	/*map<int, std::string> m2;
	print_map(m2, "m2");
	typename map<int, std::string>::iterator begin = m2.begin();
	++begin;*/

	/*typename map<int, std::string>::const_iterator cbegin = m2.begin();
	FILE << "*cbegin : " << OUTPUT << cbegin->first << ENDL;*/
	//cbegin->second = "A";


	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << ENDL;
	FILE << TITLE << "=> ENDING map tests" << ENDL << ENDL;
}

int
main(void)
{
    test_map<ft::map>();
}
