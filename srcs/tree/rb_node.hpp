/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_node.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:45:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/26 18:10:44 by c3b5aw           ###   ########.fr       */
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
	typedef typename T	value_type;
	typedef typename T& reference;
	typedef typename T const& const_reference;

	rb_node		*parent;
	rb_node		*left;
	rb_node		*right;

	T			value;
	_rb_color	color;

 public:
	explicit rb_node(const_reference val)
		: value(val) {}

	~rb_node() {}

	static rb_node *prev() {
		rb_node *node = this;
		if (node->left) {
			// max
			node = node->left;
			while (node->right)
				node = node->right;
		} else {
			while (node->parent && node == node->parent->left)
				node = node->parent;
			node = node->parent;
		}
		return node;
	}
	static rb_node	*next() {
		rb_node *node = this;
		if (node->right) {
			// min
			node = node->right;
			while (node->left)
				node = node->left;
		} else {
			while (node->parent && node == node->parent->right)
				node = node->parent;
			node = node->parent;
		}
		return node;
	}

	static rb_node	*min_leaf(rb_node *node) {
		if (node == NULL)
			return NULL;
		node = node->right;  // ! unsafe
		while (node->left)
			node = node->left;
		return node;
	}

	static rb_node	*max_leaf(rb_node *node) {
		if (node == NULL)
			return NULL;
		node = node->left;  // ! unsafe
		while (node->right != NULL)
			node = node->right;
		return node;
	}
};

}  // namespace ft

#endif  // TREE_RB_NODE_HPP_
