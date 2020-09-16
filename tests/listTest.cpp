#include "list.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include "Color.hpp"
#define TITLE FG_RED
#define CATEGORY FG_YELLOW
#define OUTPUT FG_GREEN
#define FILE f << RESET_ALL

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

class testClassForSafetyException
{
	public:
		testClassForSafetyException(int a) : _a(a) {}
		testClassForSafetyException(testClassForSafetyException const& other)
			: _a(other._a) {if (_a == 0) {throw std::exception();}}
		int geta(void) const {return (_a);}
	private:
		testClassForSafetyException(void) : _a(2) {}
		int _a;
};
std::ostream&	operator<<(std::ostream& os, testClassForSafetyException const& obj) {os << "a = " << obj.geta(); return (os);}


class TestClass
{
	public:
		TestClass(int a) : _a(a) {}
		TestClass(TestClass const& other) : _a(other._a) {}
		int geta(void) const {return (_a);}
	private:
		int _a;
		TestClass(void) : _a(2) {}
};
std::ostream&	operator<<(std::ostream& os, TestClass const& obj) {os << obj.geta(); return (os);}

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


template <template <class T, class Alloc = std::allocator<T> > class containerT>
void
test_list(void)
{
	std::ofstream f(get_file_name(__PRETTY_FUNCTION__).c_str(), std::ofstream::trunc);
	FILE << TITLE << std::endl << "=> STARTING list tests" << ENDL;

	FILE << CATEGORY << "===> Basic tests with <int>" << ENDL;
	FILE << CATEGORY << "=====> Empty list" << ENDL;
	FILE << "containerT<int> listA;" << ENDL; containerT<int> listA;
	print_list(listA, "listA", f);
	FILE << "listA.max_size() = " << OUTPUT << listA.max_size() << ENDL;
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << CATEGORY << "=====> Pushing" << ENDL;
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
	FILE << CATEGORY << "=====> Popping" << ENDL;
	FILE << "listA.pop_front();" << ENDL; listA.pop_front();
	print_list(listA, "listA", f);
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << "listA.pop_back();" << ENDL; listA.pop_back();
	print_list(listA, "listA", f);
	FILE << "listA.size() = " << OUTPUT << listA.size() << ENDL;
	FILE << CATEGORY << "=====> Front and back" << ENDL;
	FILE << "listA.front() = " << OUTPUT << listA.front() << ENDL;
	FILE << "listA.back() = " << OUTPUT << listA.back() << ENDL;
	FILE << "listA.back() = 6;" << ENDL; listA.back() = 6;
	print_list(listA, "listA", f);
	FILE << "listA.front() = 7;" << ENDL; listA.front() = 7;
	print_list(listA, "listA", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <TestClass>, a class with no default constructor" << ENDL;
	FILE << CATEGORY << "=====> Empty list" << ENDL;
	FILE << "containerT<TestClass> listB;" << ENDL; containerT<TestClass> listB;
	print_list(listB, "listB", f);
	FILE << "listB.max_size() = " << OUTPUT << listB.max_size() << ENDL;
	FILE << std::boolalpha << "listB.empty() = " << OUTPUT << listB.empty() << ENDL;
	FILE << "listB.size() = " << OUTPUT << listB.size() << ENDL;
	FILE << CATEGORY << "=====> Pushing" << ENDL;
	FILE << "listB.push_front(TestClass(2));" << ENDL; listB.push_front(TestClass(2));
	print_list(listB, "listB", f);
	FILE << "listB.size() = " << OUTPUT << listB.size() << ENDL;
	FILE << "listB.push_front(TestClass(1));" << ENDL; listB.push_front(TestClass(1));
	print_list(listB, "listB", f);
	FILE << std::boolalpha << "listB.empty() = " << OUTPUT << listB.empty() << ENDL;
	FILE << "listB.push_back(TestClass(3));" << ENDL; listB.push_back(TestClass(3));
	print_list(listB, "listB", f);
	FILE << "listB.push_back(TestClass(4));" << ENDL; listB.push_back(TestClass(4));
	print_list(listB, "listB", f);
	FILE << CATEGORY << "=====> Front and back" << ENDL;
	FILE << "listB.back() = 5;" << ENDL; listB.back() = 5;
	print_list(listB, "listB", f);
	FILE << "listB.front() = 6;" << ENDL; listB.front() = 6;
	print_list(listB, "listB", f);
	FILE << ENDL;

	/*FILE << CATEGORY << "===> Copy construction tests" << ENDL;
	print_list(listA, "listA", f);
	FILE << ENDL;*/


	/*std::cout << "Copy construction test with defaultList2 : " << std::endl;
	std::cout << "defaultList2(defaultList)" << std::endl;
	containerT<int>		defaultList2(defaultList);
	std::cout << "defaultList2.size() = " << defaultList2.size() << std::endl;
	//std::cout << "defaultList2.front() = " << defaultList2.front() << std::endl;
	//std::cout << "defaultList2.back() = " << defaultList2.back() << std::endl;
	std::cout << "defaultList2 = "; print_list(defaultList2);
	std::cout << "defaultList2.push_back(84)" << std::endl; defaultList2.push_back(84);
	std::cout << std::endl;

	std::cout << "Test on operator= with defaultList3 : " << std::endl;
	std::cout << "defaultList3(defaultList)" << std::endl;
	containerT<int>		defaultList3(defaultList);
	std::cout << "defaultList3 = defaultList2" << std::endl; defaultList3 = defaultList2;
	std::cout << "defaultList3.size() = " << defaultList3.size() << std::endl;
	std::cout << "defaultList2.front() = " << defaultList2.front() << std::endl;
	std::cout << "defaultList2.back() = " << defaultList2.back() << std::endl;
	std::cout << std::endl;

	//containerT<int>     fillList(10000,7);
	//std::cout << ".size() = " << fillList.size() << std::endl;

	std::cout << "Const list test on back() with defaultList4 :" << std::endl;
	containerT<int> const    defaultList4(4, 1);
	std::cout << "defaultList4.back() = " << defaultList4.back() << std::endl;
	//std::cout << "defaultList4.back() = 42;" << std::endl; defaultList4.back() = 42;
	std::cout << std::endl;

	std::cout << "Assign test (back on defaultList) : " << std::endl;
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

	/*std::cout << "Exception-safety tests :" << std::endl;
	containerT<testClassForSafetyException> safelist;
	testClassForSafetyException testobject;
	try {safelist.push_back(testobject);}
	catch(...) {std::cerr << "catched exception" << std::endl;}
	std::cout << "size = " << safelist.size() << std::endl;
	std::cout << std::endl;*/
	FILE << TITLE << "=> ENDING list tests" << std::endl << ENDL;
}

int
main(void)
{
    test_list<std::list>();
    test_list<ft::list>();
}
