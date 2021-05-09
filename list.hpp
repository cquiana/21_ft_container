#pragma once

#include <iostream>
#include <string>

namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >
	class list
	{
		typedef T value_type;
		typedef Alloc alloc_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

// iterator	a bidirectional iterator to value_type	convertible to const_iterator
// const_iterator	a bidirectional iterator to const value_type
// reverse_iterator	reverse_iterator<iterator>
// const_reverse_iterator	reverse_iterator<const_iterator>

		typedef typename alloc_type::reference reference;
		typedef typename alloc_type::const_reference const_reference;
		typedef typename alloc_type::pointer pointer;
		typedef typename alloc_type::const_pointer const_pointer;



	};

}
