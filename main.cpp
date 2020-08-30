#include "List.hpp"
#include <list>
#include <iostream>

template <template <class T, class Alloc = std::allocator<T> > class containerT>
void
test_list(void)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    containerT<int>     defaultList;
}

int
main(void)
{
    test_list<std::list>();
    test_list<ft::List>();
    return (0);
}
