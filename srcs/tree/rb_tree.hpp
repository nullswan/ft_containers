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
	pointer			_root;
	size_type		_size;

 public:
	rb_tree()
		: _root(NULL), _size(0) {}

	~rb_tree();
};

}  // namespace ft

#endif  // TREE_RB_TREE_HPP_
