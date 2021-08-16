#include <iostream>
#include <vector>
#include <string>
#include "vector.hpp"

int main()
{
	ft::vector<int> v1;
	ft::vector<int> v2;

	for (size_t i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}

	for (size_t i = 0; i < 10; i++)
	{
		v2.push_back(i + 10);
	}

	ft::swap(v1, v2);
	// std::cout << v1.size() << std::endl;

	// for (size_t i = 0; i < v1.size(); i++)
	// {
	// 	std::cout << v1[i] << std::endl;
	// }

	ft::vector<int>::reverse_iterator rit = v1.rbegin();
	// std::cout << *rit  << std::endl;

	for (; rit != v1.rend(); ++rit)
	{
		std::cout << *rit  << " ";
	}
	std::cout << std::endl;


	std::cout << "v1  "<<  std::endl;
	ft::vector<int>::iterator it = v1.begin();
	for (; it != v1.end(); ++it)
	{
		std::cout << *it  << " ";
	}
	// ft::advance(it, 5);
	// std::cout << *it << std::endl;
	// ft::advance(it, -3);
	// std::cout << *it << std::endl;
	std::cout << std::endl;
	std::cout << "v2  "<<  std::endl;
	ft::vector<int>::iterator it2 = v2.begin();
	for (; it2 != v2.end(); ++it2)
	{
		std::cout << *it2  << " ";
	}
	std::cout << std::endl;
}
