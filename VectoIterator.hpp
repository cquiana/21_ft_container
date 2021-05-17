#pragma once

#include <iostream>
template <typename T>
struct random_access_iterator {
public:
	typedef T						value_type;
	typedef T&						reference;
	typedef T*						pointer;
	typedef random_access_iterator	iterator_type;
	typedef std::ptrdiff_t			difference_type;
private:
	pointer _ptr;
public:

	random_access_iterator() : _ptr(NULL) {}

	random_access_iterator(pointer ptr) : _ptr(ptr) {}

	random_access_iterator(const iterator_type &randomAccessIterator) {
		*this = randomAccessIterator; }

	iterator_type &operator=(const iterator_type &iter) {
		_ptr = iter._ptr;
		return (*this);
	}

	virtual ~random_access_iterator() {}

	reference operator[](difference_type n) {
		return (*(_ptr + n));
	}

	reference operator*() {
		return (*_ptr);
	}

	iterator_type& operator++() {
		++_ptr;
		return *this;
	}

	iterator_type &operator++(int) {
		iterator_type &tmp = *this;
		_ptr++;
		return tmp;
	}

	iterator_type &operator--() {
		--_ptr;
		return *this;
	}

	const iterator_type &operator--(int) {
		iterator_type& tmp = *this;
		_ptr--;
		return tmp;
	}

	iterator_type &operator+=(difference_type n) {
		difference_type tmp = n;
		if (tmp >= 0)
			while (tmp--)
				++_ptr;
		else
			while (tmp++)
				--_ptr;
		return *this;
	}

	iterator_type& operator-=(difference_type n) {
		_ptr -= n;
		return *this;
	}

	pointer operator->() {
		return _ptr;
	}

	iterator_type operator+(difference_type n) {
		iterator_type tmp = *this;
		return (tmp += n);
	}

	iterator_type operator-(difference_type n) {
		iterator_type tmp = *this;
		return (tmp -= n);
	}

	difference_type operator-(iterator_type iter) {
		difference_type res = 0;
		if (iter._ptr > _ptr) {
			while ((iter._ptr + res) != _ptr)
				res--;
		}
		else {
			while ((iter._ptr + res) != _ptr)
				res++;
		}
		return (res);
	}

	difference_type distance(iterator_type first, iterator_type second) {
		difference_type res = first - second;
		return (res);
	}

	void advance(iterator_type &iter, difference_type n) {
		iter += n;
	}

	bool operator>(const iterator_type& iter) {
		return (_ptr > iter._ptr);
	}

	bool operator<(const iterator_type& iter) {
		return (iter._ptr - _ptr > 0);
	}

	bool operator>=(const iterator_type& iter) {
		return !(_ptr < iter._ptr);
	}
	bool operator<=(const iterator_type& iter) {
		return !(_ptr > iter._ptr);
	}

	bool operator!=(const iterator_type& iter) {
		return (_ptr != iter._ptr);
	}

	bool operator==(const iterator_type& iter) {
		return (_ptr == iter._ptr);
	}
};

