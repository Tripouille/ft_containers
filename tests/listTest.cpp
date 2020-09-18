#include "list.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include "Color.hpp"
#define TITLE FG_CYAN << BOLD
#define CATEGORY FG_DGRAY << BOLD
#define SUBCATEGORY FG_DGRAY
#define OUTPUT FG_GREEN << UNDERLINED
#define FILE f << RESET_ALL

class ThrowingExceptionClass
{
	public:
		ThrowingExceptionClass(void) : _a(2) {}
		ThrowingExceptionClass(int a) : _a(a) {}
		ThrowingExceptionClass(ThrowingExceptionClass const& other) {(void)other; throw std::exception();}
		~ThrowingExceptionClass() {}
		ThrowingExceptionClass& operator=(ThrowingExceptionClass const& other) {(void)other; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
};

class NoDefaultConstructorClass
{
	public:
		NoDefaultConstructorClass(int a) : _a(a) {}
		NoDefaultConstructorClass(NoDefaultConstructorClass const& other) : _a(other._a) {}
		~NoDefaultConstructorClass() {}
		NoDefaultConstructorClass& operator=(NoDefaultConstructorClass const& other) {_a = other._a; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
		NoDefaultConstructorClass(void) {}
};
std::ostream&	operator<<(std::ostream& os, NoDefaultConstructorClass const& obj) {os << obj.geta(); return (os);}

struct testStruct {int a; testStruct(void) : a(3) {}};
std::ostream&	operator<<(std::ostream& os, testStruct const& obj) {os << "a = " << obj.a; return (os);}

std::string const
get_file_name(std::string s)
{
	std::string file_name = "results/"
			+ s.substr(s.find_last_of(' ') + 1, s.size() - s.find_last_of(' ') - 2)
			+ ".result";
	return (file_name);
}

template<class T>
void
print_list(T list, std::string const & name, std::ofstream & f)
{
	typename T::iterator begin = list.begin();
	typename T::iterator end = list.end();
	f << OUTPUT << name << " = [ ";
	while (begin != end)
	{
			f << *begin << " ";
			++begin;
	}
	f << "]" << ENDL;
}

template <template <class T, class Alloc = std::allocator<T> > class containerT>
void
test_list(void)
{
	std::ofstream f(get_file_name(__PRETTY_FUNCTION__).c_str(), std::ofstream::trunc);
	FILE << TITLE << std::endl << "=> STARTING list tests" << ENDL;

	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << "list<int> listA;" << ENDL; containerT<int> listA;
	print_list(listA, "listA", f);
	FILE << "listA.max_size() = " << OUTPUT << listA.max_size() << ENDL;
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "list<int> listB(4, -1);" << ENDL; containerT<int> listB(4, -1);
	print_list(listB, "listB", f);
	FILE << std::boolalpha << "listB.empty() = " << OUTPUT << listB.empty() << ENDL;
	FILE << "listB.size() = " << OUTPUT << listB.size() << ENDL;
	FILE << "listB.front() = " << OUTPUT << listB.front() << ENDL;
	FILE << "listB.back() = " << OUTPUT << listB.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	int intArray[] = {1, 2, 3, 4, 5};
	containerT<int> listC(intArray, intArray + 5);
	print_list(listC, "listC", f);
	FILE << std::boolalpha << "listC.empty() = " << OUTPUT << listC.empty() << ENDL;
	FILE << "listC.size() = " << OUTPUT << listC.size() << ENDL;
	FILE << "listC.front() = " << OUTPUT << listC.front() << ENDL;
	FILE << "listC.back() = " << OUTPUT << listC.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Copy constructor" << ENDL;
	print_list(listC, "listC", f);
	FILE << "list<int> listD(listC);" << ENDL; containerT<int> listD(listC);
	print_list(listC, "listC", f);
	print_list(listD, "listD", f);
	FILE << "listD.size() = " << OUTPUT << listD.size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Operator=" << ENDL;
	print_list(listB, "listB", f);
	print_list(listC, "listC", f);
	FILE << "listB = listC;" << ENDL; listB = listC;
	print_list(listB, "listB", f);
	FILE << "listB.size() = " << OUTPUT << listB.size() << ENDL;
	FILE << "listB.push_front(0);" << ENDL; listB.push_front(0);
	print_list(listB, "listB", f);
	print_list(listC, "listC", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <int>" << ENDL;
	print_list(listA, "listA", f);
	FILE << SUBCATEGORY << "=====> Pushing" << ENDL;
	FILE << "listA.push_front(2);" << ENDL; listA.push_front(2);
	print_list(listA, "listA", f);
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << "listA.push_front(1);" << ENDL; listA.push_front(1);
	print_list(listA, "listA", f);
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << "listA.push_back(3);" << ENDL; listA.push_back(3);
	print_list(listA, "listA", f);
	FILE << "listA.push_back(4);" << ENDL; listA.push_back(4);
	FILE << "listA.push_back(5);" << ENDL; listA.push_back(5);
	print_list(listA, "listA", f);
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << SUBCATEGORY << "=====> Popping" << ENDL;
	FILE << "listA.pop_front();" << ENDL; listA.pop_front();
	print_list(listA, "listA", f);
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << "listA.pop_back();" << ENDL; listA.pop_back();
	print_list(listA, "listA", f);
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << SUBCATEGORY << "=====> Front and back" << ENDL;
	FILE << "listA.front() = " << OUTPUT << listA.front() << ENDL;
	FILE << "listA.back() = " << OUTPUT << listA.back() << ENDL;
	FILE << "listA.back() = 9;" << ENDL; listA.back() = 9;
	print_list(listA, "listA", f);
	FILE << "listA.front() = -9;" << ENDL; listA.front() = -9;
	print_list(listA, "listA", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <int> const list" << ENDL;
	FILE << "list<int> const listE(3, -2);" << ENDL; containerT<int> const listE(3, -2);
	print_list(listE, "listE", f);
	FILE << std::boolalpha << "listE.empty() = " << OUTPUT << listE.empty() << ENDL;
	FILE << "listE.size() = " << OUTPUT << listE.size() << ENDL;
	FILE << "listE.front() = " << OUTPUT << listE.front() << ENDL;
	FILE << "listE.back() = " << OUTPUT << listE.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <NoDefaultConstructorClass>" << ENDL;
	FILE << SUBCATEGORY << "=====> Empty list" << ENDL;
	FILE << "list<NoDefaultConstructorClass> listF;" << ENDL; containerT<NoDefaultConstructorClass> listF;
	print_list(listF, "listF", f);
	FILE << "listF.max_size() = " << OUTPUT << listF.max_size() << ENDL;
	FILE << std::boolalpha << "listF.empty() = " << OUTPUT << listF.empty() << ENDL;
	FILE << "listF.size() = " << OUTPUT << listF.size() << ENDL;
	FILE << SUBCATEGORY << "=====> Pushing" << ENDL;
	FILE << "listF.push_front(NoDefaultConstructorClass(2));" << ENDL; listF.push_front(NoDefaultConstructorClass(2));
	print_list(listF, "listF", f);
	FILE << "listF.size() = " << OUTPUT << listF.size() << ENDL;
	FILE << "listF.push_front(NoDefaultConstructorClass(1));" << ENDL; listF.push_front(NoDefaultConstructorClass(1));
	print_list(listF, "listF", f);
	FILE << std::boolalpha << "listF.empty() = " << OUTPUT << listF.empty() << ENDL;
	FILE << "listF.push_back(NoDefaultConstructorClass(3));" << ENDL; listF.push_back(NoDefaultConstructorClass(3));
	print_list(listF, "listF", f);
	FILE << "listF.push_back(NoDefaultConstructorClass(4));" << ENDL; listF.push_back(NoDefaultConstructorClass(4));
	print_list(listF, "listF", f);
	FILE << SUBCATEGORY << "=====> Front and back" << ENDL;
	FILE << "listF.front() = NoDefaultConstructorClass(-9);" << ENDL; listF.front() = NoDefaultConstructorClass(-9);
	FILE << "listF.back() = NoDefaultConstructorClass(9);" << ENDL; listF.back() = NoDefaultConstructorClass(9);
	print_list(listF, "listF", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Exception-safety test with <ThrowingExceptionClass>, "
						"a class which throws an exception in copy constructor" << ENDL;
	FILE << "list<ThrowingExceptionClass> listG;" << ENDL; containerT<ThrowingExceptionClass> listG;
	FILE << "ThrowingExceptionClass testObject;" << ENDL; ThrowingExceptionClass testObject;
	FILE << "try {safelist.push_back(testobject);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {listG.push_back(testObject);}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	FILE << "listG.size() = " << OUTPUT << listG.size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Iterators" << ENDL;
	listA.clear(); listA.push_back(1); listA.push_back(2); listA.push_back(3);
	print_list(listA, "listA", f);
	FILE << "typename containerT<int>::iterator it = listA.begin();" << ENDL; typename containerT<int>::iterator it = listA.begin();
	FILE << "typename containerT<int>::iterator ite = listA.end();" << ENDL; typename containerT<int>::iterator ite = listA.end();
	FILE << "(*it == listA.front()) = " << OUTPUT << std::boolalpha << (*it == listA.front()) << ENDL;
	FILE << "while (it != ite) {...; it++;}" << ENDL;
	while (it != ite)
	{
		FILE << "*it = " << OUTPUT << *it << ENDL;
		it++;
	}
	FILE << "it--;" << ENDL; it--;
	FILE << "(*it == listA.back()) = " << OUTPUT << std::boolalpha << (*it == listA.back()) << ENDL;
	FILE << "*it = 42;" << ENDL; *it = 42;
	print_list(listA, "listA", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Const iterators" << ENDL;
	FILE << "typename containerT<int>::const_iterator c_it = listA.begin();" << ENDL; typename containerT<int>::const_iterator c_it = listA.begin();
	FILE << "typename containerT<int>::const_iterator c_ite = listA.end();" << ENDL; typename containerT<int>::const_iterator c_ite = listA.end();
	FILE << "(*c_it == listA.front()) = " << OUTPUT << std::boolalpha << (*c_it == listA.front()) << ENDL;
	FILE << "while (c_it != c_ite) {...; c_it++;}" << ENDL;
	while (c_it != c_ite)
	{
		FILE << "*c_it = " << OUTPUT << *c_it << ENDL;
		//*c_it += 1;
		c_it++;
	}
	FILE << "c_it--;" << ENDL; c_it--;
	FILE << "(*c_it == listA.back()) = " << OUTPUT << std::boolalpha << (*c_it == listA.back()) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Reverse iterators" << ENDL;
	FILE << "typename containerT<int>::reverse_iterator r_it = listA.rbegin();" << ENDL; typename containerT<int>::reverse_iterator r_it = listA.rbegin();
	FILE << "typename containerT<int>::reverse_iterator r_ite = listA.rend();" << ENDL; typename containerT<int>::reverse_iterator r_ite = listA.rend();
	FILE << "while (r_it != r_ite) {...; r_it++;}" << ENDL;
	while (r_it != r_ite)
	{
		FILE << "*r_it = " << OUTPUT << *r_it << ENDL;
		r_it++;
	}
	FILE << "r_it--;" << ENDL; r_it--;
	FILE << "(*r_it == listA.front()) = " << OUTPUT << std::boolalpha << (*r_it == listA.front()) << ENDL;
	FILE << "*r_it = -42;" << ENDL; *r_it = -42;;
	print_list(listA, "listA", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Const reverse iterators" << ENDL;
	FILE << "typename containerT<int>::const_reverse_iterator cr_it = listA.rbegin();" << ENDL; typename containerT<int>::const_reverse_iterator cr_it = listA.rbegin();
	FILE << "typename containerT<int>::const_reverse_iterator cr_ite = listA.rend();" << ENDL; typename containerT<int>::const_reverse_iterator cr_ite = listA.rend();
	FILE << "while (cr_it != cr_ite) {...; cr_it++;}" << ENDL;
	while (cr_it != cr_ite)
	{
		FILE << "*cr_it = " << OUTPUT << *cr_it << ENDL;
		//*cr_it += 1;
		cr_it++;
	}
	FILE << "cr_it--;" << ENDL; cr_it--;
	FILE << "(*cr_it == listA.front()) = " << OUTPUT << std::boolalpha << (*cr_it == listA.front()) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Assign" << ENDL;
	print_list(listA, "listA", f);
	FILE << "listA.assign(7, 100);" << ENDL; listA.assign(7, 100);
	print_list(listA, "listA", f);
	print_list(listB, "listB", f);
	FILE << "listA.assign(listB.rbegin(), listB.rend());" << ENDL; listA.assign(listB.rbegin(), listB.rend());
	print_list(listA, "listA", f);
	FILE << "int myints[] = {1337, 4, 7};" << ENDL; int myints[] = {1337, 4, 7};
	FILE << "listA.assign(myints + 1, myints + 3);" << ENDL; listA.assign(myints + 1, myints + 3);
	print_list(listA, "listA", f);
	FILE << ENDL;


	/*	std::cout << "Assign test (back on defaultList) : " << std::endl;
	std::cout << "defaultList.assign(4, 5)" << std::endl; defaultList.assign(4, 5);
	std::cout << "defaultList.size() = " << defaultList.size() << std::endl;
	std::cout << "defaultList.back() = " << defaultList.back() << std::endl;
	std::cout << "defaultList.front() = " << defaultList.front() << std::endl;
	std::cout << "defaultList.assign(0, 5)" << std::endl; defaultList.assign(0, 5);
	std::cout << "defaultList.size() = " << defaultList.size() << std::endl;
	std::cout << std::endl;

	std::cout << "Swap test : " << std::endl;
	std::cout << "defaultList.size() = " << defaultList.size() << std::endl;
	std::cout << "defaultList2.size() = " << defaultList2.size() << std::endl;
	std::cout << "defaultList2.front() = " << defaultList2.front() << std::endl;
	std::cout << "defaultList.swap(defaultList2)" << std::endl; defaultList.swap(defaultList2);
	std::cout << "defaultList.size() = " << defaultList.size() << std::endl;
	std::cout << "defaultList.front() = " << defaultList.front() << std::endl;
	std::cout << "defaultList2.size() = " << defaultList2.size() << std::endl;
	std::cout << "defaultList3.push_front(3)" << std::endl; defaultList3.push_front(3);
	std::cout << "defaultList3.size() = " << defaultList3.size() << std::endl;
	std::cout << "defaultList.swap(defaultList3)" << std::endl; defaultList.swap(defaultList3);
	std::cout << "defaultList.size() = " << defaultList.size() << std::endl;
	std::cout << "defaultList.front() = " << defaultList.front() << std::endl;
	std::cout << "defaultList3.size() = " << defaultList3.size() << std::endl;
	std::cout << "defaultList3.front() = " << defaultList3.front() << std::endl;
	std::cout << std::endl;*/

	FILE << TITLE << "=> ENDING list tests" << ENDL << ENDL;
}

int
main(void)
{
    test_list<std::list>();
    test_list<ft::list>();
}
