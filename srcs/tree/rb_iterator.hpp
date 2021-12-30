/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:44:49 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/30 07:40:58 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_RB_ITERATOR_HPP_
#define TREE_RB_ITERATOR_HPP_

namespace ft {

#include "rb_node.hpp"

template <class T>
class rb_tree_iterator {
 public:
	typedef T*			node_pointer;

	//  this is some serious magic (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧
	//  use the value_type of T which is the node,
	//  instead of rb_node<T> we only get the T of the node.
	typedef typename T::value_type const value_type;

	typedef value_type &reference;
	typedef value_type const &const_reference;
	typedef value_type *pointer;
	typedef value_type const *const_pointer;

 private:
	node_pointer	_root;
	node_pointer	_base;
	node_pointer	RB_NULL;

 public:
	rb_tree_iterator()
	:	_root(NULL),
		_base(NULL),
		RB_NULL(NULL) {}

	rb_tree_iterator(node_pointer root, node_pointer base, node_pointer null)
	:	_root(root),
		_base(base),
		RB_NULL(null) {}

	rb_tree_iterator(const rb_tree_iterator& x)
	:	_root(x._root),
		_base(x._base),
		RB_NULL(x.RB_NULL) {}

	rb_tree_iterator &operator=(const rb_tree_iterator& rhs) {
		if (this != &rhs) {
			_root = rhs._root;
			_base = rhs._base;
		}
		return *this;
	}

	~rb_tree_iterator() {}

	/* const_iterator cast support */
	operator rb_tree_iterator<T const>() const {
		return rb_tree_iterator<T const>(_root, _base);
	}

	bool	operator== (const rb_tree_iterator& rhs) const {
		return _base == rhs._base;
	}
	bool	operator!= (const rb_tree_iterator& rhs) const {
		return _base != rhs._base;
	}

	reference	operator*		() {
		return _base->value;
	}

	const_reference	operator*	() const {
		return _base->value;
	}

	pointer		operator->		() {
		return &_base->value;
	}

	const_pointer	operator->	() const {
		return &_base->value;
	}

	rb_tree_iterator&	operator++ () {
		if (_base != NULL)
			_base = __next(_base);
		return *this;
	}
	rb_tree_iterator	operator++ (int) {
		rb_tree_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	rb_tree_iterator&	operator-- () {
		if (_base)
			_base = __prev(_base);
		else
			_base = __max_leaf(_root);
		return *this;
	}
	rb_tree_iterator	operator-- (int) {
		rb_tree_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	pointer get_base() const {
		return _base;
	}

 private:
	node_pointer __max_leaf(node_pointer node) {
		if (node == NULL)
			return NULL;
		while (node->right != RB_NULL)
			node = node->right;
		return node;
	}

	node_pointer	__prev(node_pointer node) {
		if (node->left != RB_NULL) {
			node = __max_leaf(node);
		} else {
			while (node->parent && node == node->parent->left)
				node = node->parent;
			node = node->parent;
		}
		return node;
	}

	node_pointer	__min_leaf(node_pointer node) {
		if (node == NULL)
			return NULL;
		while (node->left != RB_NULL)
			node = node->left;
		return node;
	}

	node_pointer	__next(node_pointer node) {
		if (node->right != RB_NULL) {
			node = __min_leaf(node);
		} else {
			while (node->parent && node->parent->right)
				node = node->parent;
			node = node->parent;
		}
		return node;
	}
};

}  // namespace ft

#endif  // TREE_RB_ITERATOR_HPP_
