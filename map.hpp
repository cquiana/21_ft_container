#pragma once
#include "utils.hpp"

namespace ft
{
template<class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
public:
	typedef Key												key_type;
	typedef T												mapped_type;
	typedef ft::pair<const Key, T>							value_type;
	typedef std::size_t										size_type;
	typedef std::ptrdiff_t									difference_type;
	typedef Compare											key_compare;
	typedef Alloc											allocator_type;
	typedef ft::map_iterator<value_type, Compare>			iterator;
	typedef ft::const_map_iterator<value_type, Compare>		const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;

	class value_compare : std::binary_function<value_type, value_type, bool> {
		friend class map;

	protected:
		Compare _comp;

		value_compare(Compare comp) : _comp(comp) {}

	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;

		bool operator()(value_type x, value_type y) const { return _comp(x.first, y.first); }
	};
protected:
	typedef RBTreeNode<value_type> _node;
	typedef typename allocator_type::template rebind<_node>::other _allocator_type;

private:
	_node *_end;
	size_type _size;
	key_compare _comp;
	std::allocator<_node> _alloc;

public:
	explicit map(const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type()) : _end(0), _size(0), _comp(comp), _alloc() {
		(void) alloc;
		createEnd();
	}


	template<class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare &comp = key_compare(),
		const allocator_type &alloc = allocator_type()) : _end(0), _size(0), _comp(comp), _alloc() {
		(void) alloc;
		createEnd();
		insert(first, last);
	}

	map(const map &x) : _end(0), _size(0), _comp(x._comp), _alloc(x._alloc) {
		createEnd();
		insert(x.begin(), x.end());
	}

	map &operator=(const map &x) {
		if (this != &x) {
		map tmp(x);
		swap(tmp);
		}
		return *this;
	}

	~map() {
		clear();
		deleteNode(_end);
	}


	iterator begin() { return iterator(_end->left, _end); }

	const_iterator begin() const { return const_iterator(_end->left, _end); }

	iterator end() {
		return iterator(_end, _end);
	}

	const_iterator end() const {
		return const_iterator(_end, _end);
	}

	reverse_iterator rbegin() { return reverse_iterator(end()); }

	const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

	reverse_iterator rend() { return reverse_iterator(begin()); }

	const_reverse_iterator rend() const { return reverse_iterator(begin()); }

	size_type size() const { return _size; }

	bool empty() const { return _size == 0; }

	size_type max_size() const { return _alloc.max_size(); }

	mapped_type& operator[] (const key_type& k) {
		return insert(ft::make_pair(k,mapped_type())).first->second;
	}

	ft::pair<iterator, bool> insert(const value_type &val) {

		_node *tmp = _end->right;

		while (tmp != _end) {
		if (val.first == tmp->_value.first) {
			return ft::make_pair(iterator(tmp, _end), false);
		} else if (!_comp(val.first, tmp->_value.first)) {
			if (tmp->right != _end) {
			tmp = tmp->right;
			} else {
			tmp->right = createNode(RED, tmp, _end, _end, val);
			return ft::make_pair(iterator(tmp->right, _end), true);
			}
		} else if (_comp(val.first, tmp->_value.first)) {
			if (tmp->left != _end) {
			tmp = tmp->left;
			} else {
			tmp->left = createNode(RED, tmp, _end, _end, val);
			return ft::make_pair(iterator(tmp->left, _end), true);
			}
		}
		}
		_end->right = createNode(BLACK, _end, _end, _end, val);
		return ft::make_pair(iterator(_end->right, _end), true);
	}

	iterator insert(iterator position, const value_type &val) {
		(void) position;
		return insert(val).first;
	}

	template<class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last) {
		insert(*first);
		++first;
		}
	}

	void swap(map &x) {
		_node *tmp_end = _end;
		size_type tmp_size = _size;
		_end = x._end;
		_size = x._size;
		x._end = tmp_end;
		x._size = tmp_size;
	}

	void erase(iterator position) {
		_node *node = position._node;
		++position;
		_node *x = position._node;
		if (node == _end)
			return;
		if (node->right == _end || node->left == _end) {

		_node *y = node->right != _end ? node->right : node->left;

		if (node->parent->right == node) {
			node->parent->right = y;
		} else {
			node->parent->left = y;
		}
		if (y != _end) {
			y->parent = node->parent;
		}
		} else if (x != _end) {
		if (x->parent->right == x) {
			x->parent->right = x->right;
		} else {
			x->parent->left = x->right;
		}
		if (x->right != _end) {
			x->right->parent = x->parent;
		}
		if (node->parent->right == node) {
			node->parent->right = x;
		} else {
			node->parent->left = x;
		}
		x->right = node->right;
		node->right->parent = x;
		x->left = node->left;
		node->left->parent = x;
		x->parent = node->parent;
		}
		if (_end->left == node) {
		_end->left = x;
		}
		if (node != _end)
		deleteNode(node);
		--_size;
	}

	size_type erase(const key_type &k) {
		iterator tmp = find(k);
		if (tmp == end())
			return 0;
		erase(tmp);
		return 1;
	}

	void erase(iterator first, iterator last) {
		if (first == end())
			return;
		while (first != last) {
			iterator tmp(first);
			++first;
			erase(tmp);
		}
	}

	void clear() {
		erase(begin(), end());
	}

	key_compare key_comp() const {
		return key_compare();
	}

	value_compare value_comp() const {
		return value_compare(_comp);
	}

	iterator find(const key_type &k) {
		return iterator((const_cast<const map*>(this)->find(k))._node, _end);
	}

	const_iterator find(const key_type &k) const {
		_node *tmp = _end->right;
		while (tmp != _end) {
			if (tmp->_value.first == k) {
				return (const_iterator(tmp, _end));
			} else if (_comp(k, tmp->_value.first)) {
				tmp = tmp->left;
			} else {
				tmp = tmp->right;
			}
		}
		return const_iterator(_end, _end);
	}

	size_type count(const key_type &k) const {
		if (find(k) != end()) {
			return 1;
		}
		return 0;
	}

	iterator lower_bound(const key_type &k) {
		return iterator((const_cast<const map*>(this)->lower_bound(k))._node, _end);
	}

	const_iterator lower_bound(const key_type &k) const {
		const_iterator itb = begin();
		const_iterator ite = end();
		while (itb != ite) {
			if (!_comp((*itb).first, k)) {
				return itb;
			}
			++itb;
		}
		return ite;
	}

	iterator upper_bound(const key_type &k) {
		return iterator((const_cast<const map*>(this)->upper_bound(k))._node, _end);
	}

	const_iterator upper_bound(const key_type &k) const {
		const_iterator itb = begin();
		const_iterator ite = end();
		while (itb != ite) {
			if (!_comp((*itb).first, k)) {
				if (_comp(k, (*itb).first)) {
					return itb;
				} else {
					return ++itb;
				}
			}
		++itb;
		}
		return ite;
	}

	pair<iterator, iterator> equal_range(const key_type &k) {
		iterator lower = lower_bound(k);
		iterator upper = upper_bound(k);
		return ft::make_pair(lower, upper);
	}

	pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
		const_iterator lower = lower_bound(k);
		const_iterator upper = upper_bound(k);
		return ft::make_pair(lower, upper);
	}



	void deleteNode(_node *node) {
		_alloc.destroy(node);
		_alloc.deallocate(node, sizeof(node));
	}

	_node *createNode(Color clr = RED, _node *p = 0, _node *l = 0, _node *r = 0,
						value_type val = value_type()) {
		_node *node = _alloc.allocate(1);
		_alloc.construct(node, val);
		node->color = clr;
		node->parent = p;
		node->left = l;
		node->right = r;
		updateMinimum(node);
		++_size;
		return node;
	}

	void updateMinimum(_node *node) {
		if (_end->left == _end) {
		_end->left = node;
		} else if (_comp(node->_value.first, _end->left->_value.first)) {
		_end->left = node;
		}
	}

	void createEnd() {
		_end = _alloc.allocate(1);
		_alloc.construct(_end, value_type());
		_end->color = BLACK;
		_end->parent = _end;
		_end->left = _end;
		_end->right = _end;
	}

	};
}
