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
    /*defaultList.push_back(10);
    defaultList.push_back(20);
    print_list(defaultList);*/
		std::cout << "defaultList.push_front(10)" << std::endl; defaultList.push_front(10);
		std::cout << "defaultList.push_front(20)" << std::endl; defaultList.push_front(20);
}

int
main(void)
{
    test_list<std::list>();
    //test_list<ft::List>();
    return (0);
}
