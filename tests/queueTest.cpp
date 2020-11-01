#include "queue.hpp"
#include <queue>
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

template <template <class T, class Container = deque<T> > class queue>
void
test_queue(void)
{
	FILE << TITLE << std::endl << "=> STARTING queue tests" << ENDL;
	FILE << TITLE << std::endl << "=> deque" << ENDL;

	FILE << "queue<int> queueA;" << ENDL; queue<int> queueA;
	FILE << "queueA.empty() : " << std::boolalpha << OUTPUT << queueA.empty() << ENDL;
	FILE << "queueA.size() : " << OUTPUT << queueA.size() << ENDL;

	FILE << "queueA.push(0);" << ENDL; queueA.push(0);
	FILE << "queueA.top() : " << OUTPUT << queueA.top() << ENDL;
	FILE << "queueA.empty() : " << std::boolalpha << OUTPUT << queueA.empty() << ENDL;
	FILE << "queueA.size() : " << OUTPUT << queueA.size() << ENDL;

	FILE << "queueA.push(1);" << ENDL; queueA.push(1);
	FILE << "queueA.top() : " << OUTPUT << queueA.top() << ENDL;
	FILE << "queueA.push(2);" << ENDL; queueA.push(2);
	FILE << "queueA.top() : " << OUTPUT << queueA.top() << ENDL;
	FILE << "queueA.pop();" << ENDL; queueA.pop();
	FILE << "queueA.top() : " << OUTPUT << queueA.top() << ENDL;

	FILE << "queue<int> queueB(queueA);" << ENDL; queue<int> queueB(queueA);
	FILE << "queueB.top() : " << OUTPUT << queueB.top() << ENDL;
	FILE << "queueB.empty() : " << std::boolalpha << OUTPUT << queueB.empty() << ENDL;
	FILE << "queueB.size() : " << OUTPUT << queueB.size() << ENDL;
	FILE << "queueA.push(42);" << ENDL; queueA.push(42);
	FILE << "queueB.top() : " << OUTPUT << queueB.top() << ENDL;
	FILE << "queueB = queueA;" << ENDL; queueB = queueA;
	FILE << "queueB.top() : " << OUTPUT << queueB.top() << ENDL;

	FILE << ENDL;
	FILE << "queue<int> const queueConst(queueA);" << ENDL; queue<int> const queueConst(queueA);
	FILE << "queueConst.top() : " << OUTPUT << queueConst.top() << ENDL;
	FILE << "queueConst.empty() : " << std::boolalpha << OUTPUT << queueConst.empty() << ENDL;
	FILE << "queueConst.size() : " << OUTPUT << queueConst.size() << ENDL;

	FILE << ENDL;
	FILE << "queue<int> queueEmpty;" << ENDL; queue<int> queueEmpty;
	FILE << "queueConst == queueA : " << std::boolalpha << OUTPUT << (queueConst == queueA) << ENDL;
	FILE << "queueConst == queueEmpty : " << std::boolalpha << OUTPUT << (queueConst == queueEmpty) << ENDL;
	FILE << "queueConst != queueA : " << std::boolalpha << OUTPUT << (queueConst != queueA) << ENDL;
	FILE << "queueConst != queueEmpty : " << std::boolalpha << OUTPUT << (queueConst != queueEmpty) << ENDL;
	FILE << "queueConst < queueA : " << std::boolalpha << OUTPUT << (queueConst < queueA) << ENDL;
	FILE << "queueEmpty < queueConst: " << std::boolalpha << OUTPUT << (queueEmpty < queueConst) << ENDL;
	FILE << "queueConst <= queueA : " << std::boolalpha << OUTPUT << (queueConst <= queueA) << ENDL;
	FILE << "queueEmpty <= queueConst: " << std::boolalpha << OUTPUT << (queueEmpty <= queueConst) << ENDL;
	FILE << "queueConst > queueA : " << std::boolalpha << OUTPUT << (queueConst > queueA) << ENDL;
	FILE << "queueEmpty > queueConst: " << std::boolalpha << OUTPUT << (queueEmpty > queueConst) << ENDL;
	FILE << "queueConst >= queueA : " << std::boolalpha << OUTPUT << (queueConst >= queueA) << ENDL;
	FILE << "queueEmpty >= queueConst: " << std::boolalpha << OUTPUT << (queueEmpty >= queueConst) << ENDL;


	FILE << TITLE << std::endl << "=> vector" << ENDL;

	FILE << "queue<int, ft::vector<int> > vectorqueueA;" << ENDL; queue<int, ft::vector<int> > vectorqueueA;
	FILE << "vectorqueueA.empty() : " << std::boolalpha << OUTPUT << vectorqueueA.empty() << ENDL;
	FILE << "vectorqueueA.size() : " << OUTPUT << vectorqueueA.size() << ENDL;

	FILE << "vectorqueueA.push(0);" << ENDL; vectorqueueA.push(0);
	FILE << "vectorqueueA.top() : " << OUTPUT << vectorqueueA.top() << ENDL;
	FILE << "vectorqueueA.empty() : " << std::boolalpha << OUTPUT << vectorqueueA.empty() << ENDL;
	FILE << "vectorqueueA.size() : " << OUTPUT << vectorqueueA.size() << ENDL;

	FILE << "vectorqueueA.push(1);" << ENDL; vectorqueueA.push(1);
	FILE << "vectorqueueA.top() : " << OUTPUT << vectorqueueA.top() << ENDL;
	FILE << "vectorqueueA.push(2);" << ENDL; vectorqueueA.push(2);
	FILE << "vectorqueueA.top() : " << OUTPUT << vectorqueueA.top() << ENDL;
	FILE << "vectorqueueA.pop();" << ENDL; vectorqueueA.pop();
	FILE << "vectorqueueA.top() : " << OUTPUT << vectorqueueA.top() << ENDL;

	FILE << "queue<int, ft::vector<int> > vectorqueueB(vectorqueueA);" << ENDL; queue<int, ft::vector<int> > vectorqueueB(vectorqueueA);
	FILE << "vectorqueueB.top() : " << OUTPUT << vectorqueueB.top() << ENDL;
	FILE << "vectorqueueB.empty() : " << std::boolalpha << OUTPUT << vectorqueueB.empty() << ENDL;
	FILE << "vectorqueueB.size() : " << OUTPUT << vectorqueueB.size() << ENDL;
	FILE << "vectorqueueA.push(42);" << ENDL; vectorqueueA.push(42);
	FILE << "vectorqueueB.top() : " << OUTPUT << vectorqueueB.top() << ENDL;
	FILE << "vectorqueueB = vectorqueueA;" << ENDL; vectorqueueB = vectorqueueA;
	FILE << "vectorqueueB.top() : " << OUTPUT << vectorqueueB.top() << ENDL;

	FILE << ENDL;
	FILE << "queue<int, ft::vector<int> > const vectorqueueConst(vectorqueueA);" << ENDL; queue<int, ft::vector<int> > const vectorqueueConst(vectorqueueA);
	FILE << "vectorqueueConst.top() : " << OUTPUT << vectorqueueConst.top() << ENDL;
	FILE << "vectorqueueConst.empty() : " << std::boolalpha << OUTPUT << vectorqueueConst.empty() << ENDL;
	FILE << "vectorqueueConst.size() : " << OUTPUT << vectorqueueConst.size() << ENDL;

	FILE << ENDL;
	FILE << "queue<int, ft::vector<int> > vectorqueueEmpty;" << ENDL; queue<int, ft::vector<int> > vectorqueueEmpty;
	FILE << "vectorqueueConst == vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst == vectorqueueA) << ENDL;
	FILE << "vectorqueueConst == vectorqueueEmpty : " << std::boolalpha << OUTPUT << (vectorqueueConst == vectorqueueEmpty) << ENDL;
	FILE << "vectorqueueConst != vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst != vectorqueueA) << ENDL;
	FILE << "vectorqueueConst != vectorqueueEmpty : " << std::boolalpha << OUTPUT << (vectorqueueConst != vectorqueueEmpty) << ENDL;
	FILE << "vectorqueueConst < vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst < vectorqueueA) << ENDL;
	FILE << "vectorqueueEmpty < vectorqueueConst: " << std::boolalpha << OUTPUT << (vectorqueueEmpty < vectorqueueConst) << ENDL;
	FILE << "vectorqueueConst <= vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst <= vectorqueueA) << ENDL;
	FILE << "vectorqueueEmpty <= vectorqueueConst: " << std::boolalpha << OUTPUT << (vectorqueueEmpty <= vectorqueueConst) << ENDL;
	FILE << "vectorqueueConst > vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst > vectorqueueA) << ENDL;
	FILE << "vectorqueueEmpty > vectorqueueConst: " << std::boolalpha << OUTPUT << (vectorqueueEmpty > vectorqueueConst) << ENDL;
	FILE << "vectorqueueConst >= vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst >= vectorqueueA) << ENDL;
	FILE << "vectorqueueEmpty >= vectorqueueConst: " << std::boolalpha << OUTPUT << (vectorqueueEmpty >= vectorqueueConst) << ENDL;

	FILE << TITLE << "=> ENDING queue tests" << ENDL << ENDL;
}

int
main(void)
{
    test_queue<std::queue>();
}
