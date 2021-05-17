#pragma once

#include <iostream>
template <typename T>
struct random_access_iterator {
public:
	typedef T		value_type;
	typedef T&		reference;
	typedef T*		pointer;
private:
	pointer _ptr;
public:

	random_access_iterator() : _ptr(NULL) {}

	random_access_iterator(pointer ptr) : _ptr(ptr) {}

	random_access_iterator(const random_access_iterator &randomAccessIterator) {
		*this = randomAccessIterator; }

	random_access_iterator &operator=(const random_access_iterator &iter) {
		_ptr = iter._ptr;
		return (*this);
	}

	virtual ~random_access_iterator() {}


	reference operator*() {
		return (*_ptr);
	}

		random_access_iterator& operator++() {
			++_ptr;
			return *this;
		}

		random_access_iterator& operator++(int) {
			// random_access_iterator tmp = random_access_iterator(*this);
			// ++_ptr;
			return _ptr++;
		}

		random_access_iterator& operator--() {
			--_ptr;
			return *this;
		}

		pointer operator->() {
			return _ptr;
		}

		bool operator!=(const random_access_iterator& iter) {
			return (_ptr != iter._ptr);
		}

		bool operator==(const random_access_iterator& iter) {
			return (_ptr == iter._ptr);
		}
};

