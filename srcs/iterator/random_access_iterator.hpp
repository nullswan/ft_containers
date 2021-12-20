/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:05:40 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/20 08:16:02 by c3b5aw           ###   ########.fr       */
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
	random_access_iterator()
		: _base(NULL) {}
	random_access_iterator(const random_access_iterator &rhs)
		: _base(rhs._base) {}

	/*
		Fix for:
		"""
			no matching conversion for functional-style cast from 
			'ft::vector<int, std::allocator<int> >::pointer' 
				(aka 'int *')
			to
			'ft::vector<int, std::allocator<int> >::iterator' 
				(aka 'random_access_iterator<int>')
		"""
	*/
	explicit random_access_iterator(pointer base)
		: _base(base) {}

	random_access_iterator &operator=(const random_access_iterator &rhs) {
		if (this != &rhs)
			_base = rhs._base;
		return *this;
	}
	virtual ~random_access_iterator() {}

	/* const_iterator cast support */
	operator random_access_iterator<T const>() const {
		return random_access_iterator<T const>(_base);
	}

	/*
		Can be compared for equivalence using the equality/inequality operators
		(meaningful when both iterator values iterate over the same underlying sequence).
		- a == b
		- a != b
	*/
	bool	operator==	(const random_access_iterator &rhs) const {
		return _base == rhs._base;
	}
	bool	operator!=	(const random_access_iterator &rhs) const {
		return _base != rhs._base;
	}

	/*
		Can be dereferenced as an rvalue (if in a dereferenceable state).
		- *a
		- a->m
	*/
	reference operator*	() const {
		return *_base;
	}
	pointer	operator->	() const {
		return _base;
	}

	/*
		For mutable iterators (non-constant iterators):
		Can be dereferenced as an lvalue (if in a dereferenceable state).
		- *a = t
		? a->m = t
	*/

	/*
		Can be incremented (if in a dereferenceable state).
		The result is either also dereferenceable or a past-the-end iterator.
		Two iterators that compare equal, keep comparing equal after being both increased.
		++a
		a++
		*a++
	*/
	random_access_iterator &operator++	() {
		++_base;
		return *this;
	}
	random_access_iterator	operator++	(int) {
		random_access_iterator temp(*this);
		++_base;
		return temp;
	}

	/*
		Can be decremented (if a dereferenceable iterator value precedes it).
		- --a
		- a--
		- *a--
	*/
	random_access_iterator &operator--	() {
		--_base;
		return *this;
	}
	random_access_iterator operator--	(int) {
		random_access_iterator temp(*this);
		--_base;
		return temp;
	}

	/*
		Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.
		- a + n
		- n + a
		- a - n
		- a - b
	*/
	random_access_iterator 	operator+	(const difference_type &n) const {
		return random_access_iterator(_base + n);
	}
	difference_type 		operator+	(const random_access_iterator &rhs) const {
		return _base + rhs._base;
	}
	random_access_iterator 	operator-	(const difference_type &n) const {
		return random_access_iterator(_base - n);
	}
	difference_type 		operator-	(const random_access_iterator &rhs) const {
		return _base - rhs._base;
	}

	/*
		Can be compared with inequality relational operators (<, >, <= and >=).
		- a < b
		- a > b
		- a <= b
		- a >= b
	*/
	bool	operator<	(const random_access_iterator &rhs) const {
		return _base < rhs._base;
	}
	bool	operator>	(const random_access_iterator &rhs) const {
		return _base > rhs._base;
	}
	bool	operator<=	(const random_access_iterator &rhs) const {
		return _base <= rhs._base;
	}
	bool	operator>=	(const random_access_iterator &rhs) const {
		return _base >= rhs._base;
	}

	/*
		Supports compound assignment operations += and -=
		- a += n
		- a -= n
	*/
	random_access_iterator &operator+=	(difference_type n) {
		_base += n;
		return *this;
	}
	random_access_iterator &operator-=	(difference_type n) {
		_base -= n;
		return *this;
	}

	/*
		Supports the offset dereference operator ([])
		- a[n]
	*/
	reference operator[]	(difference_type n) const {
		return _base[n];
	}
};

template <class Iterator>
random_access_iterator<Iterator>	operator+	(
	typename random_access_iterator<Iterator>::difference_type n,
	const random_access_iterator<Iterator> &rhs) {
	return n + rhs;
}

template <class Iterator>
random_access_iterator<Iterator>	operator-	(
	typename random_access_iterator<Iterator>::difference_type n,
	const random_access_iterator<Iterator> &rhs) {
	return n - rhs;
}
}  // namespace ft

#endif  // ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_
