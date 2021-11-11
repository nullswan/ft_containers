/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:05:40 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/10 18:20:51 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Link:
	https://www.cplusplus.com/reference/iterator/RandomAccessIterator/

	Used by:
		- vector.hpp
*/

#ifndef ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_
#define ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_

namespace ft {
template <class T>
class random_access_iterator {
 public:
	typedef T value_type;

	typedef value_type &reference;
	typedef value_type	*pointer;

 private:
	T	*_ptr;
 public:
	random_access_iterator() {}

	random_access_iterator(const random_access_iterator &rhs)
	: _ptr(rhs._ptr) {}

	~random_access_iterator() {}

	random_access_iterator &operator=(const random_access_iterator &rhs) {
		if (this != &rhs)
			_ptr = rhs._ptr;
		return *this;
	}
};

/*
	Supports the arithmetic operators
	+ and - between an iterator and an integer value,
	or subtracting an iterator from another.

	template + / - ?
*/

}  // namespace ft

#endif  // ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_
