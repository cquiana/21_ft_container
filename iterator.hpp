#pragma once

#include <iostream>

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;

		reference operator*() {
			return pointer;
		}

		iterator& operator++() {
			++pointer;
			return *this;
		}

		iterator& operator--() {
			--pointer;
			return *this;
		}

		pointer operator->() {
			return pointer;
		}
	};
}

