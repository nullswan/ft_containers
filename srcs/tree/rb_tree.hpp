/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 08:00:43 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/28 08:01:30 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_RB_TREE_HPP_
#define TREE_RB_TREE_HPP_

/*
	Almost always mimic std::map references.
	Inspired from: https://www.cplusplus.com/reference/map/map/

	Links:
	- https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
	- https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
*/

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

	mapped_type	&operator[](const key_type &key) {
		iterator	ret = find(ft::make_pair(key, value_type));

		if (ret != end()) {
			rb_node	*tmp = ret.get_base();
			if (tmp)
				return tmp->value;
				//  ! unsafe .second;
			return NULL;
		}
		ft::pair<iterator, bool> tmp = insert(
			ft::make_pair(key, value_type));
		return tmp.first.get_base()->value;
		//  ! unsafe .second;
	}

	// ft::pair<iterator, bool> insert(value_type const &value) {}
	// iterator insert(iterator pos, const value_type &value) {}
	// template <class InputIterator>
	// 	void insert(InputIterator first, InputIterator last) {}

	// void	erase(iterator pos) {
		// check if ite node exist and attempt to delete
	// }
	// size_type erase(value_type const &value) {
		// if rb_node
			// delete ret 1
		// ret 0
	// }
	// void	erase(iterator first, iterator last) {}

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

	iterator lower_bound(const value_type &value) {
		return end();
	}
	const_iterator lower_bound(const value_type &value) const {
		return end();
	}

	iterator upper_bound(const value_type &value) {
		return end();
	}
	const_iterator upper_bound(const value_type &value) const {
		return end();
	}

 private:
	rb_node	*__insert(value_type const &data) {
		rb_node	*node = _alloc.allocate(1);

		node->color = RB_RED;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		_alloc.construct(node, data);
		return node;
	}

	rb_node	*__find(value_type const &data) const {
		rb_node *tmp = _root;

		while (tmp) {
			// ToDo: Implement find
			return tmp;
		}
		return NULL;
	}

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
