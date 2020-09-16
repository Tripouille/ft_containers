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

	FILE << CATEGORY << "===> Basic tests with <int>" << ENDL;
	FILE << SUBCATEGORY << "=====> Empty list" << ENDL;
	FILE << "list<int> listA;" << ENDL; containerT<int> listA;
	print_list(listA, "listA", f);
	FILE << "listA.max_size() = " << OUTPUT << listA.max_size() << ENDL;
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
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

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "list<int> listB(4, -1);" << ENDL; containerT<int> listB(4, -1);
	print_list(listB, "listB", f);
	FILE << std::boolalpha << "listB.empty() = " << OUTPUT << listB.empty() << ENDL;
	FILE << "listB.size() = " << OUTPUT << listB.size() << ENDL;
	FILE << "listB.front() = " << OUTPUT << listB.front() << ENDL;
	FILE << "listB.back() = " << OUTPUT << listB.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Copy constructor" << ENDL;
	print_list(listA, "listA", f);
	FILE << "list<int> listC(listA);" << ENDL; containerT<int> listC(listA);
	print_list(listA, "listA", f);
	print_list(listC, "listC", f);
	FILE << "listC.size() = " << OUTPUT << listC.size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Operator=" << ENDL;
	print_list(listA, "listA", f);
	print_list(listB, "listB", f);
	FILE << "listA = listB;" << ENDL; listA = listB;
	print_list(listA, "listA", f);
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << "listA.push_front(0);" << ENDL; listA.push_front(0);
	print_list(listA, "listA", f);
	print_list(listB, "listB", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <int> const list" << ENDL;
	FILE << "list<int> const listD(3, -2);" << ENDL; containerT<int> const listD(3, -2);
	print_list(listD, "listD", f);
	FILE << std::boolalpha << "listD.empty() = " << OUTPUT << listD.empty() << ENDL;
	FILE << "listD.size() = " << OUTPUT << listD.size() << ENDL;
	FILE << "listD.front() = " << OUTPUT << listD.front() << ENDL;
	FILE << "listD.back() = " << OUTPUT << listD.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <NoDefaultConstructorClass>" << ENDL;
	FILE << SUBCATEGORY << "=====> Empty list" << ENDL;
	FILE << "list<NoDefaultConstructorClass> listE;" << ENDL; containerT<NoDefaultConstructorClass> listE;
	print_list(listE, "listE", f);
	FILE << "listE.max_size() = " << OUTPUT << listE.max_size() << ENDL;
	FILE << std::boolalpha << "listE.empty() = " << OUTPUT << listE.empty() << ENDL;
	FILE << "listE.size() = " << OUTPUT << listE.size() << ENDL;
	FILE << SUBCATEGORY << "=====> Pushing" << ENDL;
	FILE << "listE.push_front(NoDefaultConstructorClass(2));" << ENDL; listE.push_front(NoDefaultConstructorClass(2));
	print_list(listE, "listE", f);
	FILE << "listE.size() = " << OUTPUT << listE.size() << ENDL;
	FILE << "listE.push_front(NoDefaultConstructorClass(1));" << ENDL; listE.push_front(NoDefaultConstructorClass(1));
	print_list(listE, "listE", f);
	FILE << std::boolalpha << "listE.empty() = " << OUTPUT << listE.empty() << ENDL;
	FILE << "listE.push_back(NoDefaultConstructorClass(3));" << ENDL; listE.push_back(NoDefaultConstructorClass(3));
	print_list(listE, "listE", f);
	FILE << "listE.push_back(NoDefaultConstructorClass(4));" << ENDL; listE.push_back(NoDefaultConstructorClass(4));
	print_list(listE, "listE", f);
	FILE << SUBCATEGORY << "=====> Front and back" << ENDL;
	FILE << "listE.front() = NoDefaultConstructorClass(-9);" << ENDL; listE.front() = NoDefaultConstructorClass(-9);
	FILE << "listE.back() = NoDefaultConstructorClass(9);" << ENDL; listE.back() = NoDefaultConstructorClass(9);
	print_list(listE, "listE", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Exception-safety test with <ThrowingExceptionClass>,"
						"a class which throws an exception in copy constructor" << ENDL;
	FILE << "list<ThrowingExceptionClass> listF;" << ENDL; containerT<ThrowingExceptionClass> listF;
	FILE << "ThrowingExceptionClass testObject;" << ENDL; ThrowingExceptionClass testObject;
	FILE << "try {safelist.push_back(testobject);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {listF.push_back(testObject);}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	FILE << "listF.size() = " << OUTPUT << listF.size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Iterators" << ENDL;
	listA.clear(); listA.push_back(1); listA.push_back(2); listA.push_back(3);
	print_list(listA, "listA", f);
	FILE << "typename containerT<int>::iterator it = listA.begin();" << ENDL; typename containerT<int>::iterator it = listA.begin();
	FILE << "*it = " << OUTPUT << *it << ENDL;
	FILE << "it++;" << ENDL; it++;
	FILE << "*it = " << OUTPUT << *it << ENDL;
	FILE << "it++;" << ENDL; it++;
	FILE << "*it = " << OUTPUT << *it << ENDL;
	FILE << "it++;" << ENDL; it++;
 
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

	FILE << TITLE << "=> ENDING list tests" << ENDL;
}

int
main(void)
{
    test_list<std::list>();
    test_list<ft::list>();
}
