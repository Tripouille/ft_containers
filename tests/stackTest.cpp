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
	FILE << TITLE << std::endl << "=> deque" << ENDL;

	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "==> Default constructor" << ENDL;
	FILE << "stack<int> stackA;" << ENDL; stack<int> stackA;
	FILE << "stackA.empty() : " << std::boolalpha << OUTPUT << stackA.empty() << ENDL;
	FILE << "stackA.size() : " << OUTPUT << stackA.size() << ENDL;

	FILE << "stackA.push(0);" << ENDL; stackA.push(0);
	FILE << "stackA.top() : " << OUTPUT << stackA.top() << ENDL;
	FILE << "stackA.empty() : " << std::boolalpha << OUTPUT << stackA.empty() << ENDL;
	FILE << "stackA.size() : " << OUTPUT << stackA.size() << ENDL;

	FILE << "stackA.push(1);" << ENDL; stackA.push(1);
	FILE << "stackA.top() : " << OUTPUT << stackA.top() << ENDL;
	FILE << "stackA.push(2);" << ENDL; stackA.push(2);
	FILE << "stackA.top() : " << OUTPUT << stackA.top() << ENDL;
	FILE << "stackA.pop();" << ENDL; stackA.pop();
	FILE << "stackA.top() : " << OUTPUT << stackA.top() << ENDL;

	FILE << "stack<int> stackB(stackA);" << ENDL; stack<int> stackB(stackA);
	FILE << "stackB.top() : " << OUTPUT << stackB.top() << ENDL;
	FILE << "stackB.empty() : " << std::boolalpha << OUTPUT << stackB.empty() << ENDL;
	FILE << "stackB.size() : " << OUTPUT << stackB.size() << ENDL;
	FILE << "stackA.push(42);" << ENDL; stackA.push(42);
	FILE << "stackB.top() : " << OUTPUT << stackB.top() << ENDL;
	FILE << "stackB = stackA;" << ENDL; stackB = stackA;
	FILE << "stackB.top() : " << OUTPUT << stackB.top() << ENDL;







	FILE << TITLE << "=> ENDING stack tests" << ENDL << ENDL;
}

int
main(void)
{
    test_stack<ft::stack>();
}
