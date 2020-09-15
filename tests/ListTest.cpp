#include "List.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include "Color.hpp"

template<class T>
void
print_list(T list, std::string const & name, std::ofstream & file)
{
	typename T::iterator begin = list.begin();
	typename T::iterator end = list.end();
	file << GREEN << name << " = [ ";
	while (begin != end)
	{
			file << *begin << " ";
			++begin;
	}
	file << "]" << RESET << std::endl;
}

/*class testClassForSafetyException
{
	public:
		testClassForSafetyException(void) : _a(0) {}
		testClassForSafetyException(testClassForSafetyException const& other)
			: _a(other._a) {if (_a == 0) {throw std::exception();}}
	private:
		int _a;
};*/

struct testStruct {int a; testStruct(void) : a(3) {}};

template <template <class T, class Alloc = std::allocator<T> > class containerT>
void
test_list(void)
{
	std::string name(__PRETTY_FUNCTION__);
	std::string file_name = name.substr(name.find_last_of(' ') + 1, name.size() - name.find_last_of(' ') - 2)
							+ ".result";
	std::ofstream file(file_name.c_str(), std::ofstream::trunc);

	containerT<int>     defaultList;
	print_list(defaultList, "defaultList", file);
	file << "defaultList.max_size() = " << GREEN << defaultList.max_size() << ENDL;
	file << std::boolalpha << "defaultList.empty() = " << GREEN << defaultList.empty() << ENDL;
	file << "defaultList.size() = " << GREEN << defaultList.size() << ENDL;
	file << "defaultList.push_front(2)" << ENDL; defaultList.push_front(2);
	file << "defaultList.push_front(1)" << ENDL; defaultList.push_front(1);
	print_list(defaultList, "defaultList", file);
	file << "defaultList.push_back(3)" << ENDL; defaultList.push_back(3);
	print_list(defaultList, "defaultList", file);
	file << "defaultList.front() = " << GREEN << defaultList.front() << ENDL;
	file << "defaultList.back() = " << GREEN << defaultList.back() << ENDL;
	file << "defaultList.push_back(4)" << ENDL; defaultList.push_back(4);

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

}

int
main(void)
{
    test_list<std::list>();
    test_list<ft::List>();
}
