#pragma once
#include "vector.hpp"


namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef Container							container_type;
		typedef typename container_type::value_type	value_type;
		typedef typename container_type::size_type	size_type;

		explicit stack (const container_type& cont = container_type()) : _cont(cont) {}
		~stack() {}

		bool empty() const { return (_cont.empty()); }
		size_type size() const { return (_cont.size()); }
		void push (const value_type& val) { return (_cont.push_back(val)) ; }
		void pop() { (_cont.pop_back()); }
		value_type& top() { return (_cont.back()); }
		const value_type& top() const { return (_cont.back()); }

		friend bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return lhs._cont == rhs._cont; }

		friend bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return lhs._cont != rhs._cont; }

		friend bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return lhs._cont < rhs._cont; }

		friend bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return lhs._cont <= rhs._cont; }

		friend bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return lhs._cont > rhs._cont; }

  		friend bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) { return lhs._cont >= rhs._cont; }

	protected:
		container_type _cont;
	};
}
