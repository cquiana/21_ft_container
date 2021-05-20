#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <limits>

#include "VectoIterator.hpp"
#include "is_integer.hpp"

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef	T											value_type;
		typedef	Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef random_access_iterator<T>					iterator;
		// typedef const_random_access_iterator<T>				const_iterator;
		// typedef reverse_random_access_iterator<T>			reverse_iterator;
		// typedef const_reverse_random_access_iterator<T>		const_reverse_iterator;

		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;

	private:
		value_type*		_array;
		size_type		_size;
		size_type 		_capacity;
		allocator_type	_alloc;

	public:
		explicit vector(const allocator_type& alloc = allocator_type()) : _array(NULL), _size(0), _capacity(0), _alloc(alloc) {}

		// Constructs a container with n elements. Each element is a copy of val.
		explicit vector(size_type n, const value_type& value = value_type(),
				const allocator_type& alloc = allocator_type())
		{
			_alloc = alloc;
			_array = _alloc.allocate(n);
			_size = n;
			_capacity = n;
			for (size_type i = 0; i < n; ++i) {
				_alloc.construct(_array + i, value);
			}
		}

		template <class InputIterator>
		vector (typename enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type first, InputIterator last,
				const allocator_type& alloc = allocator_type()) {
					_alloc = alloc;
					difference_type n = last - first;
					_array = _alloc.allocate(n);
					_size = n;
					_capacity = n;
					for (size_type i = 0; first != last; ++i, ++first) {
						_alloc.construct(_array + i, *first);
					}
				}
				//  Constructs a container with as many elements as the range [first,last), with each element
				// constructed from its corresponding element in that range, in the same order.

		vector& operator=(const vector& x) {
			if (this != &x) {
				_alloc = x._alloc;
				for ( size_type i = 0; i < _size; ++i) {
					_alloc.destroy(_array + i);
				}
				if (_capacity) {
					_alloc.deallocate(_array, _capacity);
				}
				reserve(x._capacity);
				for (size_type i = 0; i < x._size; ++i) {
					_alloc.construct(_array + i, x._array[i]);
				}
				_size = x._size;
			}
			return *this;
		}

		vector (const vector& x) {
			*this = x;
		}

		virtual ~vector() {
			clear();
			if (_capacity > 0) {
				_alloc.deallocate(_array, _capacity);
			}
		}
		// This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.

		/* ===== ITERATORS ==== */


		iterator begin() {
			return (iterator(_array));
		}
		// const_iterator begin() const;

		iterator end() {
			return (iterator(_array + _size));
		}
		// const_iterator end() const;

		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;

		// reverse_iterator rend();
		// const_reverse_iterator rend() const;


		/*  ==== SIZE =====  */

		size_type size() const { return _size;}

		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / (sizeof(value_type)));
		}

		size_type capacity() const { return _capacity; }

		bool empty() const { return _size == 0; }

		void resize(size_type n, const value_type& value = value_type())
		{
			if (n == _size)
				return;
			while (_size != n){
				if (_size > n)
					pop_back();
				else
					push_back(value);
			}
		}

		void reserve(size_type n)
		{
			if (n <= _capacity)
				return;
			value_type *tmp = _alloc.allocate(n);
			for (size_t i = 0; i < _size; ++i) {
				_alloc.construct(tmp + i, _array[i]);
				// new(tmp + i) T(_array[i]);
			}
			for (size_t i = 0; i < _size; ++i) {
				_alloc.destroy(_array + i);
				// (_array + i)->~T();
			}
			_array = tmp;
			_capacity = n;
		}

		/* ==== Element access: ===== */

		reference operator[](size_type index) { return _array[index]; }

		const_reference operator[](size_type index) const { return _array[index]; }

		reference at(size_type index) {
			if (index > _size) throw std::out_of_range("Out of range");
			return _array[index];
		}

		const_reference at(size_type index) const {
			if (index > _size) throw std::out_of_range("Out of range");
			return _array[index];
		}

		reference front() { return _array[0]; }

		const_reference front() const { return _array[0]; }

		reference back() { return _array[_size - 1]; }

		const_reference back() const { return _array[_size - 1]; }

		/* ==== Modifiers: ===== */

		void assign(size_type n, const value_type& value) {
			// reserve(n);
			clear();
			// capacity ???
			for (size_type i = 0; i < n; ++i) {
				_alloc.construct(_array + i, value);
			}
			_size = n;
		}

		template <class InputIterator>
		void assign(typename enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type first,
					InputIterator last) {
			clear();
			difference_type newCap = last - first;
			reserve(newCap);
			for (; first != last; ++first)
				push_back(*first);
		}


		void push_back(const value_type& value)
		{
			if (_size == _capacity) {
				if (!_size) {
					reserve(1);
					_alloc.construct(_array, value);
					// new (_array + _size) value_type(value);
					++_size;
					return;
				}
				reserve (_capacity * 2);
			}
			_alloc.construct(_array + _size, value);
			// new (_array + _size) value_type(value);
			++_size;
		}

		void pop_back() {
			_alloc.destroy(_array + _size - 1);
			// (_array + _size - 1)->~value_type();
			--_size;
		}

		iterator insert (iterator position, const value_type& val) {
			difference_type diff = position - this->begin();
			if (_size + 1 > _capacity)
				reserve(_capacity * 2);
			for (size_type i = _size; i > diff; --i) {
				_alloc.construct(_array + i, _array[i - 1]);
			}
			_array[diff] = val;
			++_size;
			return (begin() + diff);
		}

		void insert (iterator position, size_type n, const value_type& val) {
			difference_type diff = position - this->begin();
			if (_size + n > _capacity) {
				if (_capacity * 2 > _size + n)
					reserve(_capacity * 2);
				else
					reserve(_capacity + n);
			}
			for (size_type i = _size + n; i > diff + n; --i) {
				_alloc.construct(_array + (i - 1), _array[i - n - 1]);
			}
			for (size_type i = diff; i < n + diff; ++i) {
				_array[i] = val;
			}
			_size += n;
		}

		template <class InputIterator>
		void insert (iterator position,
			typename enable_if<!ft::is_integer<InputIterator>::value,
			InputIterator>::type first, InputIterator last) {
			difference_type diff = position - this->begin();
			difference_type count = last - first;
			if (_size + count > _capacity) {
				if (_capacity * 2 > _size + count)
					reserve(_capacity * 2);
				else
					reserve(_capacity + count);
			}
			for (size_type i = _size + count; i > diff + count; --i) {
				_alloc.construct(_array + (i - 1), _array[i - count - 1]);
			}
			for (; first != last; ++first, ++diff) {
				_array[diff] = *first;
			}
			_size += count;
		}

		iterator erase (iterator position) {
			iterator endit = this->end();
			iterator res = position;
			_alloc.destroy(&*position);
			for (; position != endit + 1; ++position) {
					_alloc.construct(&*position, *(position + 1));
			}
			--_size;
			return res;
		}

		iterator erase (iterator first, iterator last) {
			difference_type diff = last - first;
			iterator endit = this->end();
			for (iterator it = first; it != endit; ++it) {
				_alloc.destroy(&*it);
				if (diff < endit - it)
					_alloc.construct(&*it, *(it + diff));
			}
			_size -= diff;
			return last;
		}

		void swap (vector& x);

		void clear() {
			if (!_size)
				return;
			for (size_type i = _size - 1; i > 0; --i) {
				_alloc.destroy(_array + i);
			}
			_size = 0;
		}
	};
}

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
	std::vector<int>::iterator itv = v1.begin();
	std::vector<int>::iterator itv2 = v1.end();
	std::vector<int>::iterator itv11 = v11.begin();
	std::vector<int>::iterator itv112 = v11.end();
	// std::vector<int>::iterator itv3 = v1.erase(itv + 5);
	// std::cout << *itv << std::endl;
	// v1.insert(itv + 5, 10, 99);
	// std::cout << *itv3 << std::endl;
	v1.insert(itv + 5, itv11, itv112);
	for (size_t i = 0; i < v1.size(); i++)
	{
		std::cout << v1[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << v1.size() << std::endl;
	std::cout << "cap = " << v1.capacity() << std::endl;
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


	// v2.push_back(2);
	// v2.push_back(3);
	ft::vector<int>::iterator it = v2.begin();
	ft::vector<int>::iterator it2 = v2.end();
	ft::vector<int>::iterator it22 = v22.begin();
	ft::vector<int>::iterator it222 = v22.end();
	// ft::vector<int>::iterator it3 = v2.erase(it + 5);
	// std::cout << v2.size() << std::endl;
	// ft::vector<int>::iterator it3 = v2.insert(it + 5, 99);
	// std::cout << *it3 << std::endl;
	// v22.assign(it, it2);
	// v2.insert(it + 5, 10, 99);
	v2.insert(it + 5, it22, it222);
	for (size_t i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "size = " << v2.size() << std::endl;
	std::cout << "cap = " << v2.capacity() << std::endl;
	ft::vector<int> v4(v2.begin(), v2.end());
	for (size_t i = 0; i < v4.size(); i++)
	{
		std::cout << v4[i] << " ";
	}
	std::cout << std::endl;

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
