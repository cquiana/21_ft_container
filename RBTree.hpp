#pragma once
#include "utils.hpp"

namespace ft
{


typedef enum
{
	BLACK,
	RED
} Color;



template <class T>
struct RBNode
{
	T		value;
	Color	color;
	RBNode*	parent;
	RBNode*	left;
	RBNode*	right;

	RBNode() : value(),  color(RED), parent(NULL), left(NULL), right(NULL) {}
	RBNode(const T& value, Color color = RED, RBNode* parent = NULL, RBNode* left = NULL, RBNode* right = NULL) :
		value(value), color(color), parent(parent), left(left), right(right) {}
	RBNode(const RBNode& other) :
		value(other.value), color(other.color), parent(other.parent), left(other.left), right(other.right) {}
	RBNode &operator=(const RBNode& other)
	{
		value = other.value;
		color = other.color;
		parent = other.parent;
		left = other.left;
		right = other.right;
		return (*this);
	}
	~RBNode() {}
};

template <class T>
	class RBTree_iterator
	{
	public:
		typedef RBNode<T> node;
		typedef T	value_type;
		typedef typename iterator_traits<T>::size_type size_type;
		typedef typename iterator_traits<T>::difference_type difference_type;
		typedef typename iterator_traits<T>::pointer pointer;
		typedef typename iterator_traits<T>::reference reference;
		typedef std::bidirectional_iterator_tag iterator_category;
	private:
		node* _nil;
		node* _min;
		node* _max;
		node* _ptr;
	public:
		RBTree_iterator(void){}
		RBTree_iterator(node *ptr, node *nil, node *min, node *max): _nil(nil),_min(min), _max(max), _ptr(ptr){}
		RBTree_iterator(const RBTree_iterator &other): _nil(other._nil), _min(other._min), _max(other._max), _ptr(other._ptr){}
		~RBTree_iterator(){}
		RBTree_iterator &operator=(const RBTree_iterator &other)
		{
			if (this != &other) {
				_ptr = other._ptr;
				_nil = other._nil;
				_min = other._min;
				_max = other._max;
			}
			return *this;
		}

		node *base() const {return _ptr;}
		node *maxptr() const {return _max;}
		node *minptr() const {return _min;}
		node *null() const {return _nil;}

		reference operator*(void) const {return this->ptr->value;}
		pointer operator->(void) const {return &this->ptr->value;}
		bool check_endings(node *e){return (e == _nil);}
		RBTree_iterator &operator++()
		{
			if (_ptr == NULL || check_endings(_ptr))
				_ptr = _min;
			else if (!check_endings(_ptr->right))
			{
				_ptr = _ptr->right;
				while (!check_endings(_ptr) && !check_endings(_ptr->left))
					_ptr = _ptr->left;
			}
			else
			{
				node *tmp = _ptr;
				_ptr = _ptr->parent;
				while (!check_endings(_ptr) && tmp == _ptr->right)
				{
					tmp = _ptr;
					_ptr = _ptr->parent;
				}
		}
		return (*this);}
		RBTree_iterator &operator--()
		{
			if (!_ptr || check_endings(_ptr))
				_ptr = _max;
			else if (!check_endings(_ptr->left))
			{
				_ptr = _ptr->left;
				while (!check_endings(_ptr) && !check_endings(_ptr->right))
					_ptr = _ptr->right;
			}
			else
			{
				node *tmp;
				tmp = _ptr;
				_ptr = _ptr->parent;
				while (!check_endings(_ptr) && tmp == _ptr->left)
				{
					tmp = _ptr;
					_ptr = _ptr->parent;
				}
			}
			return (*this);
		}
		RBTree_iterator operator++(int)
		{
			RBTree_iterator copy = *this;
			++(*this);
			return (copy);
		}
		RBTree_iterator operator--(int)
		{
			RBTree_iterator copy = *this;
			--(*this);
			return (copy);
		}

		bool operator==(const RBTree_iterator &rhs) const {return this->_ptr == rhs._ptr;}
		bool operator!=(const RBTree_iterator &rhs) const {return this->_ptr != rhs._ptr;}
	};

	template <class T>
	class RBTree_const_iterator {
	public:
		typedef RBNode<T> 										node;
		typedef const T											value_type;
		typedef typename iterator_traits<T>::size_type			size_type;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef const T*										pointer;
		typedef const T&										reference;
		typedef std::bidirectional_iterator_tag					iterator_category;
	private:
		node* _nil;
		node* _min;
		node* _max;
		node* _ptr;
	public:
		RBTree_const_iterator(void){}
		RBTree_const_iterator(node *ptr, node *nil, node *min, node *max): _nil(nil),_min(min), _max(max), _ptr(ptr){}
		RBTree_const_iterator(const RBTree_const_iterator &other): _nil(other._nil), _min(other.min),_ max(other.max), _ptr(other._ptr){}

		RBTree_const_iterator(const RBTree_iterator<T> &other):
			_nil(other.null()), _min(other.minptr()), _max(other.maxptr()), _ptr(other.base()) {}

		~RBTree_const_iterator(){}
		RBTree_const_iterator &operator=(const RBTree_const_iterator &other)
		{
			if (this != &other) {
				_ptr = other._ptr;
				_nil = other._nil;
				_min = other._min;
				_max = other._max;
			}
			return *this;
		}
		node *base() const {return _ptr;}
		reference operator*(void) const {return this->_ptr->value;}
		pointer operator->(void) const {return &this->_ptr->value;}
		bool check_endings(node *e){return (e == _nil);}
		RBTree_const_iterator &operator++()
		{
			if (_ptr == NULL || check_endings(_ptr))
				_ptr = _min;
			else if (!check_endings(_ptr->right))
			{
				_ptr = _ptr->right;
				while (!check_endings(_ptr) && !check_endings(_ptr->left))
					_ptr = ptr->left;
			}
			else
			{
				node *tmp;
				tmp = _ptr;
				_ptr = _ptr->parent;
				while (!check_endings(_ptr) && tmp == _ptr->right)
				{
					tmp = _ptr;
					_ptr = _ptr->parent;
				}
		}
		return (*this);}
		RBTree_const_iterator &operator--()
		{
			if (!_ptr || check_endings(_ptr))
				_ptr = _max;
			else if (!check_endings(_ptr->left))
			{
				_ptr = _ptr->left;
				while (!check_endings(_ptr) && !check_endings(_ptr->right))
					_ptr = _ptr->right;
			}
			else
			{
				node *tmp;
				tmp = _ptr;
				_ptr = _ptr->parent;
				while (!check_endings(_ptr) && tmp == _ptr->left)
				{
					tmp = _ptr;
					_ptr = _ptr->parent;
				}
			}
			return (*this);
		}
		RBTree_const_iterator operator++(int)
		{
			RBTree_const_iterator copy = *this;
			++(*this);
			return (copy);
		}
		RBTree_const_iterator operator--(int)
		{
			RBTree_const_iterator copy = *this;
			--(*this);
			return (copy);
		}

		bool operator==(const RBTree_const_iterator &rhs) const {return this->_ptr == rhs._ptr;}
		bool operator!=(const RBTree_const_iterator &rhs) const {return this->_ptr != rhs._ptr;}
	};


template <class T, class Compare, class Alloc = std::allocator<RBNode<T> > >
class RBTree
{
public:
		typedef T											value_type;
		typedef RBNode<T>*									node_unit_ptr;
		typedef RBNode<T>									node_unit;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef RBNode<T>* 	const							const_node_unit_ptr;
		typedef RBTree_iterator<T>							iterator;
		typedef RBTree_const_iterator<T>					const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
private:
		node_unit_ptr _root;
		node_unit_ptr _end;
		size_type _size;
		Compare _comp;
		allocator_type _alloc;
public:
	explicit RBTree(const Compare &comp = Compare(), const allocator_type &alloc = allocator_type()) : _size(0), _comp(comp), _alloc(alloc) {
		initNil();
	}

	template <class InputIterator>
	RBTree(InputIterator first, InputIterator last, const Compare &comp = Compare(), const allocator_type &alloc = allocator_type()) : _size(0), _comp(comp), _alloc(alloc)) {
		initNil();
		insert(first, last);
	}

	RBTree(const RBTree &other) : _size(0), _comp(other._comp){
		initNil();
		insert(other.begin(), other.end());
	}

	RBTree &operator=(const RBTree &other) {
		if (this != &other) {
			clearTree();
			insert(other.begin(), other.end());
		}
		return (*this);
	}

	~RBTree() {
		clearTree();
		_alloc.destroy(_end);
		_alloc.deallocate(_end);
	}

	iterator insert(const value_type &val) {
		return insertValue(_root, val);
	}

	iterator insert(iterator position, const value_type &val) {
		(void)position;
		return insertValue(_root, val);
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		for (InputIterator it = first; it != last; ++it)
			insert(*it);
	}

	void erase(iterator position) {
		return deleteNode(position.base());
	}

	void erase(iterator first, iterator last) {
		for (iterator it = first; it != last; it++)
			erase(it);
	}

	iterator insertValue(node_unit_ptr root, const value_type &val) {
		iterator it = insertFixup(root, val);
		checkColor(it.base());
		root = it.base();
		while (getParent(root) && getParent(root) != _end)
			root = getParent(root);
		_root = root;
		return it;

	}

	iterator insertFixup(node_unit_ptr root, const value_type &val) {
		if (root == NULL && root == _end)
			return iterator(createNode(root, val), _end, getMin(), getMax());
		else {
			if (_comp(val, root->value)) {
				if (root->left != _end)
					return insertFixup(root->left, val);
				else {
					root->left = createNode(root, val);
					return iterator(root->left, _end, getMin(), getMax());
				}
			}
			else if (_comp(root->value, val)) {
				if (root->right != _end)
					return insertFixup(root->right, val);
				else {
					root->right = createNode(root, val);
					return iterator(root->right, _end, getMin(), getMax());
				}
			}
			else {
				return iterator(root, _end, getMin(), getMax());
			}
		}
	}

	bool isRoot(node_unit_ptr x) {
		return (x->parent == NULL || x->parent == _end)
	}

	node_unit_ptr getFather(node_unit_ptr x) {
		if (x == NULL)
			return NULL;
		else
			return x->parent;
	}

	node_unit_ptr getGrandFather(node_unit_ptr x) {
		if (x == NULL || x->parent == NULL)
			return NULL;
		else
			return x->parent->parent;
	}

	node_unit_ptr getBrother(node_unit_ptr x) {
		node_unit_ptr tmp = getFather(x);
		if (!tmp)
			return NULL;
		if (tmp->right == x)
			return tmp->left;
		else
			return tmp->right;
	}

	node_unit_ptr getUncle(node_unit_ptr x) {
		return getBrother(getFather(x));
	}

	// bool redUncleCase(node_unit_ptr x) {
	// 	return ()
	// }

	void checkColor(node_unit_ptr x) {
		if (isRoot())
			x->color == BLACK;
		else if (x->parent->color == BLACK)
			return ;
		else if (getUncle(x) != NULL && getUncle(x)->color == RED) {
			getFather(x)->color = BLACK;
			getUncle(x)->color = BLACK;
			getGrandFather(x)->color = RED;
			checkColor(getGrandFather(x));
		}
		else
			insertAndRotate(x);
	}

	void insertAndRotate(node_unit_ptr x) {
		node_unit_ptr father = getFather(x);
		node_unit_ptr grandfather = getGrandFather(x);
		if (x == father->right && father == grandfather->left) {
			rotateLeft(father);
			x = x->left;
		}
		else if (x == father->left && father == grandfather->right) {
			rotateRight(father);
			x = x->rigth;
		}
		insertAndRotateCase2(x);
	}

	void insertAndRotateCase2(node_unit_ptr x) {
		node_unit_ptr father = getFather(x);
		node_unit_ptr grandfather = getGrandFather(x);
		if (x == father->left)
			rotateRight(grandfather);
		else
			rotateLeft(grandfather);
		father->color = BLACK;
		grandfather->color = RED;
	}

	void rotateLeft(node_unit_ptr x) {
		node_unit_ptr y = x->right;
		x->right = y->left;
		if (y->left != _end)
			y->left->parent = x;
		if (getFather(x) == NULL || getFather(x) == _end)
			_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rotateRight(node_unit_ptr x) {
		node_unit_ptr y = x->left;
		x->left = y->right;
		if (y->right != _end)
			y->right->parent = x;
		if (getFather(x) == NULL || getFather(x) == _end)
			_root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	node_unit_ptr createNode(node_unit_ptr parent, const value_type &val) {
		node_unit_ptr tmp = _alloc.allocate(1);
		_alloc.construct(tmp, node_unit(val, RED, parent, _end, _end));
		return tmp;
	}


	void deleteNode(node_unit_ptr z) {
		node_unit_ptr x = NULL;
		node_unit_ptr y = NULL;
		if (z == NULL|| z == _end)
			return;
		if (z->right == _end || z->left ==_end)
			y = z;
		else {
			y = z->right;
			while (y->left != _end)
				y = y->left;
		}
		if (y->left != _end)
			x = y->left;
		else
			x = y->right;
		x->parent = y->parent;


	}

	void initNil() {
		_end = _alloc.allocate(1);
		_alloc.construct(_end, node_unit());
		_root = _end;
	}

	void clearTree() {
		erase(begin(), end());
	}




};




}
