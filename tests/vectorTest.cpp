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
	std::cout << "] Size = " << vector.size() << ENDL;
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
	//FILE << "vectorA.max_size() = " << OUTPUT << vectorA.max_size() << ENDL;
	//FILE << std::boolalpha << "vectorA.empty() = " << OUTPUT << vectorA.max_size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "vec<int> vectorB(3, 2);" << ENDL; vec<int> vectorB(3, 2);
	print_vector(vectorB, "vectorB");
	//FILE << std::boolalpha << "vectorA.empty() = " << OUTPUT << vectorA.max_size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	FILE << "int intArrayA[] = {1, 2, 3, 4, 5};" << ENDL; int intArrayA[] = {1, 2, 3, 4, 5};
	FILE << "vec<int> vectorC(intArrayA, intArrayA + 5);" << ENDL; vec<int> vectorC(intArrayA, intArrayA + 5);
	print_vector(vectorC, "vectorC");
	//FILE << std::boolalpha << "vectorA.empty() = " << OUTPUT << vectorA.max_size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Copy constructor" << ENDL;
	print_vector(vectorC, "vectorC");
	FILE << "vector<int> vectorD(vectorC);" << ENDL; vec<int> vectorD(vectorC);
	print_vector(vectorC, "vectorC");
	print_vector(vectorD, "vectorD");
	FILE << ENDL;

	FILE << SUBTITLE << "Operator" << ENDL;
	FILE << CATEGORY << "===> Operator=" << ENDL;
	print_vector(vectorB, "vectorB");
	print_vector(vectorC, "vectorC");
	FILE << "vectorB = vectorC;" << ENDL; vectorB = vectorC;
	//print_vector(vectorB, "vectorB");
	//FILE << "vectorB.push_back(0);" << ENDL; vectorB.push_back(0);
	print_vector(vectorB, "vectorB");
	print_vector(vectorC, "vectorC");
	FILE << ENDL;

	FILE << SUBTITLE << "Iterators" << ENDL;
	FILE << CATEGORY << "===> Iterators" << ENDL;
	vectorA.clear();
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.begin() == vectorA.end() : " << OUTPUT << std::boolalpha << (vectorA.begin() == vectorA.end()) << ENDL;
	//FILE << SUBCATEGORY << "(Pushing some values)" << ENDL;
	//vectorA.push_back(1); vectorA.push_back(2); vectorA.push_back(3);
	//print_vector(vectorA, "vectorA");
	FILE << "vec<int>::iterator it = vectorA.begin();" << ENDL; typename vec<int>::iterator it = vectorA.begin();
	FILE << "vec<int>::iterator ite = vectorA.end();" << ENDL; typename vec<int>::iterator ite = vectorA.end();
	//FILE << "(*it == vectorA.front()) = " << OUTPUT << std::boolalpha << (*it == vectorA.front()) << ENDL;
	FILE << "while (it != ite) {...; it++;}" << ENDL;
	while (it != ite)
	{
		FILE << "*it = " << OUTPUT << *it << ENDL;
		it++;
	}
	FILE << "it--;" << ENDL; it--;
	//FILE << "(*it == vectorA.back()) = " << OUTPUT << std::boolalpha << (*it == vectorA.back()) << ENDL;
	//FILE << "*it = 42;" << ENDL; *it = 42;
	//print_vector(vectorA, "vectorA");
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
