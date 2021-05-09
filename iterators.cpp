#include <iostream>
#include <vector>
#include <list>
#include <iterator>



/*
	-InputIterator
	-ForwardIterator
	-BidirectoinalIterator
	-RandomAcceessIteartor
*/

// std::iterator_traits

/*
	нам нужно понять какой итератор приходит
*/

template <typename Iterator, typename IteratorCaterory>
void myAdvanceHelper(Iterator& it, int n, IteratorCaterory)
{
	for (int i = 0; i < n; ++i, ++it);
}

template <typename Iterator>
void myAdvanceHelper(Iterator& it, int n, std::random_access_iterator_tag)
{
	it += n;
}


template <typename Iterator>
void myAdvance(Iterator& it, int n)
{
	myAdvanceHelper(it, n, typename std::iterator_traits<Iterator>::iterator_category());
}

template <typename Iterator, typename IteratorCategory>
void myDistHelper(Iterator& it1, Iterator& it2, IteratorCategory)
{

}

template <typename Iterator>
void myDistHelper(Iterator& it1, Iterator& it2, std::random_access_iterator_tag)
{

}


template <typename Iterator>
void myDistance(Iterator& it1, Iterator& it2)
{
	myDistHelper(it1, it2, typename std::iterator_traits<Iterator>::iterator_category());
}

int main()
{
	std::list<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	std::list<int>::iterator it = v1.begin();

	// std::advance - различное поведение в зависимости от категории итератора
	// std::advance(it, 3);
	// myAdvance(it, 3);
	// std::cout << *it << std::endl;

	// std::distance - различное поведение в зависимости от категории итератора
	std::list<int>::iterator it2 = v1.end();
	// реализация похожа на advance
	std::cout << std::distance(it, it2) << std::endl;


}
