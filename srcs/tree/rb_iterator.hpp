/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 07:44:49 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/26 17:28:22 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_RB_ITERATOR_HPP_
#define TREE_RB_ITERATOR_HPP_

namespace ft {

template <class T>
class rb_tree_iterator {
 public:
	typedef typename T* node;

	typedef typename T::value_type			&reference;
	typedef typename T::value_type const	&const_reference;
	typedef typename T::value_type			*pointer;
	typedef typename T::value_type const	*const_pointer;

 private:
	node	_base;

 public:
	rb_tree_iterator()
		: _base(NULL) {}
	explicit rb_tree_iterator(pointer node)
		: _base(node) {}

	rb_tree_iterator(const rb_tree_iterator& other)
		: _base(other._base) {}

	rb_tree_iterator &operator=(const rb_tree_iterator& rhs) {
		if (this != &rhs)
			_base = rhs._base;
		return *this;
	}

	~rb_tree_iterator() {}

	/* const_iterator cast support */
	operator rb_tree_iterator<T const>() const {
		return rb_tree_iterator<T const>(_base);
	}

	bool	operator== (const rb_tree_iterator& rhs) const {
		return _base == rhs._base;
	}
	bool	operator!= (const rb_tree_iterator& rhs) const {
		return _base != rhs._base;
	}

	reference	operator*		() const {
		return _base->data;
	}
	const_reference operator*	() const {
		return _base->data;
	}

	pointer		operator->	() const {
		return &_base->data;
	}
	const_pointer operator->() const {
		return &_base->data;
	}

	rb_tree_iterator&	operator++ () {
		if (_base)
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
		return *this;
	}
	rb_tree_iterator	operator-- (int) {
		rb_tree_iterator tmp(*this);
		--(*this);
		return tmp;
	}
};

}  // namespace ft

#endif  // TREE_RB_ITERATOR_HPP_
