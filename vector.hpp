#include <memory>
#include <stdexcept>
#include <limits>

#include "VectoIterator.hpp"
#include "utils.hpp"

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
		typedef const_random_access_iterator<T>				const_iterator;
		typedef reverse_random_access_iterator<T>			reverse_iterator;
		typedef const_reverse_random_access_iterator<T>		const_reverse_iterator;

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
		vector (typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type first, InputIterator last,
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

		iterator begin() { return (iterator(_array)); }

		const_iterator begin() const { return (iterator(_array)); }

		iterator end() { return (iterator(_array + _size)); }

		const_iterator end() const { return (iterator(_array + _size)); }

		reverse_iterator rbegin() { return reverse_iterator(_array + (_size - 1)); }

		const_reverse_iterator rbegin() const { return reverse_iterator(_array + (_size - 1)); }

		reverse_iterator rend() { return reverse_iterator(_array - 1); }

		const_reverse_iterator rend() const { return reverse_iterator(_array - 1); }


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
		void assign(typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type first,
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
			typename ft::enable_if<!ft::is_integer<InputIterator>::value,
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

		void swap (vector& x) {
			ft::swap(_alloc, x._alloc);
			ft::swap(_array, x._array);
			ft::swap(_size, x._size);
			ft::swap(_capacity, x._capacity);

		}

		void clear() {
			if (!_size)
				return;
			for (size_type i = _size - 1; i > 0; --i) {
				_alloc.destroy(_array + i);
			}
			_size = 0;
		}

	};

	template<class Alloc>
	class vector<bool, Alloc> {
	public:
		void hello() const {
//			std::cout << "this is vector<bool>" << std::endl;
		}
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); ++i){
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void	swap (vector<T, Alloc>& x, vector<T, Alloc>& y) {
		x.swap(y);
	};
}
