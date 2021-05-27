#pragma once

#include <iostream>
#include <string>

#include "utils.hpp"

namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >
	class list
	{
	private:


	public:
		typedef T 										value_type;
		typedef Alloc									alloc_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;

// iterator	a bidirectional iterator to value_type	convertible to const_iterator
// const_iterator	a bidirectional iterator to const value_type
// reverse_iterator	reverse_iterator<iterator>
// const_reverse_iterator	reverse_iterator<const_iterator>

		typedef typename alloc_type::reference			reference;
		typedef typename alloc_type::const_reference	const_reference;
		typedef typename alloc_type::pointer 			pointer;
		typedef typename alloc_type::const_pointer		const_pointer;

		typedef	Node<value_type>*						node_pointer;
		typedef Node<value_type>						node_data;

	private:
		alloc_type		_alloc;
		size_type		_size;
		node_pointer	_head;
		node_pointer	_end;
		node_pointer	_fakenode;

public:

	void	create_fake_node() {

	}

	explicit list (const allocator_type& alloc = allocator_type());

	explicit list (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type());

	template <class InputIterator>
	list (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type());

	list (const list& x);








	};

}
