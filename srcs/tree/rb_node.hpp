/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_node.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:45:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/30 07:41:20 by c3b5aw           ###   ########.fr       */
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

	T			value;
	_rb_color	color;

 public:
	explicit rb_node(const_reference val)
	:	value(val) {}

	~rb_node() {}
};

}  // namespace ft

#endif  // TREE_RB_NODE_HPP_
