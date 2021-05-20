#include <iostream>
#include <vector>
#include <string>
#include "vector.hpp"

int main()
{
	std::vector<int> v1;
	for (size_t i = 0; i < 8; i++)
	{
		v1.push_back(i);
	}
	// v1.clear();
	// v1.assign(5, 0);
	std::vector<int> v11;
	for (size_t i = 0; i < 10; i++)
	{
		v11.push_back(77);
	}
	std::vector<int>::reverse_iterator itv = v1.rbegin();
	std::vector<int>::reverse_iterator itv2 = v1.rend();
	std::cout << itv2 - itv << std::endl;

	std::vector<int>::const_iterator itv11 = v1.begin();
	std::vector<int>::iterator itv112 = v1.end();
	// std::vector<int>::iterator itv3 = v1.erase(itv + 5);
	// *itv11;
	// std::vector<int>::const_iterator itv111 = v1 += 3;


	// if (itv11 < itv112)
	// std::cout << "std const " << *itv11 << std::endl;
	// v1.insert(itv + 5, 10, 99);
	// std::cout << *itv3 << std::endl;
	// v1.insert(itv + 5, itv11, itv112);
	// for (size_t i = 0; i < v1.size(); i++)
	// {
	// 	std::cout << v1[i] << " ";
	// }
	// std::cout << std::endl;
	// std::cout << "size = " << v1.size() << std::endl;
	// std::cout << "cap = " << v1.capacity() << std::endl;
	// std::cout << "size = " << v1.size() << std::endl;
	// std::cout << "cap = " << v1.capacity() << std::endl;
	// v11.assign(itv, itv2);
	// for (; itv != itv2; ++itv)
	// {
	// 	std::cout << *itv << std::endl;
	// }

	// std::cout << v11.size() << std::endl;
	// std::cout << v11.capacity() << std::endl;
	// std::vector<int>::iterator itv = v1.begin();
	// std::vector<int>::iterator itv2 = v1.end();
	// std::cout << itv - itv2 << std::endl;

	// // if (itv > itv2)
	// itv[0] = 22;
	// std::cout << *itv << std::endl;
	// // std::cout << *itv2 << std::endl;


	ft::vector<int> v2;

	for (size_t i = 0; i < 8; i++)
	{
		v2.push_back(i);
		// std::cout << v2.size() << std::endl;

	}
	ft::vector<int> v22;

	for (size_t i = 0; i < 10; i++)
	{
		v22.push_back(77);
	}
	// v2.clear();
	// v2.assign(5, 0);

	// std::cout << v2.size() << std::endl;
	// std::cout << v2.capacity() << std::endl;

	// v22.swap(v2);
	// v2.push_back(2);
	// v2.push_back(3);
	ft::vector<int>::iterator it = v2.begin();
	ft::vector<int>::iterator it2 = v2.end();
	ft::vector<int>::const_iterator it22 = v2.begin();
	ft::vector<int>::iterator it222 = v2.end();
	// ft::vector<int>::iterator it3 = v2.erase(it + 5);
	// std::cout << v2.size() << std::endl;
	// ft::vector<int>::iterator it3 = v2.insert(it + 5, 99);

	// std::cout << "const_it " << *it22 << std::endl;
	// v22.assign(it, it2);
	// v2.insert(it + 5, 10, 99);
	// v2.insert(it + 5, it22, it222);
	// for (size_t i = 0; i < v2.size(); i++)
	// {
	// 	std::cout << v2[i] << " ";
	// }
	// std::cout << std::endl;

	ft::vector<int>::reverse_iterator rit = v2.rbegin();
	ft::vector<int>::reverse_iterator rend = v2.rend();
	// for (; rit !=  rend; ++rit)
	// {
		// std::cout << rit[0] << std::endl;
		// rit++;
		// std::cout << *rit << std::endl;
		// ++rit;
		// std::cout << *rit << std::endl;

		// rit--;
		// std::cout << *rit << std::endl;
		// --rit;
		// std::cout << *rit << std::endl;

		// ft::vector<int>::reverse_iterator rit2 = rit += 2;
		// std::cout << *rit2 << std::endl;
		// ft::vector<int>::reverse_iterator rit3 = rit2 -= 2;
		// std::cout << *rit3 << std::endl;
		std::cout << rend - rit << std::endl;



	// }
	for (size_t i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << " ";
	}
	std::cout << std::endl;

	ft::vector<int> v5;

	for (size_t i = 0; i < 8; i++)
	{
		v5.push_back(i);
		// std::cout << v2.size() << std::endl;

	}
	// std::cout << "size = " << v2.size() << std::endl;
	// std::cout << "cap = " << v2.capacity() << std::endl;
	// ft::vector<int> v4(v2.begin(), v2.end());
	// for (size_t i = 0; i < v4.size(); i++)
	// {
	// 	std::cout << v4[i] << " ";
	// }
	// std::cout << std::endl;

	// std::cout << v22.size() << std::endl;
	// std::cout << v22.capacity() << std::endl;


	// std::cout << it2 - it << std::endl;

	// for (; it != it2; ++it)
	// {
	// 	std::cout << *it << std::endl;
	// }

	// std::cout << ft::is_integer<int>::value << std::endl;

	// ft::vector<int>::iterator it2 = it + 7;
	// it[0] = 1223232;
	// it += 5;
	// ft::vector<int>::iterator it3 =  v2.begin();
	// if (it <= it2)
	// std::cout << *it << std::endl;
	// std::cout << *it2 << std::endl;
	// std::cout << "*****" << std::endl;
	// it--;
	// std::cout << *it << std::endl;

	// for (; it != it2; ++it)
	// {
	// std::cout << *it << std::endl;
	// }

	// v2.reserve(100);

	// ft::vector<int> v5 = v2;
	// std::cout << v5[2] << std::endl;

	// v2.pop_back();

	// std::cout << v2.empty() << std::endl;
	// std::cout << v5.size() << std::endl;
	// std::cout << v5.capacity() << std::endl;
	// std::cout << v2.size() << std::endl;
	// v2.resize(10, 7);
	// std::cout << v2.size() << std::endl;
	// for (size_t i = 0; i < v2.size(); ++i)
	// {
	// 	std::cout << v2[i] << " ";
	// }


	// std::cout << v2.capacity() << std::endl;
}
