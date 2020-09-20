#include "list.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Color.hpp"
#define TITLE FG_CYAN << BOLD
#define CATEGORY FG_DGRAY << BOLD
#define SUBCATEGORY FG_DGRAY
#define OUTPUT FG_GREEN << UNDERLINED
#define FILE f << RESET_ALL

class ThrowingExceptionClass
{
	public:
		ThrowingExceptionClass(void) : _a(2) {}
		ThrowingExceptionClass(int a) : _a(a) {}
		ThrowingExceptionClass(ThrowingExceptionClass const& other) {(void)other; throw std::exception();}
		~ThrowingExceptionClass() {}
		ThrowingExceptionClass& operator=(ThrowingExceptionClass const& other) {(void)other; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
};

class NoDefaultConstructorClass
{
	public:
		NoDefaultConstructorClass(int a) : _a(a) {}
		NoDefaultConstructorClass(NoDefaultConstructorClass const& other) : _a(other._a) {}
		~NoDefaultConstructorClass() {}
		NoDefaultConstructorClass& operator=(NoDefaultConstructorClass const& other) {_a = other._a; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
		NoDefaultConstructorClass(void) {}
};
std::ostream&	operator<<(std::ostream& os, NoDefaultConstructorClass const& obj) {os << obj.geta(); return (os);}

struct intStruct
{
	int a;
	intStruct(int n = 0) : a(n) {}
};
std::ostream&	operator<<(std::ostream& os, intStruct const& obj) {os << obj.a; return (os);}

std::string const
get_file_name(std::string s)
{
	std::string file_name = "results/"
			+ s.substr(s.find_last_of(' ') + 1, s.size() - s.find_last_of(' ') - 2)
			+ ".result";
	return (file_name);
}

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
	f << "] Size = " << list.size() << ENDL;
}

template <template <class T, class Alloc = std::allocator<T> > class containerT>
void
test_list(void)
{
	std::ofstream f(get_file_name(__PRETTY_FUNCTION__).c_str(), std::ofstream::trunc);
	std::streambuf * coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(f.rdbuf());
	FILE << TITLE << std::endl << "=> STARTING list tests" << ENDL;

	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << "list<int> listA;" << ENDL; containerT<int> listA;
	print_list(listA, "listA", f);
	FILE << "listA.max_size() = " << OUTPUT << listA.max_size() << ENDL;
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "list<int> listB(4, -1);" << ENDL; containerT<int> listB(4, -1);
	print_list(listB, "listB", f);
	FILE << std::boolalpha << "listB.empty() = " << OUTPUT << listB.empty() << ENDL;
	FILE << "listB.front() = " << OUTPUT << listB.front() << ENDL;
	FILE << "listB.back() = " << OUTPUT << listB.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	int intArray[] = {1, 2, 3, 4, 5};
	containerT<int> listC(intArray, intArray + 5);
	print_list(listC, "listC", f);
	FILE << std::boolalpha << "listC.empty() = " << OUTPUT << listC.empty() << ENDL;
	FILE << "listC.front() = " << OUTPUT << listC.front() << ENDL;
	FILE << "listC.back() = " << OUTPUT << listC.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Copy constructor" << ENDL;
	print_list(listC, "listC", f);
	FILE << "list<int> listD(listC);" << ENDL; containerT<int> listD(listC);
	print_list(listC, "listC", f);
	print_list(listD, "listD", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Operator=" << ENDL;
	print_list(listB, "listB", f);
	print_list(listC, "listC", f);
	FILE << "listB = listC;" << ENDL; listB = listC;
	print_list(listB, "listB", f);
	FILE << "listB.push_front(0);" << ENDL; listB.push_front(0);
	print_list(listB, "listB", f);
	print_list(listC, "listC", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <int>" << ENDL;
	print_list(listA, "listA", f);
	FILE << SUBCATEGORY << "=====> Pushing" << ENDL;
	FILE << "listA.push_front(2);" << ENDL; listA.push_front(2);
	print_list(listA, "listA", f);
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.push_front(1);" << ENDL; listA.push_front(1);
	print_list(listA, "listA", f);
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.push_back(3);" << ENDL; listA.push_back(3);
	print_list(listA, "listA", f);
	FILE << "listA.push_back(4);" << ENDL; listA.push_back(4);
	FILE << "listA.push_back(5);" << ENDL; listA.push_back(5);
	print_list(listA, "listA", f);
	FILE << SUBCATEGORY << "=====> Popping" << ENDL;
	FILE << "listA.pop_front();" << ENDL; listA.pop_front();
	print_list(listA, "listA", f);
	FILE << "listA.pop_back();" << ENDL; listA.pop_back();
	print_list(listA, "listA", f);
	FILE << SUBCATEGORY << "=====> Front and back" << ENDL;
	FILE << "listA.front() = " << OUTPUT << listA.front() << ENDL;
	FILE << "listA.back() = " << OUTPUT << listA.back() << ENDL;
	FILE << "listA.back() = 9;" << ENDL; listA.back() = 9;
	print_list(listA, "listA", f);
	FILE << "listA.front() = -9;" << ENDL; listA.front() = -9;
	print_list(listA, "listA", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <int> const list" << ENDL;
	FILE << "list<int> const listE(3, -2);" << ENDL; containerT<int> const listE(3, -2);
	print_list(listE, "listE", f);
	FILE << std::boolalpha << "listE.empty() = " << OUTPUT << listE.empty() << ENDL;
	FILE << "listE.front() = " << OUTPUT << listE.front() << ENDL;
	FILE << "listE.back() = " << OUTPUT << listE.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <NoDefaultConstructorClass>" << ENDL;
	FILE << SUBCATEGORY << "=====> Empty list" << ENDL;
	FILE << "list<NoDefaultConstructorClass> listF;" << ENDL; containerT<NoDefaultConstructorClass> listF;
	print_list(listF, "listF", f);
	FILE << "listF.max_size() = " << OUTPUT << listF.max_size() << ENDL;
	FILE << std::boolalpha << "listF.empty() = " << OUTPUT << listF.empty() << ENDL;
	FILE << SUBCATEGORY << "=====> Pushing" << ENDL;
	FILE << "listF.push_front(NoDefaultConstructorClass(2));" << ENDL; listF.push_front(NoDefaultConstructorClass(2));
	print_list(listF, "listF", f);
	FILE << "listF.push_front(NoDefaultConstructorClass(1));" << ENDL; listF.push_front(NoDefaultConstructorClass(1));
	print_list(listF, "listF", f);
	FILE << std::boolalpha << "listF.empty() = " << OUTPUT << listF.empty() << ENDL;
	FILE << "listF.push_back(NoDefaultConstructorClass(3));" << ENDL; listF.push_back(NoDefaultConstructorClass(3));
	print_list(listF, "listF", f);
	FILE << "listF.push_back(NoDefaultConstructorClass(4));" << ENDL; listF.push_back(NoDefaultConstructorClass(4));
	print_list(listF, "listF", f);
	FILE << SUBCATEGORY << "=====> Front and back" << ENDL;
	FILE << "listF.front() = NoDefaultConstructorClass(-9);" << ENDL; listF.front() = NoDefaultConstructorClass(-9);
	FILE << "listF.back() = NoDefaultConstructorClass(9);" << ENDL; listF.back() = NoDefaultConstructorClass(9);
	print_list(listF, "listF", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Exception-safety test with <ThrowingExceptionClass>, "
						"a class which throws an exception in copy constructor" << ENDL;
	FILE << "list<ThrowingExceptionClass> listG;" << ENDL; containerT<ThrowingExceptionClass> listG;
	FILE << "ThrowingExceptionClass testObject;" << ENDL; ThrowingExceptionClass testObject;
	FILE << "try {safelist.push_back(testobject);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {listG.push_back(testObject);}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	FILE << "listG.size() = " << OUTPUT << listG.size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Iterators" << ENDL;
	listA.clear();
	print_list(listA, "listA", f);
	FILE << "listA.begin() == listA.end() : " << OUTPUT << std::boolalpha << (listA.begin() == listA.end()) << ENDL;
	FILE << SUBCATEGORY << "(Pushing some values)" << ENDL;
	listA.push_back(1); listA.push_back(2); listA.push_back(3);
	print_list(listA, "listA", f);
	FILE << "list<int>::iterator it = listA.begin();" << ENDL; typename containerT<int>::iterator it = listA.begin();
	FILE << "list<int>::iterator ite = listA.end();" << ENDL; typename containerT<int>::iterator ite = listA.end();
	FILE << "(*it == listA.front()) = " << OUTPUT << std::boolalpha << (*it == listA.front()) << ENDL;
	FILE << "while (it != ite) {...; it++;}" << ENDL;
	while (it != ite)
	{
		FILE << "*it = " << OUTPUT << *it << ENDL;
		it++;
	}
	FILE << "it--;" << ENDL; it--;
	FILE << "(*it == listA.back()) = " << OUTPUT << std::boolalpha << (*it == listA.back()) << ENDL;
	FILE << "*it = 42;" << ENDL; *it = 42;
	print_list(listA, "listA", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Const iterators" << ENDL;
	FILE << "list<int>::const_iterator c_it = listA.begin();" << ENDL; typename containerT<int>::const_iterator c_it = listA.begin();
	FILE << "list<int>::const_iterator c_ite = listA.end();" << ENDL; typename containerT<int>::const_iterator c_ite = listA.end();
	FILE << "(*c_it == listA.front()) = " << OUTPUT << std::boolalpha << (*c_it == listA.front()) << ENDL;
	FILE << "while (c_it != c_ite) {...; c_it++;}" << ENDL;
	while (c_it != c_ite)
	{
		FILE << "*c_it = " << OUTPUT << *c_it << ENDL;
		//*c_it += 1;
		c_it++;
	}
	FILE << "c_it--;" << ENDL; c_it--;
	FILE << "(*c_it == listA.back()) = " << OUTPUT << std::boolalpha << (*c_it == listA.back()) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Reverse iterators" << ENDL;
	FILE << "list<int>::reverse_iterator r_it = listA.rbegin();" << ENDL; typename containerT<int>::reverse_iterator r_it = listA.rbegin();
	FILE << "list<int>::reverse_iterator r_ite = listA.rend();" << ENDL; typename containerT<int>::reverse_iterator r_ite = listA.rend();
	FILE << "while (r_it != r_ite) {...; r_it++;}" << ENDL;
	while (r_it != r_ite)
	{
		FILE << "*r_it = " << OUTPUT << *r_it << ENDL;
		r_it++;
	}
	FILE << "r_it--;" << ENDL; r_it--;
	FILE << "(*r_it == listA.front()) = " << OUTPUT << std::boolalpha << (*r_it == listA.front()) << ENDL;
	FILE << "*r_it = -42;" << ENDL; *r_it = -42;;
	print_list(listA, "listA", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Const reverse iterators" << ENDL;
	FILE << "list<int>::const_reverse_iterator cr_it = listA.rbegin();" << ENDL; typename containerT<int>::const_reverse_iterator cr_it = listA.rbegin();
	FILE << "list<int>::const_reverse_iterator cr_ite = listA.rend();" << ENDL; typename containerT<int>::const_reverse_iterator cr_ite = listA.rend();
	FILE << "while (cr_it != cr_ite) {...; cr_it++;}" << ENDL;
	while (cr_it != cr_ite)
	{
		FILE << "*cr_it = " << OUTPUT << *cr_it << ENDL;
		//*cr_it += 1;
		cr_it++;
	}
	FILE << "cr_it--;" << ENDL; cr_it--;
	FILE << "(*cr_it == listA.front()) = " << OUTPUT << std::boolalpha << (*cr_it == listA.front()) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Operator-> on iterators" << ENDL;
	FILE << "list<intStruct> listH;" << ENDL; containerT<intStruct> listH;
	FILE << "listH.push_back(intStruct(1));" << ENDL; listH.push_back(intStruct(1));
	FILE << "listH.push_back(intStruct(2));" << ENDL; listH.push_back(intStruct(2));
	print_list(listH, "listH", f);
	FILE << "list<intStruct>::iterator structIt = listH.begin();" << ENDL;
	typename containerT<intStruct>::iterator structIt = listH.begin();
	FILE << "structIt++;" << ENDL; structIt++;
	FILE << "structIt->a = " << OUTPUT << structIt->a << ENDL;
	FILE << "list<intStruct>::const_iterator c_structIt = listH.begin();" << ENDL;
	typename containerT<intStruct>::const_iterator c_structIt = listH.begin();
	FILE << "c_structIt++;" << ENDL; c_structIt++;
	FILE << "c_structIt->a = " << OUTPUT << c_structIt->a << ENDL;
	FILE << "list<intStruct>::reverse_iterator r_structIt = listH.rbegin();" << ENDL;
	typename containerT<intStruct>::reverse_iterator r_structIt = listH.rbegin();
	FILE << "r_structIt++;" << ENDL; r_structIt++;
	FILE << "r_structIt->a = " << OUTPUT << r_structIt->a << ENDL;
	FILE << "list<intStruct>::const_reverse_iterator cr_structIt = listH.rbegin();" << ENDL;
	typename containerT<intStruct>::const_reverse_iterator cr_structIt = listH.rbegin();
	FILE << "cr_structIt++;" << ENDL; cr_structIt++;
	FILE << "cr_structIt->a = " << OUTPUT << cr_structIt->a << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Assign" << ENDL;
	FILE << SUBCATEGORY << "=====> fill (2)" << ENDL;
	print_list(listA, "listA", f);
	FILE << "listA.assign(7, 100);" << ENDL; listA.assign(7, 100);
	print_list(listA, "listA", f);
	FILE << SUBCATEGORY << "=====> range (1)" << ENDL;
	print_list(listB, "listB", f);
	FILE << "listA.assign(listB.rbegin(), listB.rend());" << ENDL; listA.assign(listB.rbegin(), listB.rend());
	print_list(listA, "listA", f);
	FILE << "int myints[] = {1337, 4, 7};" << ENDL; int myints[] = {1337, 4, 7};
	FILE << "listA.assign(myints + 1, myints + 3);" << ENDL; listA.assign(myints + 1, myints + 3);
	print_list(listA, "listA", f);
	FILE << ENDL;

	FILE << CATEGORY << "===> Insert" << ENDL;
	FILE << SUBCATEGORY << "=====> insert single element (1)" << ENDL;
	listA.clear(); print_list(listA, "listA", f);
	FILE << "it = listA.begin();" << SUBCATEGORY << " (points to begin() = end())" << ENDL; it = listA.begin();
	FILE << "listA.insert(it, 1);" << ENDL; listA.insert(it, 1);
	print_list(listA, "listA", f);
	print_list(listC, "listC", f);
	FILE << "it = listC.begin(); ++it;" << SUBCATEGORY << " (points to 2)" << ENDL; it = listC.begin(); ++it;
	FILE << "listC.insert(it, 10);" << ENDL; listC.insert(it, 10);
	print_list(listC, "listC", f);
	FILE << "it = listC.begin();" << SUBCATEGORY << " (points now to number 1)" << ENDL; it = listC.begin();
	FILE << "listC.insert(it, 0);" << ENDL; listC.insert(it, 0);
	print_list(listC, "listC", f);
	FILE << "it = --listC.end();" << SUBCATEGORY << " (points now to number 5)" << ENDL; it = --listC.end();
	FILE << "listC.insert(it, 20);" << ENDL; listC.insert(it, 20);
	print_list(listC, "listC", f);
	FILE << "it = listC.end();" << SUBCATEGORY << " (points now to end(), after 5)" << ENDL; it = listC.end();
	FILE << "listC.insert(it, 6);" << ENDL; listC.insert(it, 6);
	print_list(listC, "listC", f);
	/*FILE << SUBCATEGORY << "=====> insert fill (2)" << ENDL;
	FILE << SUBCATEGORY << "(it still points on end() of listC)" << ENDL;
	FILE << "listC.insert(it, 3, 7);" << ENDL; listC.insert(it, 3, 7);
	print_list(listC, "listC", f);
	FILE << "it = listC.begin();" << SUBCATEGORY << " (points now to number 0)" << ENDL; it = listC.begin();
	FILE << "listC.insert(it, 2, -1);" << ENDL; listC.insert(it, 2, -1);
	print_list(listC, "listC", f);
	FILE << SUBCATEGORY << "=====> insert range (3)" << ENDL;
	FILE << "int myints[] = {1337, 4, 7};" << ENDL;*/
	FILE << ENDL;

	/*FILE << CATEGORY << "===> Erase" << ENDL;
	FILE << SUBCATEGORY << "=====> erase(iterator position)" << ENDL;
	FILE << ENDL;*/

	/*FILE << CATEGORY << "===> Swap" << ENDL;
	print_list(listA, "listA", f);
	FILE << ENDL;*/

	FILE << CATEGORY << "===> Operations" << ENDL;
	FILE << SUBCATEGORY << "=====> splice entire list (1)" << ENDL;
	FILE << "list<int> listempty;" << ENDL; containerT<int> listempty; print_list(listempty, "listempty", f);
	FILE << "list<int> listdest(1, 1);" << ENDL; containerT<int> listdest(1, 1); print_list(listdest, "listdest", f);
	FILE << "list<int> listdest3(3, 3);" << ENDL; containerT<int> listdest3(3, 3); print_list(listdest3, "listdest3", f);
	FILE << "listdest.splice(listdest.begin(), listempty);" << ENDL; listdest.splice(listdest.begin(), listempty);
	print_list(listdest, "listdest", f);
	FILE << "listempty.splice(listempty.begin(), listdest);" << ENDL; listempty.splice(listempty.begin(), listdest);
	print_list(listempty, "listempty", f);
	print_list(listdest, "listdest", f);
	FILE << "listempty.splice(listempty.end(), listdest3);" << ENDL; listempty.splice(listempty.end(), listdest3);
	print_list(listempty, "listempty", f);
	print_list(listdest3, "listdest3", f);
	FILE << "list<int> listdest2(2, 2);" << ENDL; containerT<int> listdest2(2, 2); print_list(listdest2, "listdest2", f);
	FILE << "listempty.splice(++listempty.begin(), listdest2);" << ENDL; listempty.splice(++listempty.begin(), listdest2);
	print_list(listempty, "listempty", f);
	FILE << SUBCATEGORY << "=====> splice single element (2)" << ENDL;
	FILE << "list<int> listdest4;" << ENDL; containerT<int> listdest4; print_list(listdest4, "listdest4", f);
	FILE << "listdest4.splice(listdest4.begin(), listempty, listempty.begin());" << ENDL; listdest4.splice(listdest4.begin(), listempty, listempty.begin());
	print_list(listdest4, "listdest4", f);
	print_list(listempty, "listempty", f);

	FILE << "listdest4.splice(listdest4.end(), listempty, --listempty.end());" << ENDL; listdest4.splice(listdest4.end(), listempty, --listempty.end());
	print_list(listdest4, "listdest4", f);
	print_list(listempty, "listempty", f);

	FILE << "listdest4.splice(++listdest4.begin(), listempty, listempty.begin());" << ENDL; listdest4.splice(++listdest4.begin(), listempty, listempty.begin());
	print_list(listdest4, "listdest4", f);
	print_list(listempty, "listempty", f);

	FILE << "listempty.push_front(4);" << ENDL; listempty.push_front(4); print_list(listempty, "listempty", f);
	FILE << "listdest4.splice(listdest4.end(), listempty, listempty.begin());" << ENDL; listdest4.splice(listdest4.end(), listempty, listempty.begin());
	print_list(listdest4, "listdest4", f);
	print_list(listempty, "listempty", f);

	FILE << "--listempty.begin() == listempty.end() : " << OUTPUT
	<< (--listempty.begin() == listempty.end()) << ENDL;
	FILE << "listempty.begin() == ++listempty.end() : " << OUTPUT
	<< (listempty.begin() == ++listempty.end()) << ENDL;

	FILE << "listempty.push_back(0);" << ENDL; listempty.push_back(0); print_list(listempty, "listempty", f);
	FILE << "listdest4.splice(listdest4.begin(), listempty, --listempty.end());" << ENDL; listdest4.splice(listdest4.begin(), listempty, --listempty.end());
	print_list(listdest4, "listdest4", f);
	print_list(listempty, "listempty", f);

	FILE << TITLE << "=> ENDING list tests" << ENDL;
	std::cout.rdbuf(coutbuf);
}

int	
main(void)
{
	test_list<std::list>();
    test_list<ft::list>();
}
