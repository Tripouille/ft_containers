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
	FILE << "containerT<int> vectorA;" << ENDL; containerT<int> vectorA;
	FILE << ENDL;

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "containerT<int> vectorB(3, 2);" << ENDL; containerT<int> vectorB(3, 2);
	FILE << ENDL;

	/*FILE << CATEGORY << "===> Range constructor" << ENDL;
	FILE << "int intArrayA[] = {1, 2, 3, 4, 5};" << ENDL; int intArrayA[] = {1, 2, 3, 4, 5};
	FILE << "containerT<int> vectorC(intArrayA, intArrayA + 5);" << ENDL; containerT<int> vectorC(intArrayA, intArrayA + 5);
	FILE << ENDL;*/

	FILE << TITLE << "=> ENDING vector tests" << ENDL << ENDL;
}

int
main(void)
{
    test_vector<std::vector>();
}
