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
typename Iterator::difference_type myDistance(Iterator& it1, Iterator& it2)
{
	myDistHelper(it1, it2, typename std::iterator_traits<Iterator>::iterator_category());
}


// template <bool B, typename T, typename F>
// struct conditional {
// 	typename type = F;
// };

// template <typename T, typename F>
// struct conditional<true, T, F> {
// 	typename type = T;
// };


template <typename Iterator>
struct reverse_iterator
{
private:
	Iterator _iter;
public:

	reverse_iterator(const Iterator& iter) : _iter(iter) {}

	reverse_iterator<Iterator>& operator++() {
		--_iter;
		return *this;
	}

	reverse_iterator<Iterator>& operator--() {
		++_iter;
		return *this;
	}
};


template <typename T>
class Vector {
	T* _arr;
	size_t _sz;

public:
	struct iterator {
	private:
		T* _ptr;
	public:
		iterator(T* ptr) : _ptr(ptr) {}

		T& operator*() {
			return *_ptr;
		}

		T* operator->() {
			return _ptr;
		}

		iterator& operator++() {
			++_ptr;
			return *this;
		}
	};

	iterator begin() const {
		return iterator(_arr);
	}

	iterator end() const {
		return iterator(_arr + _sz);
	}

	using re

};


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
	myAdvance(it, 3);
	std::cout << *it << std::endl;

	// // std::distance - различное поведение в зависимости от категории итератора
	// std::list<int>::iterator it2 = v1.end();
	// // реализация похожа на advance
	// ptrdiff_t ptr_d;
	// // ptr_d = it2 - it;
	// std::cout << ptr_d << std::endl;
	// std::cout << std::distance(it, it2) << std::endl;


}
