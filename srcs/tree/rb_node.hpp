#ifndef TREE_RB_NODE_HPP_
#define TREE_RB_NODE_HPP_

namespace ft {

enum _rb_color : bool {
	RB_BLACK, RB_RED
};

template <class T>
class rb_node {
 public:
	typedef typename T value_type;

	rb_node		*parent;
	rb_node		*left;
	rb_node		*right;

	T			value;
	_rb_color	color;

 public:
	explicit rb_node(T const &val)
	: value(val) {}
};

}  // namespace ft

#endif  // TREE_RB_NODE_HPP_
