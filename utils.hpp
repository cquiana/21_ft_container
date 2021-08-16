#pragma once
#include <memory>
#include <stdexcept>
#include <limits>
#include <iterator>

/*
**==========================
**         Colors
**==========================
*/

# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

namespace ft
{

	template<typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<typename T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t 						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
	public:
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};


	template <class Iter>
	class	reverse_iterator
	{
	public:
		typedef	Iter												iterator_type;
		typedef	typename iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;

	private:
		iterator_type	_it;

	public:
		reverse_iterator(): _it(iterator_type()) {}
		explicit reverse_iterator(const iterator_type& it) : _it(it) {}
		template <typename It>
		reverse_iterator(const reverse_iterator<It>& src): _it(src.base()) {}

		iterator_type		base()									const	{ return (_it); }
		reverse_iterator&	operator++()									{ (_it)--; return (*this); }
		reverse_iterator	operator++(int)										{ reverse_iterator result(*this); this->operator++(); return (result); }
		reverse_iterator&	operator--()									{ (_it)++; return (*this); }
		reverse_iterator	operator--(int)										{ reverse_iterator result(*this); this->operator--(); return (result); }
		reverse_iterator	operator+(difference_type n)				const	{ return (reverse_iterator(_it - n)); }
		reverse_iterator	operator-(difference_type n)				const	{ return (reverse_iterator(_it + n)); }
		reverse_iterator&	operator+=(difference_type n)						{ (_it) -= n; return (*this);}
		reverse_iterator&	operator-=(difference_type n)						{ (_it) += n; return (*this);}

		bool				operator==(reverse_iterator const & rhs)	const	{ return (_it == rhs._it); }
		bool				operator!=(reverse_iterator const & rhs)	const	{ return (_it != rhs._it); }

		reference operator*() const
		{
			Iter tmp = _it;
    		return *(--tmp);
		}

		pointer	operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n)	const
		{
			return base()[-n-1];
		}


	};


	template <typename T, T _value>
	struct integral_constant
	{
		static const T value = _value;
	};

	struct true_type : public integral_constant<bool, true> {};
	struct false_type : public integral_constant<bool, false> {};

	template <class> struct is_integral : public false_type {};
	template<> struct is_integral<bool> : public true_type {};
	template<> struct is_integral<char> : public true_type {};
	template<> struct is_integral<wchar_t> : public true_type {};
	template<> struct is_integral<signed char> : public true_type {};
	template<> struct is_integral<unsigned char> : public true_type {};

	template<> struct is_integral<int> : public true_type {};
	template<> struct is_integral<unsigned int> : public true_type {};

	template<> struct is_integral<short int> : public true_type {};
	template<> struct is_integral<unsigned short int> : public true_type {};

	template<> struct is_integral<long int> : public true_type {};
	template<> struct is_integral<unsigned long int> : public true_type {};

	template<> struct is_integral<long long int> : public true_type {};
	template<> struct is_integral<unsigned long long int> : public true_type {};

	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if <true, T>
	{
		typedef T type;
	};


	template <class T>
	void swap(T &x, T &y)
	{
		T tmp = x;
		x = y;
		y = tmp;
	}

	template <typename Iterator, typename IteratorCaterory>
	void advanceHelper(Iterator& it, int n, IteratorCaterory)
	{
		if (n >= 0)
			for (int i = 0; i < n; ++i, ++it);
		else
			for (int i = 0; i > n; --i, --it);
	}

	template <typename Iterator>
	void advanceHelper(Iterator& it, int n, std::random_access_iterator_tag)
	{
		it += n;
	}

	template <typename Iterator>
	void advance(Iterator& it, int n)
	{
		advanceHelper(it, n, typename ft::iterator_traits<Iterator>::iterator_category());
	}


	template <typename Iterator, typename IteratorCaterory>
	typename ft::iterator_traits<Iterator>::difference_type distanceHelper(Iterator first, Iterator last, IteratorCaterory)
	{
		ptrdiff_t dist = 0;
		for (; first != last; ++first, ++dist);
		return dist;
	}

	template <typename Iterator>
	typename ft::iterator_traits<Iterator>::difference_type distanceHelper(Iterator first, Iterator last, std::random_access_iterator_tag)
	{
		return last - first;
	}


	template<typename Iterator>
	typename ft::iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last)
	{
		return distanceHelper(first, last, typename ft::iterator_traits<Iterator>::iterator_category());
	}


		// Rule that creates a typedefs
	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};


	template <class T>
	struct less : binary_function<T, T, bool>
	{
		// typedef T	first_argument_type;
		// typedef T	second_argument_type;
		// typedef bool result_type;

		bool operator()(const T& x, const T& y) const { return x < y; }
	};

	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;
		first_type	first;
		second_type	second;

		pair() : first(T1()), second(T2()) {}
		template<class U, class V> pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}
		pair& operator=(const pair& pr) { first = pr.first; second = pr.second; return (*this); }
		~pair() {}
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair (T1 x, T2 y) { return (pair<T1, T2>(x, y)); }

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
	template<class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class Ite1, class Ite2>
	bool	equal(Ite1 first1, Ite1 last1, Ite2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		return true;
	}

enum Color {
	RED,
	BLACK,
};

template<class T>
struct RBTreeNode {
	typedef T value_type;

	Color color;
	RBTreeNode *parent;
	RBTreeNode *left;
	RBTreeNode *right;
	value_type _value;

	RBTreeNode(const value_type &val = value_type()) : _value(val) {}
	};

template<class T, class Compare>
struct map_iterator {

	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef map_iterator<T, Compare>		iterator;
	typedef RBTreeNode<T>					RBTNode;

	RBTNode *_node;
	RBTNode *_end;
	Compare _compare;

	map_iterator(RBTNode *node, RBTNode *end) : _node(node), _end(end) {}

	map_iterator(iterator const &x) : _node(x._node), _end(x._end) {}

	~map_iterator() {}

	iterator &operator=(iterator const &x) {
		if (this != &x) {
		_node = x._node;
		_node = x._end;
		}
		return *this;
	}

	bool operator==(iterator const &rhs) const { return _node == rhs._node; }

	bool operator!=(iterator const &rhs) const { return !(*this == rhs); }

	reference operator*() const { return _node->_value; }

	pointer operator->() const { return &operator*(); }

	iterator &operator++() {

		if (_node->right != _end) {
		_node = _node->right;
		while (_node->left != _end) {
			_node = _node->left;
		}
		} else {
		RBTNode *tmp = _node->parent;
		while (_node == tmp->right) {
			_node = tmp;
			tmp = tmp->parent;
		}
		if (_node->right != tmp) {
			_node = tmp;
		}
		}
		return *this;
	}

	iterator operator++(int) {
		iterator old = *this;
		operator++();
		return old;
	}

	iterator &operator--() {
		if (_node == _end) {
		while (_node->right != _end) {
			_node = _node->right;
		}
		} else if (_node->left != _end) {
		_node = _node->left;
		while (_node->right != _end) {
			_node = _node->right;
		}
		} else {
		RBTNode *tmp = _node->parent;
		while (_node == tmp->left) {
			_node = tmp;
			tmp = tmp->parent;
		}
		if (_node->left != tmp) {
			_node = tmp;
		}
		}
		return *this;
	}

	iterator operator--(int) {
		iterator old = *this;
		operator--();
		return old;
	}


	};


	template<class T, class Compare>
	struct const_map_iterator {
		typedef const T							value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef const_map_iterator<T, Compare>	iterator;
		typedef RBTreeNode<T>						RBTNode;

		RBTNode *_node;
		RBTNode *_end;
		Compare _compare;

		const_map_iterator(RBTNode *node, RBTNode *last_node) : _node(node), _end(last_node) {}

		const_map_iterator(iterator const &x) : _node(x._node), _end(x._end) {}

		~const_map_iterator() {}

		iterator &operator=(iterator const &x) {
			if (this != &x) {
			_node = x._node;
			_node = x._end;
			}
			return *this;
		}

		bool operator==(iterator const &rhs) const { return _node == rhs._node; }

		bool operator!=(iterator const &rhs) const { return !(*this == rhs); }

		reference operator*() const { return _node->_value; }

		pointer operator->() const { return &operator*(); }

		iterator &operator++() {

			if (_node->right != _end) {
				_node = _node->right;
				while (_node->left != _end) {
					_node = _node->left;
				}
			} else {
				RBTNode *tmp = _node->parent;
				while (_node == tmp->right) {
					_node = tmp;
					tmp = tmp->parent;
				}
				if (_node->right != tmp) {
					_node = tmp;
				}
			}
			return *this;
		}

		iterator operator++(int) {
			iterator old = *this;
			operator++();
			return old;
		}

		iterator &operator--() {
			if (_node == _end) {
				while (_node->right != _end) {
					_node = _node->right;
				}
			} else if (_node->left != _end) {
				_node = _node->left;
				while (_node->right != _end) {
					_node = _node->right;
				}
			} else {
				RBTNode *tmp = _node->parent;
				while (_node == tmp->left) {
					_node = tmp;
					tmp = tmp->parent;
				}
				if (_node->left != tmp) {
					_node = tmp;
				}
			}
			return *this;
		}

		iterator operator--(int) {
			iterator old = *this;
			operator--();
			return old;
		}
	};
}
