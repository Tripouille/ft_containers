#include "stack.hpp"
#include <stack>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include "vector.hpp"
#include "Color.hpp"
#define TITLE FG_CYAN << BOLD
#define SUBTITLE FG_RED << BOLD
#define CATEGORY FG_DGRAY << BOLD
#define SUBCATEGORY FG_DGRAY
#define OUTPUT FG_GREEN << UNDERLINED
#define FILE std::cout << RESET_ALL
using std::deque;

template<class T>
void
print_stack(T const & stack, std::string const & name)
{
	(void)stack;
	(void)name;
}

template <template <class T, class Container = deque<T> > class stack>
void
test_stack(void)
{
	FILE << TITLE << std::endl << "=> STARTING stack tests" << ENDL;

	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "==> Default constructor" << ENDL;
	FILE << "stack<int> stackA;" << ENDL; stack<int> stackA;

	FILE << TITLE << "=> ENDING stack tests" << ENDL << ENDL;
}

int
main(void)
{
    test_stack<ft::stack>();
}
