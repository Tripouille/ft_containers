#include "List.hpp"
#include <list>
#include <iostream>

template<class T>
void
print_list(T list)
{
	typename T::iterator begin = list.begin();
	typename T::iterator end = list.end();
	std::cout << "List: [ ";
	while (begin != end)
	{
			std::cout << *begin << " ";
			++begin;
	}
	std::cout << "]" << std::endl;
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

template <template <class T, class Alloc = std::allocator<T> > class containerT>
void
test_list(void)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	containerT<int>     defaultList;
	std::cout << std::boolalpha << ".empty() = " << defaultList.empty() << std::endl;
	std::cout << ".size() = " << defaultList.size() << std::endl;
	std::cout << ".max_size() = " << defaultList.max_size() << std::endl;
	std::cout << "defaultList.push_front(20)" << std::endl; defaultList.push_front(20);
	std::cout << "defaultList.push_front(10)" << std::endl; defaultList.push_front(10);
	std::cout << "defaultList.front() = " << defaultList.front() << std::endl;
	std::cout << "defaultList.back() = " << defaultList.back() << std::endl;
	std::cout << "defaultList.push_back(30)" << std::endl; defaultList.push_back(30);
	std::cout << "defaultList.push_back(40)" << std::endl; defaultList.push_back(40);
	std::cout << "defaultList.pop_front()" << std::endl; defaultList.pop_front();
	std::cout << "defaultList.pop_back()" << std::endl; defaultList.pop_back();
	std::cout << "defaultList.front() = " << defaultList.front() << std::endl;
	std::cout << "defaultList.back() = " << defaultList.back() << std::endl;
	std::cout << "defaultList.back() = 42" << std::endl; defaultList.back() = 42;
	std::cout << "defaultList.back() = " << defaultList.back() << std::endl;
	std::cout << "defaultList.front() = 21" << std::endl; defaultList.front() = 21;
	std::cout << "defaultList.front() = " << defaultList.front() << std::endl;
    typename containerT<int>::iterator it = defaultList.begin();
	std::cout << *it << std::endl;
	std::cout << *++it << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << std::endl;

	std::cout << "Copy construction test with defaultList2 : " << std::endl;
	std::cout << "defaultList2(defaultList)" << std::endl;
	containerT<int>		defaultList2(defaultList);
	std::cout << "defaultList2.size() = " << defaultList2.size() << std::endl;
	std::cout << "defaultList2.front() = " << defaultList2.front() << std::endl;
	std::cout << "defaultList2.back() = " << defaultList2.back() << std::endl;
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
	std::cout << std::endl;

	/*std::cout << "Exception-safety tests :" << std::endl;
	containerT<testClassForSafetyException> safelist;
	testClassForSafetyException testobject; //ok seulement si constructeur par défaut
	try {safelist.push_back(testobject);}
	catch(...) {std::cerr << "catched exception" << std::endl;}
	std::cout << "size = " << safelist.size() << std::endl;
	std::cout << std::endl;*/
}

int
main(void)
{
    //test_list<std::list>();
    test_list<ft::List>();
}
