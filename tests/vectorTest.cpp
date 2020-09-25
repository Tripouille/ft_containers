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
	std::cout << "] Size : " << vector.size() << ENDL;
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
	//FILE << "vectorA.max_size() : " << OUTPUT << vectorA.max_size() << ENDL;
	//FILE << std::boolalpha << "vectorA.empty() : " << OUTPUT << vectorA.max_size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "vec<int> vectorB(3, 2);" << ENDL; vec<int> vectorB(3, 2);
	print_vector(vectorB, "vectorB");
	//FILE << std::boolalpha << "vectorA.empty() : " << OUTPUT << vectorA.max_size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	FILE << "int intArrayA[] = {1, 2, 3, 4, 5};" << ENDL; int intArrayA[] = {1, 2, 3, 4, 5};
	FILE << "vec<int> vectorC(intArrayA, intArrayA + 5);" << ENDL; vec<int> vectorC(intArrayA, intArrayA + 5);
	print_vector(vectorC, "vectorC");
	//FILE << std::boolalpha << "vectorA.empty() : " << OUTPUT << vectorA.max_size() << ENDL;
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
	print_vector(vectorB, "vectorB");
	FILE << "vectorB.push_back(6);" << ENDL; vectorB.push_back(6);
	print_vector(vectorB, "vectorB");
	print_vector(vectorC, "vectorC");
	FILE << ENDL;

	FILE << SUBTITLE << "Iterators" << ENDL;
	FILE << CATEGORY << "===> Iterators" << ENDL;
	vectorA.clear();
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.begin() == vectorA.end() : " << OUTPUT << std::boolalpha << (vectorA.begin() == vectorA.end()) << ENDL;
	FILE << SUBCATEGORY << "(Pushing some values)" << ENDL;
	vectorA.push_back(1); vectorA.push_back(2); vectorA.push_back(3); vectorA.push_back(4);
	print_vector(vectorA, "vectorA");
	FILE << "vec<int>::iterator it = vectorA.begin();" << ENDL; typename vec<int>::iterator it = vectorA.begin();
	FILE << "vec<int>::iterator ite = vectorA.end();" << ENDL; typename vec<int>::iterator ite = vectorA.end();
	//FILE << "(*it == vectorA.front()) = " << OUTPUT << std::boolalpha << (*it == vectorA.front()) << ENDL;
	FILE << "it == vectorA.end() : " << OUTPUT << std::boolalpha << (it == vectorA.end()) << ENDL;
	FILE << "it != vectorA.end() : " << OUTPUT << std::boolalpha << (it != vectorA.end()) << ENDL;
	FILE << "while (it != ite) {...; it++;}" << ENDL;
	while (it != ite)
	{
		FILE << "*it = " << OUTPUT << *it << ENDL;
		++it;
	}
	FILE << "it == vectorA.end() : " << OUTPUT << std::boolalpha << (it == vectorA.end()) << ENDL;
	FILE << "it != vectorA.end() : " << OUTPUT << std::boolalpha << (it != vectorA.end()) << ENDL;
	FILE << "it--;" << ENDL; it--;
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "--it;" << ENDL; --it;
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "it++;" << ENDL; it++;
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "--it; --it;" << ENDL; --it; --it;
	//FILE << "(*it == vectorA.back()) = " << OUTPUT << std::boolalpha << (*it == vectorA.back()) << ENDL;
	FILE << "*it = 42;" << ENDL; *it = 42;
	print_vector(vectorA, "vectorA");
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "*(it + 2) : " << OUTPUT << *(it + 2) << ENDL;
	FILE << "*(it - 1) : " << OUTPUT << *(it - 1) << ENDL;
	FILE << "*(2 + it) : " << OUTPUT << *(2 + it) << ENDL;
	FILE << "ite - it : " << OUTPUT << (ite - it) << ENDL;
	FILE << "*(it += 2) : " << OUTPUT << *(it += 2) << ENDL;
	FILE << "*(it -= 2) : " << OUTPUT << *(it -= 2) << ENDL;
	FILE << "(it += 42) = vectorA.begin();" << ENDL; (it += 42) = vectorA.begin();
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "(it -= 42) = --vectorA.end();" << ENDL; (it -= 42) = --vectorA.end();
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "it[0] : " << OUTPUT << it[0] << ENDL;
	FILE << "it[-2] : " << OUTPUT << it[-2] << ENDL;
	FILE << "vec<int>::iterator const const_it = vectorA.begin();" << ENDL;
	typename vec<int>::iterator const const_it = vectorA.begin();
	FILE << "const_it[0] : " << OUTPUT << const_it[0] << ENDL;
	FILE << "const_it[2] : " << OUTPUT << const_it[2] << ENDL;
	FILE << ENDL;

	FILE << SUBTITLE << "Element access" << ENDL;
	FILE << CATEGORY << "===> operator[]" << ENDL;
	FILE << "vec<int> test(2, 1);" << ENDL; vec<int> test(2, 1);
	FILE << "test[0] : " << OUTPUT << test[0] << ENDL;
	FILE << "test[0] = 21;" << ENDL; test[0] = 21;
	FILE << "test[0] : " << OUTPUT << test[0] << ENDL;
	FILE << "test[1] = 7;" << ENDL; test[1] = 7;
	FILE << "test[1] : " << OUTPUT << test[1] << ENDL;
	FILE << "vec<int> const const_test(1, 42);" << ENDL; vec<int> const const_test(1, 42);
	FILE << "const_test[0] : " << OUTPUT << const_test[0] << ENDL;
	FILE << CATEGORY << "===> at" << ENDL;
	FILE << "test.at(0) : " << OUTPUT << test.at(0) << ENDL;
	try
		{FILE << "test.at(42) : " << test.at(42) << ENDL;}
	catch (std::out_of_range const & e)
		{FILE << OUTPUT << e.what() << ENDL;}
	FILE << "const_test.at(0) : " << const_test.at(0) << ENDL;
	try
		{FILE << "const_test.at(-1) : " << const_test.at(static_cast<unsigned long>(-1)) << ENDL;}
	catch (std::out_of_range const & e)
		{FILE << OUTPUT << e.what() << ENDL;}

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
