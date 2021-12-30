/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_node.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:45:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/30 19:49:43 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_RB_NODE_HPP_
#define TREE_RB_NODE_HPP_

namespace ft {

enum _rb_color : bool {
	RB_BLACK, RB_RED
};

template <class T>
struct rb_node {
	typedef T value_type;

	rb_node	*parent;
	rb_node	*left;
	rb_node	*right;

	_rb_color	color;

	T	value;

	explicit rb_node(T const &val)
	:	value(val) {}
};
}  // namespace ft

#endif  // TREE_RB_NODE_HPP_
