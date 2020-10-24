#include "map.hpp"
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Color.hpp"
#define TITLE FG_CYAN << BOLD
#define SUBTITLE FG_RED << BOLD
#define CATEGORY FG_DGRAY << BOLD
#define SUBCATEGORY FG_DGRAY
#define OUTPUT FG_GREEN << UNDERLINED
#define FILE std::cout << RESET_ALL
using std::pair;
using std::make_pair;
using std::string;

class AllocatingClass
{
	public:
		AllocatingClass(void) : _array(new int[2]) {_array[0] = 0; _array[1] = 0;}
		AllocatingClass(AllocatingClass const & other) : _array(new int[2]) {(void)other; _array[0] = 0; _array[1] = 0;}
		~AllocatingClass() {delete[] _array;}
		AllocatingClass & operator=(AllocatingClass const & other) {(void)other; return (*this);}
		int* getArray(void) const {return (_array);}
	private:
		int* _array;
};
bool operator<(AllocatingClass const & a1, AllocatingClass const & a2) {return (a1.getArray()[0] < a2.getArray()[0]);}

class ThrowingExceptionClass
{
	public:
		ThrowingExceptionClass(void) : _a(2) {}
		ThrowingExceptionClass(int a) : _a(a) {}
		ThrowingExceptionClass(ThrowingExceptionClass const& other) {(void)other; throw std::exception();}
		~ThrowingExceptionClass() {}
		ThrowingExceptionClass & operator=(ThrowingExceptionClass const & other) {(void)other; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
};
bool operator<(ThrowingExceptionClass const & a1, ThrowingExceptionClass const & a2)
{return (a1.geta() < a2.geta());}
std::ostream& operator<<(std::ostream & os, ThrowingExceptionClass const & a) {os << a.geta(); return (os);}

class ThrowingExceptionClass2
{
	public:
		ThrowingExceptionClass2(void) : _a(2) {throw std::exception();}
		ThrowingExceptionClass2(int a) : _a(a) {}
		ThrowingExceptionClass2(ThrowingExceptionClass2 const& other) {_a = other._a;}
		~ThrowingExceptionClass2() {}
		ThrowingExceptionClass2 & operator=(ThrowingExceptionClass2 const & other) {(void)other; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
};
bool operator<(ThrowingExceptionClass2 const & a1, ThrowingExceptionClass2 const & a2)
{return (a1.geta() < a2.geta());}
std::ostream& operator<<(std::ostream & os, ThrowingExceptionClass2 const & a) {os << a.geta(); return (os);}

template<class T>
void
print_map(T const & map, std::string const & name)
{
	typename T::const_iterator begin = map.begin();
	typename T::const_iterator end = map.end();
	std::cout << OUTPUT << name << " = [ ";
	while (begin != end)
	{
		std::cout << "(" << begin->first << " : " << begin->second << ") ";
		++begin;
	}
	std::cout << "] Size : " << map.size() << ENDL;
}

template <template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > > class map>
void
test_map(void)
{
	FILE << TITLE << std::endl << "=> STARTING map tests" << ENDL;

	map<int, string> m2;
	m2[10] = "";
	m2[7] = "";
	m2[7] = "";
	m2[9] = "";
	m2[8] = "";
	m2[20] = "";
	m2[30] = "";
	m2[21] = "";
	m2[22] = "";
	m2[23] = "";
	m2[33] = "";
	m2[32] = "";
	m2[31] = "";
	
	//print_map(m2, "m2");

	/*begin = m2.begin();
	end = m2.end();
	while (end != begin)
	{
		--end;
		std::cout << "reverse(" << end->first << " : " << end->second << ") ";
	}*/

	/*typename map<int, string>::reverse_iterator rbegin = m2.rbegin();
	typename map<int, string>::reverse_iterator rend = m2.rend();
	while (rbegin != rend)
	{
		std::cout << "reverse(" << rbegin->first << " : " << rbegin->second << ") ";
		++rbegin;
	}

	typename map<int, string>::const_reverse_iterator crbegin = m2.rbegin();
	typename map<int, string>::const_reverse_iterator crend = m2.rend();
	while (crbegin != crend)
	{
		std::cout << "reverse(" << crbegin->first << " : " << crbegin->second << ") ";
		++crbegin;
	}*/
	//(--crbegin)->second = "A";

	//begin->first = 1;

	/*map<int, string> m2;
	print_map(m2, "m2");
	typename map<int, string>::iterator begin = m2.begin();
	++begin;*/

	/*typename map<int, string>::const_iterator cbegin = m2.begin();
	FILE << "*cbegin : " << OUTPUT << cbegin->first << ENDL;*/
	//cbegin->second = "A";




	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << "map<int, string> mapA;" << ENDL; map<int, string> mapA;
	print_map(mapA, "mapA");
	FILE << std::boolalpha << "mapA.empty() = " << OUTPUT << mapA.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	FILE << "pair<int, string> pairArray[] = {make_pair(1, \"A\"), make_pair(2, \"B\"), make_pair(3, \"C\")};" << ENDL;
	pair<int, string> pairArray[] = {make_pair(1, "A"), make_pair(2, "B"), make_pair(3, "C")};
	FILE << "map<int, string> mapB(pairArray, pairArray + 3);" << ENDL;
	map<int, string> mapB(pairArray, pairArray + 3);
	print_map(mapB, "mapB");
	FILE << std::boolalpha << "mapB.empty() = " << OUTPUT << mapB.empty() << ENDL;
	FILE << "map<int, string> mapC(pairArray, pairArray);" << ENDL;
	map<int, string> mapC(pairArray, pairArray);
	print_map(mapC, "mapC");
	FILE << std::boolalpha << "mapC.empty() = " << OUTPUT << mapC.empty() << ENDL;
	FILE << "pair<int, string> pairArray2[] = {make_pair(10, \"\"), make_pair(7, \"\"), make_pair(7, \"\"), make_pair(9, \"\"), make_pair(8, \"\"), make_pair(20, \"\"), make_pair(30, \"\"), make_pair(21, \"\"), make_pair(22, \"\"), make_pair(23, \"\"), make_pair(33, \"\"), make_pair(32, \"\"), make_pair(31, \"\")};" << ENDL;
	pair<int, string> pairArray2[] = {make_pair(10, ""), make_pair(7, ""), make_pair(7, ""), make_pair(9, ""), make_pair(8, ""), make_pair(20, ""), make_pair(30, ""), make_pair(21, ""), make_pair(22, ""), make_pair(23, ""), make_pair(33, ""), make_pair(32, ""), make_pair(31, "")};
	FILE << "map<int, string> mapD(pairArray2, pairArray2 + 13);" << ENDL;
	map<int, string> mapD(pairArray2, pairArray2 + 13);
	print_map(mapD, "mapD");
	FILE << std::boolalpha << "mapD.empty() = " << OUTPUT << mapD.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Copy constructor" << ENDL;
	print_map(mapD, "mapD");
	FILE << "map<int, string> mapE(mapD);" << ENDL; map<int, string> mapE(mapD);
	print_map(mapD, "mapD");
	print_map(mapE, "mapE");
	FILE << ENDL;

	FILE << CATEGORY << "===> Destructor" << ENDL;
	AllocatingClass allocatedInstance;
	FILE << "pair<AllocatingClass, AllocatingClass> pairArray3[] = {...};" << ENDL;
	pair<AllocatingClass, AllocatingClass> pairArray3[] = {make_pair(allocatedInstance, allocatedInstance), make_pair(allocatedInstance, allocatedInstance), make_pair(allocatedInstance, allocatedInstance)};
	FILE << "map<AllocatingClass, AllocatingClass> allocatingMap(pairArray3, pairArray3 + 3);" << ENDL;
	map<AllocatingClass, AllocatingClass> allocatingMap(pairArray3, pairArray3 + 3);
	FILE << ENDL;

	FILE << SUBTITLE << "Operator" << ENDL;
	FILE << CATEGORY << "===> Operator=" << ENDL;
	print_map(mapB, "mapB");
	print_map(mapC, "mapC");
	FILE << "mapB = mapC;" << ENDL; mapB = mapC;
	print_map(mapB, "mapB");
	FILE << "mapB.insert(make_pair(0, ""));" << ENDL; mapB.insert(make_pair(0, ""));
	print_map(mapB, "mapB");
	print_map(mapC, "mapC");
	FILE << "mapB = mapC;" << ENDL; mapB = mapC;
	print_map(mapB, "mapB");
	FILE << "mapB = mapD;" << ENDL; mapB = mapD;
	print_map(mapB, "mapB");
	print_map(mapD, "mapD");
	FILE << ENDL;

	FILE << SUBTITLE << "Iterators" << ENDL;
	FILE << CATEGORY << "===> Iterators" << ENDL;
	FILE << ENDL;

	FILE << SUBTITLE << "Element access" << ENDL;
	FILE << CATEGORY << "===> operator[]" << ENDL;
	FILE << "mapA[10] = \"A\";" << ENDL; mapA[10] = "A";
	FILE << "mapA[7] = \"B\";" << ENDL; mapA[7] = "B";
	FILE << "mapA[7] = \"C\";" << ENDL; mapA[7] = "C";
	FILE << "mapA[9] = \"D\";" << ENDL; mapA[9] = "D";
	FILE << "mapA[8] = \"E\";" << ENDL; mapA[8] = "E";
	FILE << "mapA[20] = \"F\";" << ENDL; mapA[20] = "F";
	FILE << "mapA[30] = \"G\";" << ENDL; mapA[30] = "G";
	FILE << "mapA[21] = \"H\";" << ENDL; mapA[21] = "H";
	FILE << "mapA[22] = \"I\";" << ENDL; mapA[22] = "I";
	FILE << "mapA[23] = \"J\";" << ENDL; mapA[23] = "J";
	FILE << "mapA[33] = \"K\";" << ENDL; mapA[33] = "K";
	FILE << "mapA[32] = \"L\";" << ENDL; mapA[32] = "L";
	FILE << "mapA[31] = \"M\";" << ENDL; mapA[31] = "M";
	FILE << "mapA[0] : " << OUTPUT << mapA[0] << ENDL;
	FILE << "mapA[23] : " << OUTPUT << mapA[23] << ENDL;
	FILE << "mapA[23] = \"JJ\";" << ENDL; mapA[23] = "JJ";
	print_map(mapA, "mapA");
	#ifdef CONST_TEST
	FILE << "map<int, string> const const_map(pairArray2, pairArray2 + 13);" << ENDL; map<int, string> const const_map(pairArray2, pairArray2 + 13);
	FILE << "const_map[23] : " << OUTPUT << const_map[23] << ENDL;
	#endif
	FILE << ENDL;

	FILE << SUBTITLE << "Modifiers" << ENDL;
	FILE << CATEGORY << "===> Exception-safety test with ThrowingExceptionClass, "
						"a class which throws an exception in copy constructor" << ENDL;
	FILE << "ThrowingExceptionClass throwingInstance;" << ENDL; ThrowingExceptionClass throwingInstance;
	FILE << "map<int, ThrowingExceptionClass> mapF;" << ENDL; map<int, ThrowingExceptionClass> mapF;
	FILE << "try {mapF.insert(make_pair(0, throwingInstance);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {mapF.insert(make_pair(0, throwingInstance));}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	print_map(mapF, "mapF");
	FILE << ENDL;

	FILE << CATEGORY << "===> Exception-safety test with ThrowingExceptionClass2, "
						"a class which throws an exception in default constructor" << ENDL;
	FILE << "map<int, ThrowingExceptionClass2> mapG;" << ENDL; map<int, ThrowingExceptionClass2> mapG;
	FILE << "ThrowingExceptionClass2 throwingInstance2(3);" << ENDL; ThrowingExceptionClass2 throwingInstance2(3);
	FILE << "try {mapG.insert(make_pair(0, throwingInstance2);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {mapG.insert(make_pair(0, throwingInstance2));}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	print_map(mapG, "mapG");
	FILE << "try {cout << \"mapG[23] : \" << mapG[23];}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {FILE << "mapG[23] : " << OUTPUT << mapG[23] << ENDL;}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	print_map(mapG, "mapG");
	FILE << ENDL;

	FILE << CATEGORY << "===> insert" << ENDL;
	FILE << SUBCATEGORY << "=====> single element (1)" << ENDL;
	print_map(mapA, "mapA");
	FILE << "pair<map<int, string>::iterator, bool> res;" << ENDL;
	pair<typename map<int, string>::iterator, bool> res;
	FILE << "res = mapA.insert(make_pair(-1, \"Z\"));" << ENDL; res = mapA.insert(make_pair(-1, "Z"));
	FILE << "(res.first)->first : " << OUTPUT << (res.first)->first << ENDL;
	FILE << "(res.first)->second : " << OUTPUT << (res.first)->second << ENDL;
	FILE << "res.second : " << OUTPUT << std::boolalpha << res.second << ENDL;
	FILE << "res = mapA.insert(make_pair(15, \"Y\"));" << ENDL; res = mapA.insert(make_pair(15, "Y"));
	FILE << "(res.first)->first : " << OUTPUT << (res.first)->first << ENDL;
	FILE << "(res.first)->second : " << OUTPUT << (res.first)->second << ENDL;
	FILE << "res.second : " << OUTPUT << std::boolalpha << res.second << ENDL;
	FILE << "res = mapA.insert(make_pair(7, \"CC\"));" << ENDL; res = mapA.insert(make_pair(7, "CC"));
	FILE << "(res.first)->first : " << OUTPUT << (res.first)->first << ENDL;
	FILE << "(res.first)->second : " << OUTPUT << (res.first)->second << ENDL;
	FILE << "res.second : " << OUTPUT << std::boolalpha << res.second << ENDL;
	print_map(mapA, "mapA");
	FILE << SUBCATEGORY << "=====> with hint (2)" << ENDL;
	//FILE << "map<int, string>::iterator res2;" << ENDL; typename map<int, string>::iterator res2;
	//FILE << "map<int, string>::iterator hint = mapA.begin();" << ENDL;
	//typename map<int, string>::iterator hint = mapA.begin();
	//FILE << "res2 = mapA.insert(hint, make_pair(-3, \"X\"));" << ENDL; res2 = mapA.insert(hint, make_pair(-3, "X"));
	//FILE << "res2->first : " << OUTPUT << res2->first << ENDL;
	//FILE << "res2->second : " << OUTPUT << res2->second << ENDL;
	//FILE << "res2 = mapA.insert(hint, make_pair(11, \"W\"));" << ENDL; res2 = mapA.insert(hint, make_pair(11, "W"));
	//FILE << "res2->first : " << OUTPUT << res2->first << ENDL;
	//FILE << "res2->second : " << OUTPUT << res2->second << ENDL;
	//print_map(mapA, "mapA");
	FILE << SUBCATEGORY << "=====> range (3)" << ENDL;
	//FILE << "mapA.insert(pairArray, pairArray);" << ENDL; mapA.insert(pairArray, pairArray);
	//print_map(mapA, "mapA");
	//FILE << "mapA.insert(pairArray, pairArray + 1);" << ENDL; mapA.insert(pairArray, pairArray + 1);
	//print_map(mapA, "mapA");
	//FILE << "mapA.insert(pairArray, pairArray + 3);" << ENDL; mapA.insert(pairArray, pairArray + 3);
	//print_map(mapA, "mapA");
	//FILE << "mapA.insert(pairArray2, pairArray2 + 13);" << ENDL; mapA.insert(pairArray2, pairArray2 + 13);
	//print_map(mapA, "mapA");
	FILE << ENDL;

	FILE << TITLE << "=> ENDING map tests" << ENDL << ENDL;
}

int
main(void)
{
    test_map<ft::map>();
}
