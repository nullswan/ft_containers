/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:44:49 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/30 20:23:41 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_RB_ITERATOR_HPP_
#define TREE_RB_ITERATOR_HPP_

namespace ft {

#include <cstddef>  // Implement ptrdiff_t

#include "rb_node.hpp"

template <class T>
class rb_tree_iterator {
 public:
	typedef T*			node_pointer;

	/*
		this is some serious magic (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧
		use the value_type of T which is the node,
		instead of rb_node<T> we only get the T of the node.
	*/
	typedef typename T::value_type const value_type;

	/* reserved for reverse iterator && iterators traits */
	typedef typename std::ptrdiff_t difference_type;
	typedef typename std::bidirectional_iterator_tag iterator_category;

	typedef value_type &reference;
	typedef value_type const &const_reference;
	typedef value_type *pointer;
	typedef value_type const *const_pointer;

	node_pointer base;
	node_pointer RB_NULL;

 private:
	node_pointer	_root;

 public:
	rb_tree_iterator()
	:	base(NULL),
		RB_NULL(NULL),
		_root(NULL) {}

	rb_tree_iterator(node_pointer root, node_pointer base, node_pointer null)
	:	base(base),
		RB_NULL(null),
		_root(root) {}

	rb_tree_iterator(const rb_tree_iterator& x)
	:	base(x.base),
		RB_NULL(x.RB_NULL),
		_root(x._root) {}

	rb_tree_iterator &operator=(const rb_tree_iterator& rhs) {
		if (this != &rhs) {
			base = rhs.base;
			RB_NULL = rhs.RB_NULL;
			_root = rhs._root;
		}
		return *this;
	}

	~rb_tree_iterator() {}

	/* const_iterator cast support */
	operator rb_tree_iterator<T const>() const {
		return rb_tree_iterator<T const>(_root, base, RB_NULL);
	}

	/*
		Operators used to compare iterators
	*/
	bool	operator==	(const rb_tree_iterator& rhs) const {
		return base == rhs.base;
	}
	bool	operator!=	(const rb_tree_iterator& rhs) const {
		return base != rhs.base;
	}

	reference	operator*		() {
		return base->value;
	}

	const_reference	operator*	() const {
		return base->value;
	}

	pointer		operator->		() {
		return &base->value;
	}

	const_pointer	operator->	() const {
		return &base->value;
	}

	rb_tree_iterator&	operator++ () {
		if (base != RB_NULL)
			base = __next(base);
		return *this;
	}
	rb_tree_iterator	operator++ (int) {
		rb_tree_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	rb_tree_iterator&	operator-- () {
		if (base != RB_NULL)
			base = __prev(base);
		else
			base = __max_leaf(_root);
		return *this;
	}
	rb_tree_iterator	operator-- (int) {
		rb_tree_iterator tmp(*this);
		--(*this);
		return tmp;
	}

 private:
	node_pointer __max_leaf(node_pointer node) const {
		while (node->right != RB_NULL)
			node = node->right;
		return node;
	}

	node_pointer	__prev(node_pointer node) const {
		if (node->left != RB_NULL)
			return __max_leaf(node->left);

		while (node->parent != RB_NULL && node == node->parent->left)
			node = node->parent;
		return node->parent;
	}

	node_pointer	__min_leaf(node_pointer node) const {
		while (node->left != RB_NULL)
			node = node->left;
		return node;
	}

	node_pointer	__next(node_pointer node) const {
		if (node->right != RB_NULL)
			return __min_leaf(node->right);

		while (node->parent != RB_NULL && node == node->parent->right)
			node = node->parent;
		return node->parent;
	}
};

}  // namespace ft

#endif  // TREE_RB_ITERATOR_HPP_
