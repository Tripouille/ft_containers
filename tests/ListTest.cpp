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
    std::cout << "defaultList.push_back(30)" << std::endl; defaultList.push_back(30);
    std::cout << "defaultList.push_back(40)" << std::endl; defaultList.push_back(40);
    std::cout << "defaultList.pop_front()" << std::endl; defaultList.pop_front();
    std::cout << "defaultList.pop_back()" << std::endl; defaultList.pop_back();
		
    //containerT<int>     fillList(10000,7);
    //std::cout << ".size() = " << fillList.size() << std::endl;
}

int
main(void)
{
    test_list<std::list>();
    test_list<ft::List>();
    //ft::List<int>     fillList((unsigned long)(10000), 12);
    ft::List<int>     fillList(4, 1);
    std::cout << ".size() = " << fillList.size() << std::endl;
    return (0);
}
