/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_node.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:45:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/29 22:00:17 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_RB_NODE_HPP_
#define TREE_RB_NODE_HPP_

namespace ft {

enum _rb_color : bool {
	RB_BLACK, RB_RED
};

template <class T>
class rb_node {
 public:
	typedef T		value_type;
	typedef T		&reference;
	typedef T const	&const_reference;

	rb_node		*parent;
	rb_node		*left;
	rb_node		*right;
	rb_node		*RB_NULL;

	T			value;
	_rb_color	color;

 public:
	rb_node(const_reference val, rb_node *null)
	:	RB_NULL(null),
		value(val) {}

	~rb_node() {}

	rb_node<T> *prev() {
		rb_node *node = this;
		if (node->left) {
			node = max_leaf(node);
		} else {
			while (node->parent && node == node->parent->left)
				node = node->parent;
			node = node->parent;
		}
		return node;
	}
	rb_node<T>	*next() {
		rb_node *node = this;
		if (node->right) {
			node = min_leaf(node);
		} else {
			while (node->parent && node == node->parent->right)
				node = node->parent;
			node = node->parent;
		}
		return node;
	}

	rb_node<T>	*min_leaf(rb_node *node) {
		if (node == NULL)
			return NULL;
		// node = node->right;  // ! unsafe
		while (node->left != RB_NULL)
			node = node->left;
		return node;
	}

	rb_node<T>	*max_leaf(rb_node *node) {
		if (node == NULL)
			return NULL;
		// node = node->left;  // ! unsafe
		while (node->right != RB_NULL)
			node = node->right;
		return node;
	}
};

}  // namespace ft

#endif  // TREE_RB_NODE_HPP_
