#ifndef TREE_RB_TREE_HPP_
#define TREE_RB_TREE_HPP_

#include <memory>

#include "rb_node.hpp"
#include "rb_iterator.hpp"
#include "iterator/reverse_iterator.hpp"

namespace ft {

template <class T, class Compare,
	class Alloc = std::allocator<rb_node<T> > >
class rb_tree {
 public:
	typedef T		value_type;
	typedef Compare	compare_type;
	typedef Alloc 	allocator_type;

	typedef rb_node<T>&			reference;
	typedef const rb_node<T>&	const_reference;
	typedef rb_node<T>*			pointer;
	typedef const rb_node<T>*	const_pointer;

	typedef typename ft::rb_tree_iterator<pointer> iterator;
	typedef typename ft::rb_tree_iterator<const pointer> const_iterator;
	typedef typename ft::reverse_iterator<iterator> reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef std::ptrdiff_t	difference_type;
	typedef std::size_t		size_type;

 private:
	allocator_type	_alloc;
	compare_type	_compare;
	pointer			_root;
	size_type		_size;

 public:
	explicit rb_tree(allocator alloc = allocator())
		:	_alloc(alloc),
			_root(NULL),
			_size(0) {}

	rb_tree(const rb_tree& other)
		:	_alloc(other._alloc),
			_root(NULL)
			_size(other._size) {
		__copy_tree(other._root);
	}

	rb_tree &operator=(const rb_tree &rhs) {
		if (this != &rhs) {
			_alloc = rhs._alloc;
			_root = NULL;
			_size = rhs._size;
			__destroy_tree(_root);
			__copy_tree(rhs._root);
		}
		return *this;
	}

	~rb_tree() { clear(); }

	iterator begin() {
		return iterator(_root, rb_node::min_leaf(_root));
	}
	const_iterator begin() const {
		return iterator(_root, rb_node::min_leaf(_root));
	}
	iterator end() {
		return iterator(_root, NULL);
	}
	const_iterator end() const {
		return iterator(_root, NULL);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(_root, NULL);
	}
	const_reverse_iterator rbegin() const {
		return reverse_iterator(_root, NULL);
	}
	reverse_iterator rend() {
		return reverse_iterator(_root, rb_node::min_leaf(_root));
	}
	const_reverse_iterator rend() const {
		return reverse_iterator(_root, rb_node::min_leaf(_root));
	}

	bool	empty() const {
		return _size == 0;
	}

	size_type	size() const {
		return _size;
	}

	size_type	max_size() const {
		return _alloc.max_size();
	}

	// ft::pair<iterator, bool> insert(value_type const &value) {}
	// iterator insert(iterator pos, const value_type &value) {}
	// size_type erase(value_type const &value) {}
	// void	erase(iterator pos) {}

	void	swap(rb_tree &rhs) {
		std::swap(_alloc, rhs._alloc);
		std::swap(_compare, rhs._compare);
		std::swap(_root, rhs._root);
		std::swap(_size, rhs._size);
	}

	void	clear() {
		__destroy_tree(_root);
		_root = NULL;
		_size = 0;
	}

	// iterator find(value_type const &value) {}
	// const_iterator find(value_type const &value) const {}

	// iterator lower_bound(const value_type &value) {}
	// const_iterator lower_bound(const value_type &value) const {}
	// iterator upper_bound(const value_type &value) {}
	// const_iterator upper_bound(const value_type &value) const {}

 private:
	void __copy_tree(pointer node) {
		if (node == NULL)
			return;
		__copy_tree(node->left);
		insert(node->data);
		__copy_tree(node->right);
	}

	void	__destroy_nodes(pointer node) {
		if (node == NULL)
			return;
		__destroy_nodes(node->left);
		__destroy_nodes(node->right);
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
	}
};

}  // namespace ft

#endif  // TREE_RB_TREE_HPP_
