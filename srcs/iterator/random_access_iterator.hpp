/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:05:40 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/12 15:56:50 by c3b5aw           ###   ########.fr       */
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
	/*
		https://www.cplusplus.com/reference/iterator/iterator/
		
		Member types of iterator template

		member 				type definition								notes
		iterator_category	the first template parameter (Category)	
		value_type			the second template parameter (T)	
		difference_type		the third template parameter (Distance)		defaults to: ptrdiff_t
		pointer				the fourth template parameter (Pointer)		defaults to: T*
		reference			the fifth template parameter (Reference)	defaults to: T&
	*/
	typedef std::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

 private:
	T	*_base;

 public:
	/*
		Is default-constructible, copy-constructible, copy-assignable and destructible
		- X a;
		- X b(a);
		- b = a;
	*/
	random_access_iterator() {
		_base = NULL;
	}
	random_access_iterator(const random_access_iterator &rhs)
	: _base(rhs._ptr) {}
	random_access_iterator &operator=(const random_access_iterator &rhs) {
		if (this != &rhs)
			_base = rhs._base;
		return *this;
	}
	~random_access_iterator() {}

	/*
		Can be compared for equivalence using the equality/inequality operators
		(meaningful when both iterator values iterate over the same underlying sequence).
		- a == b
		- a != b
	*/

	/*
		Can be dereferenced as an rvalue (if in a dereferenceable state).
		- *a
		- a->m
	*/

	/*
		For mutable iterators (non-constant iterators):
		Can be dereferenced as an lvalue (if in a dereferenceable state).
		- *a = t
	*/

	/*
		Can be incremented (if in a dereferenceable state).
		The result is either also dereferenceable or a past-the-end iterator.
		Two iterators that compare equal, keep comparing equal after being both increased.
		++a
		a++
		*a++
	*/

	/*
		Can be decremented (if a dereferenceable iterator value precedes it).
		- --a
		- a--
		- *a--
	*/

	/*
		Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.
		- a + n
		- n + a
		- a - n
		- a - b
	*/

	/*
		Can be compared with inequality relational operators (<, >, <= and >=).
		- a < b
		- a > b
		- a <= b
		- a >= b
	*/

	/*
		Supports compound assignment operations += and -=
		- a += n
		- a -= n
	*/

	/*
		Supports the offset dereference operator ([])
		- a[n]
	*/
};

}  // namespace ft

#endif  // ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_
