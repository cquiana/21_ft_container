#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <limits>

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

		/*
		typedef for iterators
		typedef RandomAccess< T >					iterator;
		typedef ConstRandomAccess< T >				const_iterator;
		typedef ReverseRandomAccess< T >				reverse_iterator;
		typedef ConstReverseRandomAccess< T >			const_reverse_iterator;
		*/

		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;

	private:
		value_type*		_array;
		size_type		_size;
		size_type 		_capacity;
		allocator_type	_alloc;

	public:
		explicit vector(const allocator_type& alloc = allocator_type()) : _array(nullptr), _size(0), _capacity(0) {
			_alloc = alloc;
		}

		// Constructs a container with n elements. Each element is a copy of val.
		explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
		{
			// _alloc = alloc;
			// _array = _alloc.allocate(n);
			// _size = n;
			// _capacity = n;
			// for (size_type i = 0; i < n; ++i) {
			// 	_alloc.construct(_array + i, value);
			// }
		}

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

		template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());
				//  Constructs a container with as many elements as the range [first,last), with each element
				// constructed from its corresponding element in that range, in the same order.
		vector (const vector& x) {
			*this = x;
		}

		virtual ~vector() {
			if (_capacity > 0)
				_alloc.deallocate(_array, _capacity);
			// deallocate capacity
		}
		// This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.


		value_type& operator[](size_type index) {
			return _array[index];
		}

		value_type& at(size_type index) {
			if (index > _size) throw std::out_of_range("Out of range");
			return _array[index];
		}

		const value_type& operator[](size_type index) const {
			return _array[index];
		}

		const value_type& at(size_type index) const
		{
			if (index > _size) throw std::out_of_range("Out of range");
			return _array[index];
		}
		/*  ==== SIZE =====  */
		size_type size() const { return _size;}

		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / (sizeof(value_type)));
		}

		size_type capacity() const { return _capacity; }

		bool empty() const { return !_size; }

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

		void pop_back()
		{
			(_array + _size - 1)->~value_type();
			--_size;
		}
	};
}

int main()
{
	// std::vector<int> v1(10, 9);
	// std::cout << v1.capacity() << std::endl;
	// std::vector<int> v4 = v1;
	// v1[1] = 0;
	// std::cout << v4.capacity() << std::endl;
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	std::cout << v4[i] <<std::endl;
	// }
	// std::cout << "================" << std::endl;
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	std::cout << v1[i] <<std::endl;
	// }

	ft::vector<int> v2;
	// ft::vector<int> v3(1, 0);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	std::cout << v2[0] << std::endl;
	v2.reserve(100);

	// ft::vector<int> v5 = v2;
	// std::cout << v5[2] << std::endl;

	// v2.pop_back();

	// std::cout << "1111" << std::endl;
	// std::cout << v2.empty() << std::endl;
	// std::cout << v5.size() << std::endl;
	// std::cout << v5.capacity() << std::endl;
	std::cout << v2.size() << std::endl;
	v2.resize(10, 7);
	std::cout << v2.size() << std::endl;
	for (size_t i = 0; i < v2.size(); ++i)
	{
		std::cout << v2[i] << " ";
	}


	// std::cout << v2.capacity() << std::endl;
}
