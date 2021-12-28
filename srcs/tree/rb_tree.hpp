/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 08:00:43 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/28 12:11:02 by c3b5aw           ###   ########.fr       */
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
	- https://www.programiz.com/dsa/insertion-in-a-red-black-tree
	- https://www.programiz.com/dsa/deletion-from-a-red-black-tree
	- https://iq.opengenus.org/red-black-tree-search/
*/

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
	typedef Compare	compare_type;
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
	compare_type	_compare_type;
	pointer			_root;
	size_type		_size;

 public:
	explicit rb_tree(allocator alloc = allocator())
		:	_alloc(alloc),
			_compare_type(compare_type()),
			_root(NULL),
			_size(0) {}

	rb_tree(const rb_tree& other)
		:	_alloc(other._alloc),
			_root(NULL)
			_size(other._size) {
		__copy_tree(other._root);
	}

	rb_tree &operator=(const rb_tree &rhs) {
		if (this != &rhs) {
			_alloc = rhs._alloc;
			_root = NULL;
			_size = rhs._size;
			__destroy_tree(_root);
			__copy_tree(rhs._root);
		}
		return *this;
	}

	~rb_tree() { clear(); }

	iterator begin() {
		return iterator(_root, rb_node::min_leaf(_root));
	}
	const_iterator begin() const {
		return iterator(_root, rb_node::min_leaf(_root));
	}
	iterator end() {
		return iterator(_root, NULL);
	}
	const_iterator end() const {
		return iterator(_root, NULL);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(_root, NULL);
	}
	const_reverse_iterator rbegin() const {
		return reverse_iterator(_root, NULL);
	}
	reverse_iterator rend() {
		return reverse_iterator(_root, rb_node::min_leaf(_root));
	}
	const_reverse_iterator rend() const {
		return reverse_iterator(_root, rb_node::min_leaf(_root));
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

	mapped_type	&operator[](const key_type &key) {
		iterator	ret = find(ft::make_pair(key, value_type));

		if (ret != end()) {
			rb_node	*tmp = ret.get_base();
			if (tmp)
				return tmp->value;
				//  ! unsafe .second;
			return NULL;
		}
		ft::pair<iterator, bool> tmp = insert(
			ft::make_pair(key, value_type));
		return tmp.first.get_base()->value;
		//  ! unsafe .second;
	}

	// ft::pair<iterator, bool> insert(value_type const &value) {}
	// iterator insert(iterator pos, const value_type &value) {}
	// template <class InputIterator>
	// void insert(InputIterator first, InputIterator last,
	// 	typename ft::enable_if<!ft::is_integral<InputIterator>::value,
	// 	InputIterator::type* = NULL) {
	// }

	void	erase(iterator pos) {
		if (pos == end())
			return;
		__erase_node(pos.get_base());
	}
	size_type erase(value_type const &value) {
		rb_node	*node = __find_node(value);
		if (node) {
			__erase_node(node);
			return 1;
		}
		return 0;
	}
	void	erase(iterator first, iterator last) {
		while (first != last) {
			erase(*first);
			++first;
		}
	}

	void	swap(rb_tree &rhs) {
		std::swap(_alloc, rhs._alloc);
		std::swap(_compare, rhs._compare);
		std::swap(_root, rhs._root);
		std::swap(_size, rhs._size);
	}

	void	clear() {
		__destroy_tree(_root);
		_root = NULL;
		_size = 0;
	}

	iterator find(value_type const &value) {
		rb_node	*tmp = __lookup_node(value);

		if (tmp)
			return iterator(_root, tmp);
		return end();
	}
	const_iterator find(value_type const &value) const {
		rb_node	*tmp = __lookup_node(value);

		if (tmp)
			return const_iterator(_root, tmp);
		return end();
	}

	iterator lower_bound(const value_type &value) {
		return end();
	}
	const_iterator lower_bound(const value_type &value) const {
		return end();
	}

	iterator upper_bound(const value_type &value) {
		return end();
	}
	const_iterator upper_bound(const value_type &value) const {
		return end();
	}

 private:
	void	__insert_fixup(rb_node *node) {
		rb_node *u;

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
						__right_rotate(node);
					}
					node->parent->color = RB_BLACK;
					node->parent->parent->color = RB_RED;
					__left_rotate(node->parent->parent);
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
						__left_rotate(node);
					}
					node->parent->color = RB_BLACK;
					node->parent->parent->color = RB_RED;
					__right_rotate(node->parent->parent);
				}
			}

			if (node == _root)
				break;
		}
		_root->color = RB_BLACK;
	}

	void	__insert_node(const value_type &data) {
		// ! What if it exists already
		rb_node	*node = __alloc_node(data);

		if (!node)
			return;

		rb_node	*y = NULL;
		rb_node	*x = _root;

		while (x) {
			y = x;
			if (_compare_type(node->value, x->value))
				x = x->left;
			else
				x = x->right;
		}

		node->parent = y;
		if (!y)
			_root = node;
		else if (_compare_type(node->value, y->value))
			y->left = node;
		else
			y->right = node;

		if (node->parent == NULL) {
			node->parent->color = RB_BLACK;
			return;
		}

		if (node->parent->parent == NULL)
			return;

		__insert_fixup(node);
	}

	void	__transplant(rb_node *u, rb_node *v) {
		if (u->parent == NULL)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v)
			v->parent = u->parent;
	}

	void	__left_rotate(rb_node *node) {
		rb_node *tmp = node->right;

		node->right = tmp->left;
		if (tmp->left)
			tmp->left->parent = node;

		tmp->parent = node->parent;
		if (node->parent == NULL)
			_root = tmp;
		else if (node == node->parent->left)
			node->parent->left = tmp;
		else
			node->parent->right = tmp;
		tmp->left = node;
		node->parent = tmp;
	}

	void	__right_rotate(rb_node *node) {
		rb_node	*tmp = node->left;

		node->left = tmp->right;
		if (tmp->right)
			tmp->right->parent = node;

		tmp->parent = node->parent;
		if (node->parent == NULL)
			_root = tmp;
		else if (node == node->parent->left)
			node->parent->left = tmp;
		else
			node->parent->right = tmp;
		tmp->right = node;
		node->parent = tmp;
	}

	void	__delete_fixup(rb_node *node) {
		rb_node	*s;

		while (node != _root && node->color == RB_BLACK) {
			if (node == node->parent->left) {
				s = node->parent->right;
				if (s->color == RB_RED) {
					s->color = RB_BLACK;
					node->parent->color = RB_RED;
					__left_rotate(node->parent);
					s = node->parent->right;
				}
				if (s->left->color == RB_BLACK && s->right->color == RB_BLACK) {
					s->color = RB_RED;
					node = node->parent;
				} else {
					if (s->right->color == RB_BLACK) {
						s->left->color = RB_BLACK;
						s->color = RB_RED;
						__right_rotate(s);
						s = node->parent->right;
					}
					s->color = node->parent->color;
					node->parent->color = RB_BLACK;
					s->right->color = RB_BLACK;
					__left_rotate(node->parent);
					node = _root;
				}
			} else {
				s = node->parent->left;
				if (s->color == RB_RED) {
					s->color = RB_BLACK;
					node->parent->color = RB_RED;
					__right_rotate(node->parent);
					s = node->parent->left;
				}
				if (s->right->color == RB_BLACK && s->left->color == RB_BLACK) {
					s->color = RB_RED;
					node = node->parent;
				} else {
					if (s->left->color == RB_BLACK) {
						s->right->color = RB_BLACK;
						s->color = RB_RED;
						__left_rotate(s);
						s = node->parent->left;
					}
					s->color = node->parent->color;
					node->parent->color = RB_BLACK;
					s->left->color = RB_BLACK;
					__right_rotate(node->parent);
					node = _root;
				}
			}
		}
		node->color = RB_BLACK;
	}

	void	__erase_node(rb_node *node) {
		if (node == NULL)
			return;

		rb_node *root = _root;
		rb_node *z = NULL;

		while (root) {
			if (root->data == node->data)
				z = root;

			if (root->data <= node->data)
				root = root->right;
			else
				root = root->left;
		}

		if (z == NULL)
			return;

		rb_node *x;
		rb_node *y = z;
		_rb_color y_original_color = y->color;
		if (z->left == NULL) {
			x = z->right;
			__transplant(z, z->right);
		} else if (z->right == NULL) {
			x = z->left;
			__transplant(z, z->left);
		} else {
			y = rb_node::min_leaf(z->right);
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
		if (y_original_color == _rb_black)
			__delete_fixup(x);
	}

	void	__destroy_node(rb_node *node) {
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
		--_size;
	}

	rb_node	*__alloc_node(const value_type &data) {
		rb_node	*node = _alloc.allocate(1);

		node->color = RB_RED;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
		_alloc.construct(node->data, data);
		return node;
	}

	rb_node	*__lookup_node(const value_type &data) const {
		rb_node *node = _root;

		while (node) {
			int	cmp = _compare(data, node->data);
			if (cmp  == 0)
				return node;
			else if (cmp < 0)
				node = node->left;
			else
				node = node->right;
		}
		return NULL;
	}

	void __copy_tree(pointer node) {
		if (node == NULL)
			return;
		__copy_tree(node->left);
		insert(node->data);
		__copy_tree(node->right);
	}

	void	__destroy_nodes(pointer node) {
		if (node == NULL)
			return;
		__destroy_nodes(node->left);
		__destroy_nodes(node->right);
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
	}
};

}  // namespace ft

#endif  // TREE_RB_TREE_HPP_
