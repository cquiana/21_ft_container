#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <time.h>
#include "utils.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"


template <typename Cont>
void print_vector(Cont& cont) {
	typename Cont::iterator it1 = cont.begin();
	typename Cont::iterator it2 = cont.end();

	for (; it1 != it2; ++it1)
		std::cout << *it1 << " ";

	std::cout << "vector size = " << cont.size() << " capacity = " << cont.capacity() << std::endl;
	if (cont.empty())
		std::cout << "vector is empty\n";


}

void test_int_vector() {

	// std::vector<int> sVec;
	std::cout << "CONSTRUCTORS" << std::endl;

	ft::vector<int> first;
	ft::vector<int> second (4, 100);
	ft::vector<int> third (second.begin(),second.end());
	ft::vector<int> fourth (third);

	print_vector(first);
	print_vector(second);
	print_vector(third);
	print_vector(fourth);

	first.push_back(10);
	first.push_back(3);
	first.push_back(-21);
	first.push_back(0);
	first.push_back(101);
	print_vector(first);

	std::cout << "ELEMENT ACCESS" << std::endl;

	std::cout << "operator[]: " << first[1] << std::endl;
	const ft::vector<int> const_vec(5, 101);
	std::cout << "const operator[]: " << const_vec[1] << std::endl;

	std::cout << "at(): " << std::endl;
	try {
		std::cout << first.at(10) << std::endl;
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "front(): " << first.front() << std::endl;
	std::cout << "back(): " << first.back() << std::endl;


	std::cout << "RESERVE & RESIZE" << std::endl;
	// std::vector<int> sVec(4, 100);
	std::cout << "max_size(): " << first.max_size() << std::endl;
	// std::cout << "max_size(): " << sVec.max_size() << std::endl;
	first.reserve(10);
	print_vector(first);

	first.resize(2);
	print_vector(first);

	ft::vector<int> a(10, 21);
	print_vector(a);
	a.assign(5, 42);
	print_vector(a);

	ft::vector<int> c;
	ft::vector<int>::iterator it1 = a.begin();
	ft::vector<int>::iterator it2 = a.end();
	++it1;

	std::cout << "ASSIGN" << std::endl;

	c.assign(it1, it2);
	print_vector(c);
	c.clear();
	print_vector(c);


	for (size_t i = 0; i < 10; i++) {
		a.push_back(i);
	}
	print_vector(a);
	for (size_t i = 0; i < 5; i++) {
		a.pop_back();
	}

	std::cout << "ITERATORS" << std::endl;

	ft::vector<int> d;
	for (size_t i = 0; i < 10; i++) {
		d.push_back(i);
	}

	const ft::vector<int> e(d);

	ft::vector<int>::iterator itb = d.begin();
	std::cout << "random access iteraror (5th element): " << *itb + 4 << std::endl;
	d.erase(itb + 4);
	d.erase(itb + 5, itb + 7);
	ft::vector<int>::iterator ite = d.end();
	for (; itb != ite; ++itb) {
		std::cout << *itb << " ";
	}
	std::cout << std::endl;

	ft::vector<int>::const_iterator itcb  = e.begin();
	// std::cout << *ictb + 4 << std::endl;
	ft::vector<int>::const_iterator itce = e.end();
	for (; itcb != itce; ++itcb) {
		std::cout << *itcb << " ";
	}
	std::cout << std::endl;

	ft::vector<int>::reverse_iterator itrb = d.rbegin();
	ft::vector<int>::reverse_iterator itre = d.rend();
	for (; itrb != itre; ++itrb) {
		std::cout << *itrb << " ";
	}
	std::cout << std::endl;

	ft::vector<int>::const_reverse_iterator itcrb = e.rbegin();
	ft::vector<int>::const_reverse_iterator itcre = e.rend();
	for (; itcrb != itcre; ++itcrb) {
		std::cout << *itcrb << " ";
	}
	std::cout << std::endl;

	std::cout << "REALATION OPERATORS" << std::endl;
	ft::vector<int> x (6,400);
	ft::vector<int> y (7,200);

	if (x == y)
		std::cout << "x and y are equal\n";
	if (x != y)
		std::cout << "x and y are not equal\n";
	if (x < y)
		std::cout << "x is less than y\n";
	if (x > y)
		std::cout << "x is greater than y\n";
	if (x <= y)
		std::cout << "x is less than or equal to y\n";
	if (x >= y)
		std::cout << "x is greater than or equal to y\n";

	std::cout << "SWAP" << std::endl;
	x.swap(y);
	print_vector(x);
	print_vector(y);

	ft::swap(x, y);
	print_vector(x);
	print_vector(y);
}

void test_string_vector() {


	std::cout << "CONSTRUCTORS" << std::endl;

	ft::vector<std::string> s1;
	ft::vector<std::string> s2 (4, "test");
	ft::vector<std::string> s3 (s2.begin(), s2.end());
	ft::vector<std::string> s4 (s3);

	print_vector(s1);
	print_vector(s2);
	print_vector(s3);
	print_vector(s3);

	s1.push_back("a");
	s1.push_back("b");
	s1.push_back("c");
	s1.push_back("d");
	s1.push_back("e");
	print_vector(s1);

	std::cout << "ELEMENT ACCESS" << std::endl;

	std::cout << "operator[]: " << s1[1] << std::endl;

	std::cout << "REALATION OPERATORS" << std::endl;

	if (s3 == s2)
		std::cout << "s3 and s2 are equal\n";
	if (s1 != s2)
		std::cout << "s1 and s2 are not equal\n";
	if (s3 < s4)
		std::cout << "s3 is less than s4\n";
	if (s1 > s4)
		std::cout << "s1 is greater than s4\n";
	if (s2 <= s4)
		std::cout << "s2 is less than or equal to s4\n";
	if (s3 >= s4)
		std::cout << "s3 is greater than or equal to s4\n";

	std::cout << "SWAP" << std::endl;
	s1.swap(s2);
	print_vector(s1);
	print_vector(s2);

	ft::swap(s1, s2);
	print_vector(s1);
	print_vector(s2);

}

void test_int_stack() {

	ft::stack<int> ftStack;
	ftStack.push(21);
	ftStack.push(101);
	ftStack.push(555);
	ftStack.push(-88);
	std::cout << "top(): " << ftStack.top() << std::endl;
	ftStack.pop();
	std::cout << "top() after pop(): " << ftStack.top() << std::endl;
	if (!ftStack.empty())
		std::cout << "ftStack is not empty\n";
	std::cout << std::endl;

	std::cout << "STACK ON LIST" << std::endl;

	ft::stack<int, std::list<int> > lStack;
	if (lStack.empty())
		std::cout << "lStack is empty\n";
	lStack.push(22);
	lStack.push(10);
	lStack.push(45);
	lStack.push(130);
	std::cout << "lStack size = " << lStack.size() << std::endl;
	lStack.pop();
	std::cout << "lStack size after pop = " << lStack.size() << std::endl;

	std::cout << std::endl;

	std::cout << "REALATION OPERATORS" << std::endl;


	ft::stack<int> ftStack2;
	ftStack2.push(21);
	ftStack2.push(101);
	ftStack2.push(-555);

	ft::stack<int> ftStack3;
	ftStack3.push(21);
	ftStack3.push(101);
	ftStack3.push(555);

	if (ftStack == ftStack3)
		std::cout << "ftStack == ftStack2\n";
	if (ftStack != ftStack2)
		std::cout << "ftStack != ftStack2\n";
	if (ftStack < ftStack2)
		std::cout << "ftStack < ftStack2\n";
	if (ftStack > ftStack2)
		std::cout << "ftStack > ftStack2\n";
	if (ftStack <= ftStack3)
		std::cout << "ftStack <= ftStack3\n";
	if (ftStack >= ftStack2)
		std::cout << "ftStack >= ftStack2\n";
}

void test_string_stack() {
	ft::stack<std::string> ftStack;
	ftStack.push("abc");
	ftStack.push("hello");
	ftStack.push("world");
	ftStack.push("21school");
	std::cout << "top(): " << ftStack.top() << std::endl;
	ftStack.pop();
	std::cout << "top() after pop(): " << ftStack.top() << std::endl;
	if (!ftStack.empty())
		std::cout << "ftStack is not empty\n";
	std::cout << std::endl;

	std::cout << "STACK ON LIST" << std::endl;

	ft::stack<std::string, std::list<std::string> > lStack;
	if (lStack.empty())
		std::cout << "lStack is empty\n";
	lStack.push("Mary");
	lStack.push("Kate");
	lStack.push("Sam");
	lStack.push("Ostin");
	std::cout << "lStack size = " << lStack.size() << std::endl;
	lStack.pop();
	std::cout << "lStack size after pop = " << lStack.size() << std::endl;

	std::cout << std::endl;

	std::cout << "REALATION OPERATORS" << std::endl;


	ft::stack<std::string> ftStack2;
	ftStack2.push("abc");
	ftStack2.push("hello");
	ftStack2.push("world!");

	ft::stack<std::string> ftStack3;
	ftStack3.push("abc");
	ftStack3.push("hello");
	ftStack3.push("world");

	if (ftStack == ftStack3)
		std::cout << "ftStack == ftStack2\n";
	if (ftStack != ftStack2)
		std::cout << "ftStack != ftStack2\n";
	if (ftStack < ftStack2)
		std::cout << "ftStack < ftStack2\n";
	if (ftStack > ftStack2)
		std::cout << "ftStack > ftStack2\n";
	if (ftStack <= ftStack3)
		std::cout << "ftStack <= ftStack3\n";
	if (ftStack >= ftStack2)
		std::cout << "ftStack >= ftStack2\n";

}

template<class T>
void print_map(T const& map) {
	typename T::const_iterator it1 = map.begin();
	typename T::const_iterator it2 = map.end();
	for (; it1 != it2; ++it1) {
		std::cout << "Key = " << (*it1).first << " Value = " << (*it1).second << " | ";
	}
	std::cout << std::endl;

}


bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};


void test_int_map() {

	std::cout << "CONSTRUCTORS" << std::endl;
	ft::map<int, int> m1;
	// std::cout << m1.size() << std::endl;
	m1[1] = 101;
	m1[2] = 201;
	m1[3] = 301;
	m1[4] = 301;

	ft::map<int, int> m2(m1.begin(), m1.end());
	ft::map<int, int> m3(m2);

	print_map(m1);
	print_map(m2);
	print_map(m3);

	std::cout << "ITERATORS" << std::endl;
	for (ft::map<int, int>::iterator it = m1.begin(); it != m1.end(); ++it)
		std::cout << "Key = " << (*it).first << " Value = " << (*it).second << " | ";
	std::cout << std::endl;

	for (ft::map<int, int>::reverse_iterator it = m1.rbegin(); it != m1.rend(); ++it)
		std::cout << "Key = " << (*it).first << " Value = " << (*it).second << " | ";
	std::cout << std::endl;


	std::cout << "ELEMENT ACCESS" << std::endl;

	std::cout << "operator []: key 1 = " << m1[1] << std::endl;
	m1[5];
	print_map(m1);

	std::cout << "CAPACITY" << std::endl;
	if (!m1.empty())
		std::cout << "Map is not empty | size = " << m1.size() << " max_size = " << m1.max_size() << std::endl;


	std::cout << "MODIFIERS" << std::endl;
	std::cout << "insert" << std::endl;
	ft::map<int, int> m5;
	for (size_t i = 0; i < 10; ++i)
		m5.insert(ft::make_pair(i, i * 10));
	print_map(m5);

	std::cout << m5.insert(ft::make_pair(0, 100)).second << std::endl;
	m2.clear();
	if (m2.empty())
		std::cout << "Map 2 is empty | size = " << m1.size() << std::endl;
	m2.insert(m5.begin(), --(m5.end()));
	print_map(m2);

	std::cout << "erase" << std::endl;
	m5.erase(m5.begin());
	print_map(m2);
	m5.erase(m5.begin(), m5.end());
	if (m5.empty())
		std::cout << "Map 5 is empty | size = " << m5.size() << std::endl;
	std::cout << m2.erase(1) << " | size = " << m2.size() << std::endl;
	print_map(m2);

	std::cout << "swap" << std::endl;
	m5.insert(m3.begin(), m3.end());
	m2.swap(m5);
	print_map(m2);
	print_map(m5);

	std::cout << "OBSERVERS" << std::endl;
	std::cout << m2.key_comp()(1, 2) << std::endl;
	std::cout << m2.value_comp()(ft::make_pair(1, 1), ft::make_pair(1, 2)) << std::endl;

	std::cout << "OPERATIONS" << std::endl;
	std::cout << "find" << std::endl;

	ft::map<int, int>::iterator fnd = m2.find(0);
	if (fnd == m2.end())
		std::cout << "Element not found" << std::endl;
	ft::map<int, int>::iterator fnd2 = m2.find(3);
	if (fnd2 != m2.end())
		std::cout << (*fnd2).second << std::endl;

	std::cout << "count" << std::endl;
	std::cout << m1.count(2) << std::endl;

	std::cout << "lower bound" << std::endl;
	std::cout << m1.lower_bound(2)->second << std::endl;

	std::cout << "upper bound" << std::endl;
	std::cout << m1.upper_bound(2)->second << std::endl;

	std::cout << "equal range" << std::endl;
	std::cout << m1.equal_range(2).first->second << std::endl;
	std::cout << m1.equal_range(2).second->second << std::endl;


}

int main() {

	// clock_t start = clock();

	std::cout << YELLOW << "=================VECTOR INT=================" << std::endl << RESET;
	test_int_vector();
	std::cout << std::endl;

	std::cout << YELLOW << "=================VECTOR STRING=================" << std::endl << RESET;
	test_string_vector();
	std::cout << std::endl;

	std::cout << YELLOW << "=================MAP INT=================" << std::endl << RESET;
	test_int_map();
	std::cout << std::endl;

	std::cout << YELLOW << "=================MAP STRING=================" << std::endl << RESET;
	std::cout << std::endl;

	std::cout << YELLOW << "=================STACK INT=================" << std::endl << RESET;
	test_int_stack();
	std::cout << std::endl;

	std::cout << YELLOW << "=================STACK STRING=================" << std::endl << RESET;
	test_string_stack();
	std::cout << std::endl;

	// clock_t end = clock();
	// double sec = (double)(end - start) / CLOCKS_PER_SEC;
	// std::cout << sec << std::endl;

	return 0;
}
