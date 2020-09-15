#include "list.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include "Color.hpp"
#define FILE f << RESET

template<class T>
void
print_list(T list, std::string const & name, std::ofstream & f)
{
	typename T::iterator begin = list.begin();
	typename T::iterator end = list.end();
	f << GREEN << name << " = [ ";
	while (begin != end)
	{
			f << *begin << " ";
			++begin;
	}
	f << "]" << RESET << std::endl;
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
	FILE << RED << std::endl << "=> STARTING list tests <=" << ENDL;

	containerT<int>     defaultList;
	print_list(defaultList, "defaultList", f);
	FILE << "defaultList.max_size() = " << GREEN << defaultList.max_size() << ENDL;
	FILE << std::boolalpha << "defaultList.empty() = " << GREEN << defaultList.empty() << ENDL;
	FILE << "defaultList.size() = " << GREEN << defaultList.size() << ENDL;
	FILE << "defaultList.push_front(2)" << ENDL; defaultList.push_front(2);
	FILE << "defaultList.push_front(1)" << ENDL; defaultList.push_front(1);
	print_list(defaultList, "defaultList", f);
	FILE << "defaultList.push_back(3)" << ENDL; defaultList.push_back(3);
	print_list(defaultList, "defaultList", f);
	FILE << "defaultList.front() = " << GREEN << defaultList.front() << ENDL;
	FILE << "defaultList.back() = " << GREEN << defaultList.back() << ENDL;
	FILE << "defaultList.push_back(4)" << ENDL; defaultList.push_back(4);

	/*std::cout << "defaultList.pop_front()" << ENDL; defaultList.pop_front();
	std::cout << "defaultList.pop_back()" << ENDL; defaultList.pop_back();
	std::cout << "defaultList.front() = " << defaultList.front() << ENDL;
	std::cout << "defaultList.back() = " << defaultList.back() << ENDL;
	std::cout << "defaultList.back() = 42" << ENDL; defaultList.back() = 42;
	std::cout << "defaultList.back() = " << defaultList.back() << ENDL;
	std::cout << "defaultList.front() = 21" << ENDL; defaultList.front() = 21;
	std::cout << "defaultList.front() = " << defaultList.front() << ENDL;*/


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
	FILE << RED << "=> ENDING list tests <=" << std::endl << ENDL;
}

int
main(void)
{
    test_list<std::list>();
    test_list<ft::list>();
}
