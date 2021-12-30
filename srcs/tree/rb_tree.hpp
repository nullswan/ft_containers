/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 08:00:43 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/30 16:54:46 by c3b5aw           ###   ########.fr       */
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
	- https://www.programiz.com/dsa/red-black-tree
	- https://www.programiz.com/dsa/insertion-in-a-red-black-tree
	- https://www.programiz.com/dsa/deletion-from-a-red-black-tree
	- https://iq.opengenus.org/red-black-tree-search/

	- Visualizer: https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
*/

#include <memory>

#include "rb_node.hpp"
#include "rb_iterator.hpp"

#include "../utility/pair.hpp"
#include "../iterator/reverse_iterator.hpp"

namespace ft {

template <
	class T,
	class Compare,
	class Alloc = std::allocator<rb_node<T> >
>
class rb_tree {
 public:
	typedef T		value_type;
	typedef Compare	compare_type;
	typedef Alloc 	allocator_type;

	typedef	rb_node<T>			node_value_type;
	typedef const rb_node<T>	const_node_value_type;

	typedef rb_node<T>&		reference;
	typedef rb_node<T>*		pointer;

	typedef const rb_node<T>&	const_reference;
	typedef const rb_node<T>*	const_pointer;

	typedef typename ft::rb_tree_iterator<node_value_type> 	iterator;
	typedef typename ft::rb_tree_iterator<node_value_type>	const_iterator;
	typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	typedef std::ptrdiff_t	difference_type;
	typedef std::size_t		size_type;

 private:
	allocator_type	_alloc;
	compare_type	_compare_type;

	pointer			_root;
	pointer			RB_NULL;

	size_type		_size;

 public:
	explicit rb_tree(allocator_type alloc = allocator_type())
		:	_alloc(alloc),
			_compare_type(compare_type()),
			_root(NULL),
			RB_NULL(NULL),
			_size(0) {
		__alloc_null_node();
	}

	rb_tree(const rb_tree& x)
	:	_alloc(x._alloc),
		_root(NULL),
		RB_NULL(NULL),
		_size(0) {
		__alloc_null_node();
		__copy_tree(x._root, x.RB_NULL);
	}

	rb_tree &operator=(const rb_tree &rhs) {
		if (this != &rhs) {
			clear();
			__destroy_null_node();
			_alloc = rhs._alloc;
			__alloc_null_node();
			__copy_tree(rhs._root, rhs.RB_NULL);
		}
		return *this;
	}

	~rb_tree() {
		clear();
		__destroy_null_node();
	}

	iterator begin() {
		return iterator(_root, __min_node(_root), RB_NULL);
	}
	const_iterator begin() const {
		return const_iterator(_root, __min_node(_root), RB_NULL);
	}
	iterator end() {
		return iterator(_root, RB_NULL, RB_NULL);
	}
	const_iterator end() const {
		return const_iterator(_root, RB_NULL, RB_NULL);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}
	reverse_iterator rend() {
		return reverse_iterator(begin());
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator(begin());
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

	ft::pair<iterator, bool> insert(const value_type &value) {
		return __insert_node(value);
	}
	iterator insert(iterator pos, const value_type &value) {
		(void)pos;
		return insert(value).first;
	}
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last,
				typename ft::enable_if<
					!ft::is_integral<InputIterator>::value
				>::type * = NULL) {
		for (; first != last; ++first)
			__insert_node(*first);
	}

	void	erase(iterator pos) {
		if (pos == end())
			return;
		__erase_node(pos.base);
	}
	size_type erase(const value_type &value) {
		pointer node = __lookup_node(value);
		if (node) {
			__erase_node(node);
			return 1;
		}
		return 0;
	}
	void	erase(iterator first, iterator last) {
		while (first != last)
			erase(first++);
	}

	void	swap(rb_tree &rhs) {
		std::swap(_alloc, rhs._alloc);
		std::swap(_compare_type, rhs._compare_type);

		std::swap(_root, rhs._root);
		std::swap(RB_NULL, rhs.RB_NULL);

		std::swap(_size, rhs._size);
	}

	void	clear() {
		__destroy_nodes(_root);
		_root = RB_NULL;
		_size = 0;
	}

	iterator find(const value_type &value) {
		pointer tmp = __lookup_node(value);

		if (tmp)
			return iterator(_root, tmp, RB_NULL);
		return end();
	}
	const_iterator find(const value_type &value) const {
		pointer tmp = __lookup_node(value);

		if (tmp)
			return const_iterator(_root, tmp, RB_NULL);
		return end();
	}

	iterator lower_bound(const value_type &value) {
		for (iterator it = begin(); it != end(); ++it) {
			if (_compare_type(value, it.base->value)
				|| !_compare_type(it.base->value, value))
				return it;
		}
		return end();
	}
	const_iterator lower_bound(const value_type &value) const {
		for (const_iterator it = begin(); it != end(); ++it) {
			if (_compare_type(value, it.base->value)
				|| !_compare_type(it.base->value, value))
				return it;
		}
		return end();
	}

	iterator upper_bound(const value_type &value) {
		for (iterator it = begin(); it != end(); ++it) {
			if (_compare_type(value, it.base->value))
				return it;
		}
		return end();
	}
	const_iterator upper_bound(const value_type &value) const {
		for (const_iterator it = begin(); it != end(); ++it) {
			if (_compare_type(value, it.base->value))
				return it;
		}
		return end();
	}

	ft::pair<const_iterator, const_iterator>
	equal_range(const value_type& k) const {
		const_iterator first = lower_bound(k);
		const_iterator last = upper_bound(k);

		return ft::make_pair(first, last);
	}

	ft::pair<iterator, iterator> equal_range(const value_type& k) {
		iterator first = lower_bound(k);
		iterator last = upper_bound(k);

		return ft::make_pair(first, last);
	}

 private:
	pointer	__min_node(pointer node) const {
		while (node->left != RB_NULL)
			node = node->left;
		return node;
	}
	void	__alloc_null_node() {
		RB_NULL = _alloc.allocate(1);

		RB_NULL->color = RB_BLACK;
		RB_NULL->parent = RB_NULL;
		RB_NULL->left = RB_NULL;
		RB_NULL->right = RB_NULL;

		_root = RB_NULL;
	}

	void	__destroy_null_node() {
		if (RB_NULL == NULL)
			return;
		_alloc.destroy(RB_NULL);
		_alloc.deallocate(RB_NULL, 1);
		RB_NULL = NULL;
	}

	void	__insert_fixup(pointer node) {
		pointer u;

		while (node->parent->color == RB_RED) {
			if (node->parent == node->parent->parent->right) {
				u = node->parent->parent->left;
				if (u->color == RB_RED) {
					u->color = RB_BLACK;
					node->parent->color = RB_BLACK;
					node->parent->parent->color = RB_RED;
					node = node->parent->parent;
				} else {
					if (node == node->parent->left) {
						node = node->parent;
						__rotate_right(node);
					}
					node->parent->color = RB_BLACK;
					node->parent->parent->color = RB_RED;
					__rotate_left(node->parent->parent);
				}
			} else {
				u = node->parent->parent->right;
				if (u->color == RB_RED) {
					u->color = RB_BLACK;
					node->parent->color = RB_BLACK;
					node->parent->parent->color = RB_RED;
					node = node->parent->parent;
				} else {
					if (node == node->parent->right) {
						node = node->parent;
						__rotate_left(node);
					}
					node->parent->color = RB_BLACK;
					node->parent->parent->color = RB_RED;
					__rotate_right(node->parent->parent);
				}
			}

			if (node == _root)
				break;
		}
		_root->color = RB_BLACK;
	}

	ft::pair<iterator, bool>	__insert_node(const value_type &data) {
		pointer look = __lookup_node(data);
		if (look)
			return ft::make_pair(iterator(_root, look, RB_NULL), false);

		pointer node = __alloc_node(data);
		if (!node)
			throw std::bad_alloc();

		pointer y = RB_NULL;
		pointer x = _root;

		while (x != RB_NULL) {
			y = x;
			if (_compare_type(data, x->value) > 0)
				x = x->left;
			else
				x = x->right;
		}

		node->parent = y;
		if (y == RB_NULL)
			_root = node;
		else if (_compare_type(node->value, y->value))
			y->left = node;
		else
			y->right = node;

		if (node->parent == RB_NULL) {
			node->color = RB_BLACK;
			return ft::make_pair(iterator(_root, node, RB_NULL), true);
		}

		if (node->parent->parent == RB_NULL)
			return ft::make_pair(iterator(_root, node, RB_NULL), true);

		__insert_fixup(node);
		return ft::make_pair(iterator(_root, node, RB_NULL), true);
	}

	void	__transplant(pointer u, pointer v) {
		if (u->parent == RB_NULL)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v)
			v->parent = u->parent;
	}

	void	__rotate_left(pointer node) {
		pointer tmp = node->right;

		node->right = tmp->left;
		if (tmp->left != RB_NULL)
			tmp->left->parent = node;

		tmp->parent = node->parent;
		if (node->parent == RB_NULL)
			_root = tmp;
		else if (node == node->parent->left)
			node->parent->left = tmp;
		else
			node->parent->right = tmp;
		tmp->left = node;
		node->parent = tmp;
	}

	void	__rotate_right(pointer node) {
		pointer tmp = node->left;

		node->left = tmp->right;
		if (tmp->right != RB_NULL)
			tmp->right->parent = node;

		tmp->parent = node->parent;
		if (node->parent == RB_NULL)
			_root = tmp;
		else if (node == node->parent->right)
			node->parent->right = tmp;
		else
			node->parent->left = tmp;
		tmp->right = node;
		node->parent = tmp;
	}

	void	__delete_fixup(pointer node) {
		pointer s;

		while (node != _root && node->color == RB_BLACK) {
			if (node == node->parent->left) {
				s = node->parent->right;
				if (s->color == RB_RED) {
					s->color = RB_BLACK;
					node->parent->color = RB_RED;
					__rotate_left(node->parent);
					s = node->parent->right;
				}
				if (s->left->color == RB_BLACK && s->right->color == RB_BLACK) {
					s->color = RB_RED;
					node = node->parent;
				} else {
					if (s->right->color == RB_BLACK) {
						s->left->color = RB_BLACK;
						s->color = RB_RED;
						__rotate_right(s);
						s = node->parent->right;
					}
					s->color = node->parent->color;
					node->parent->color = RB_BLACK;
					s->right->color = RB_BLACK;
					__rotate_left(node->parent);
					node = _root;
				}
			} else {
				s = node->parent->left;
				if (s->color == RB_RED) {
					s->color = RB_BLACK;
					node->parent->color = RB_RED;
					__rotate_right(node->parent);
					s = node->parent->left;
				}
				if (s->right->color == RB_BLACK && s->left->color == RB_BLACK) {
					s->color = RB_RED;
					node = node->parent;
				} else {
					if (s->left->color == RB_BLACK) {
						s->right->color = RB_BLACK;
						s->color = RB_RED;
						__rotate_left(s);
						s = node->parent->left;
					}
					s->color = node->parent->color;
					node->parent->color = RB_BLACK;
					s->left->color = RB_BLACK;
					__rotate_right(node->parent);
					node = _root;
				}
			}
		}
		node->color = RB_BLACK;
	}

	void	__erase_node(pointer node) {
		if (node == NULL)
			return;

		pointer root = _root;
		pointer z = RB_NULL;

		while (root != RB_NULL) {
			if (root->value == node->value)
				z = root;

			if (root->value <= node->value)
				root = root->right;
			else
				root = root->left;
		}

		if (z == RB_NULL)
			return;

		pointer x;
		pointer y = z;
		_rb_color y_original_color = y->color;
		if (z->left == RB_NULL) {
			x = z->right;
			__transplant(z, z->right);
		} else if (z->right == RB_NULL) {
			x = z->left;
			__transplant(z, z->left);
		} else {
			y = __min_node(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				__transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			__transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		__destroy_node(z);
		if (y_original_color == RB_BLACK)
			__delete_fixup(x);
	}

	void	__destroy_node(pointer node) {
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
		--_size;
	}

	pointer __alloc_node(const value_type &data) {
		pointer node = _alloc.allocate(1);

		node->value = data;
		node->color = RB_RED;
		node->left = RB_NULL;
		node->right = RB_NULL;
		node->parent = RB_NULL;
		++_size;
		return node;
	}

	pointer __lookup_node(const value_type &data) const {
		pointer node = _root;

		while (node != RB_NULL) {
			if (_compare_type(data, node->value))
				node = node->left;
			else if (_compare_type(node->value, data))
				node = node->right;
			else
				return node;
		}
		return NULL;
	}

	void __copy_tree(pointer node, pointer null_ref) {
		if (node == NULL || node == null_ref)
			return;
		__copy_tree(node->left, null_ref);
		__insert_node(node->value);
		__copy_tree(node->right, null_ref);
	}

	void	__destroy_nodes(pointer node) {
		if (node == NULL || node == RB_NULL)
			return;
		__destroy_nodes(node->left);
		__destroy_nodes(node->right);
		__destroy_node(node);
	}
};

}  // namespace ft

#endif  // TREE_RB_TREE_HPP_
