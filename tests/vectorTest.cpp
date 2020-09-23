#include "vector.hpp"
#include <vector>
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
print_vector(T vector, std::string const & name)
{
	(void)vector;
	(void)name;
	/*typename T::iterator begin = list.begin();
	typename T::iterator end = list.end();
	std::cout << OUTPUT << name << " = [ ";
	while (begin != end)
	{
			std::cout << *begin << " ";
			++begin;
	}
	std::cout << "] Size = " << list.size() << ENDL;*/
}

template <template <class T, class Alloc = std::allocator<T> > class containerT>
void
test_vector(void)
{
	FILE << TITLE << std::endl << "=> STARTING vector tests" << ENDL;

	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << ENDL;

	FILE << TITLE << "=> ENDING vector tests" << ENDL << ENDL;
}

int
main(void)
{
    test_vector<ft::vector>();
}
