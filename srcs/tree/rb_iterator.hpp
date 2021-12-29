/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:44:49 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/29 22:07:17 by c3b5aw           ###   ########.fr       */
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

	//	this is some serious magic (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧
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

 public:
	rb_tree_iterator()
		:	_root(NULL), _base(NULL) {}

	rb_tree_iterator(node_pointer root, node_pointer base)
		:	_root(root), _base(base) {}

	rb_tree_iterator(const rb_tree_iterator& x)
		:	_root(x._root),
			_base(x._base) {}

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
			_base = _base->next();
		return *this;
	}
	rb_tree_iterator	operator++ (int) {
		rb_tree_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	rb_tree_iterator&	operator-- () {
		if (_base)
			_base = _base->prev();
		else
			_base = _base->max_leaf(_root);
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
	// __next()
	// __prev()
};

}  // namespace ft

#endif  // TREE_RB_ITERATOR_HPP_
