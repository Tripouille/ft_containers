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
print_vector(T & vector, std::string const & name)
{
	typename T::iterator begin = vector.begin();
	typename T::iterator end = vector.end();
	std::cout << OUTPUT << name << " = [ ";
	while (begin != end)
	{
		std::cout << *begin << " ";
		++begin;
	}
	std::cout << "]"/* Size = " << vector.size()*/ << ENDL;
}

template <template <class T, class Alloc = std::allocator<T> > class vec>
void
test_vector(void)
{
	FILE << TITLE << std::endl << "=> STARTING vector tests" << ENDL;

	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << "vec<int> vectorA;" << ENDL; vec<int> vectorA;
	print_vector(vectorA, "vectorA");
	FILE << ENDL;

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "vec<int> vectorB(3, 2);" << ENDL; vec<int> vectorB(3, 2);
	print_vector(vectorB, "vectorB");
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	FILE << "int intArrayA[] = {1, 2, 3, 4, 5};" << ENDL; int intArrayA[] = {1, 2, 3, 4, 5};
	FILE << "vec<int> vectorC(intArrayA, intArrayA + 5);" << ENDL; vec<int> vectorC(intArrayA, intArrayA + 5);
	print_vector(vectorC, "vectorC");
	FILE << ENDL;

	FILE << SUBTITLE << "Iterators" << ENDL;
	typename vec<int>::iterator it = vectorB.begin();
	typename vec<int>::iterator ite = vectorB.end();
	for (; it != ite; ++it)
		FILE << *it << ENDL;
	FILE << ENDL;

	FILE << TITLE << "=> ENDING vector tests" << ENDL << ENDL;
}

int
main(void)
{
    test_vector<ft::vector>();
	/*std::vector<int> test;
	test.push_back(0);
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	std::vector<int>::iterator it = test.begin();
	std::vector<int>::iterator ite = test.end();
	std::cout << it - ite << std::endl;*/
}
