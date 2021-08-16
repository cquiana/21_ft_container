#pragma once

#include <iterator>
#include "utils.hpp"

namespace ft
{
	// template <class T, class Pointer = T*, class Reference = T&, class Category = std::random_access_iterator_tag, class allocator_type = std::allocator<T>  >
	// class vector_iterator
	// {
	// public:
	// 	typedef typename ft::iterator_traits<T>::value_type			value_type;
	// 	typedef typename ft::iterator_traits<T>::difference_type	difference_type;
	// 	typedef typename ft::iterator_traits<T>::pointer			pointer;
	// 	typedef typename ft::iterator_traits<T>::reference			reference;
	// 	typedef typename ft::iterator_traits<T>::const_pointer		const_pointer;
	// 	typedef typename ft::iterator_traits<T>::const_reference	const_reference;
	// 	typedef typename ft::iterator_traits<T>::size_type			size_type;
	// 	typedef Category	iterator_category;

	template <class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&, class Category = std::random_access_iterator_tag>
	class vector_iterator
	{
	public:
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
		typedef Category		iterator_category;

	private:
		pointer _ptr;

	public:
		vector_iterator() : _ptr(0) {};
		vector_iterator(pointer ptr) : _ptr(ptr) {}
		vector_iterator(vector_iterator const &other) : _ptr(other._ptr) {}
		vector_iterator	&operator=(const vector_iterator& other) {
			_ptr= other._ptr;
			return (*this);
		}
		~vector_iterator() {}

		pointer base() {
			return (this->_ptr);
		}

		// const_pointer base() const {
		// 	return (this->_ptr);
		// }

		vector_iterator &operator++() {
			++_ptr;
			return (*this);
		}

		vector_iterator	operator++(int) {
			vector_iterator copy(*this);
			++_ptr;
			return (copy);
		}

		vector_iterator &operator--() {
			--_ptr;
			return (*this);
		}

		vector_iterator operator--(int) {
			vector_iterator copy(*this);
			--_ptr;
			return (copy);
		}

		difference_type	operator-(vector_iterator other) const {
			return (_ptr - other._ptr);
		}

		difference_type	operator+(vector_iterator other) const {
			return (_ptr + other._ptr);
		}

		vector_iterator	operator-(difference_type n) const {
			vector_iterator copy(*this);
			copy._ptr -= n;
			return (copy);
		}

		vector_iterator	operator+(difference_type n) const {
			vector_iterator copy(*this);
			copy._ptr += n;
			return (copy);
		}

		vector_iterator	&operator+=(difference_type n) {
			_ptr += n;
			return (*this);
		}

		vector_iterator	&operator-=(difference_type n) {
			_ptr -= n;
			return (*this);
		}

		reference	operator*() { return (*_ptr); }
		pointer		operator->() { return (_ptr); }
		// const_reference	operator*() const { return (*_ptr); }
		// const_pointer	operator->() const { return (_ptr); }
		reference	operator[](difference_type n) const { return (*(_ptr + n)); }

		bool operator==(const vector_iterator & other) const { return (_ptr == other._ptr); }
		bool operator!=(const vector_iterator & other) const { return (_ptr != other._ptr); }
		bool operator>=(const vector_iterator & other) const { return (_ptr >= other._ptr); }
		bool operator<=(const vector_iterator & other) const { return (_ptr <= other._ptr); }
		bool operator>(const vector_iterator & other) const { return (_ptr > other._ptr); }
		bool operator<(const vector_iterator & other) const { return (_ptr < other._ptr); }
	};

	template <typename T>
	bool operator==(const ft::vector_iterator<T> lhs, const ft::vector_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename T1, typename T2>
	bool operator==(const ft::vector_iterator<T1> lhs, const ft::vector_iterator<T2> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	bool operator!=(const ft::vector_iterator<T> lhs, const ft::vector_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename T1, typename T2>
	bool operator!=(const ft::vector_iterator<T1> lhs, const ft::vector_iterator<T2> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	bool operator<(const ft::vector_iterator<T> lhs, const ft::vector_iterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template<typename T1, typename T2>
	bool operator<(const ft::vector_iterator<T1> lhs, const ft::vector_iterator<T2> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	bool operator>(const ft::vector_iterator<T> lhs, const ft::vector_iterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename T1, typename T2>
	bool operator>(const ft::vector_iterator<T1> lhs, const ft::vector_iterator<T2> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	bool operator<=(const ft::vector_iterator<T> lhs, const ft::vector_iterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T1, typename T2>
	bool operator<=(const ft::vector_iterator<T1> lhs, const ft::vector_iterator<T2> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	bool operator>=(const ft::vector_iterator<T> lhs, const ft::vector_iterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T1, typename T2>
	bool operator>=(const ft::vector_iterator<T1> lhs, const ft::vector_iterator<T2> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename T>
	typename ft::vector_iterator<T>::difference_type operator-(const ft::vector_iterator<T> lhs, const ft::vector_iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<typename T1, typename T2>
	typename ft::vector_iterator<T1>::difference_type operator-(const ft::vector_iterator<T1> lhs, const ft::vector_iterator<T2> rhs)
	{
		return (lhs.base() - rhs.base());
	}

}
