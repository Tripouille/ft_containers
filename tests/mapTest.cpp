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
	(void)map;
	(void)name;
}

template <template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > > class map>
void
test_map(void)
{
	FILE << TITLE << std::endl << "=> STARTING map tests" << ENDL;
	map<int, std::string> m;
	m[1] = "A";
	FILE << "m[1] : " << OUTPUT << m[1] << ENDL;
	FILE << "m[2] : " << OUTPUT << m[2] << ENDL;
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