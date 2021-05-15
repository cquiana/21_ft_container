#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
	// public:
	// 	typedef	T											value_type;
	// 	typedef	Alloc										allocator_type;
	// 	typedef typename allocator_type::reference			reference;
	// 	typedef typename allocator_type::const_reference	const_reference;
	// 	typedef typename allocator_type::pointer			pointer;
	// 	typedef typename allocator_type::const_pointer		const_pointer;

	private:
		T* _array;
		size_t _size;
		size_t _capacity;
		Alloc _alloc;

	public:
		vector(size_t n, const T &value = T(), const Alloc &alloc = Alloc());
		~vector();


		T& operator[](size_t index)
		{
			return _array[index];
		}

		T& at(size_t index)
		{
			if (index > _size) throw std::out_of_range("...");
			return _array[index];
		}

		const T& operator[](size_t index) const
		{
			return _array[index];
		}

		const T& at(size_t index) const
		{
			if (index > _size) throw std::out_of_range("...");
			return _array[index];
		}

		size_t size() const
		{
			return _size;
		}

		size_t capacity() const
		{
			return _capacity;
		}

		void resize(size_t n, const T& value = T())
		{
			if (n < _capacity)
				reserve (_capacity);
			for
		}

		void reserve(size_t n)
		{
			if (n <= _capacity)
				return;
			// T* tmp = reinterpret_cast<T*>(new int8_t[n * sizeof(T)]);

			T *tmp = _alloc.allocate(n);
			try {
				std::uninitialized_copy(_array, _array + _size, tmp);
			} catch (...) {
				// delete[] reinterpret_cast<int8_t*>(tmp);
					_alloc.deallocate(tmp, n);
				throw;
			}


			// for (size_t i = 0; i < _size; ++i)
			// {
			// 	new(tmp + j) T(_array[i]);
			// }
			// for (size_t i = 0; i < _size; ++i)
			// {
			// 	(_array + i)->~T();
			// }
			// delete[] reinterpret_cast<int8_t*>(_array);
			// _array = tmp;
		}

		void push_back(const T& value)
		{
			if (_size == _capacity)
				reserve (_capacity * 2);
			new (_array + _size) T(value);
			++_size;
		}

		void pop_back()
		{
			(_array + _size - 1)->~T();
			--_size;
		}
	};
}

int main()
{
	std::vector<int> v1;
	for (int i = 0; i < 25; ++i)
	{
		v1.push_back(i);
		std::cout << v1.size() << ' ' << v1.capacity() << std::endl;
	}

}
