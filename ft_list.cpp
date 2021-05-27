#include <iostream>
#include <list>

#include "list.hpp"

template<typename T>
void print_list(T& data){
	std::cout << data << std::endl;
}

int main()
{
	std::list<int> l1;
	l1.push_back(1);
	std::list<int>::iterator sit = l1.begin();
	print_list(*sit);




}
