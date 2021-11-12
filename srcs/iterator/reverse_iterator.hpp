/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:31:00 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/12 14:36:23 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Link:
	https://en.cppreference.com/w/cpp/iterator/reverse_iterator

	This class reverses the direction in which a bidirectional or random-access iterator iterates through a range.
	A copy of the original iterator (the base iterator) is kept internally and used to reflect the operations performed on the reverse_iterator: whenever the reverse_iterator is incremented, its base iterator is decreased, and vice versa. A copy of the base iterator with the current state can be obtained at any time by calling member base.

	Used by:
		- vector.hpp
*/

#ifndef ITERATOR_REVERSE_ITERATOR_HPP_
#define ITERATOR_REVERSE_ITERATOR_HPP_

#include "iterator_traits.hpp"

namespace ft {
template <class Iterator>
class reverse_iterator {
 public:
	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/

		Defined in member types.
	*/

	typedef Iterator iterator_type;
	typedef typename \
		iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

 public:
	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
	
		(1) default constructor
		Constructs a reverse iterator that points to no object.
		The internal base iterator is value-initialized.
	*/
	reverse_iterator()
		: _base(Iterator()) {}

	/*
		(2) initalization constructor
    	Constructs a reverse iterator from some original iterator it. The behavior of the constructed object replicates the original, except that it iterates through its pointed elements in the reverse order.
	*/
	explicit reverse_iterator(iterator_type it)
		: _base(it) {}

	/*
		(3) copy / type-cast constructor
    	Constructs a reverse iterator from some other reverse iterator. The constructed object keeps the same sense of iteration as rev_it.
	*/
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it)
		: _base(rev_it._base) {}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/base/

			Returns a copy of the base iterator.
	*/
	iterator_type base() const {
		return _base;
	}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator*\/
		Returns a reference to the element pointed to by the iterator.
		Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
	*/
	reference operator*() const {
		iterator_type temp = _base;
		return *--temp;
	}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator+/

		Returns a reverse iterator pointing to the element located n positions away from the element the iterator currently points to.
		Internally, the function applies the binary operator- on the base iterator and returns a reverse iterator constructed with the resulting iterator value.
	*/
	reverse_iterator operator+ (difference_type n) const;

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator++/
		Advances the reverse_iterator by one position.
		Internally, the pre-increment version (1) decrements the base iterator kept by the object (as if applying operator-- to it).
	*/
	reverse_iterator& operator++();

	/*
		The post-increment version (2) is implemented with a behavior equivalent to:
		reverse_iterator operator++(int) {
			reverse_iterator temp = *this;
			++(*this);
			return temp;
		}
	*/
	reverse_iterator  operator++(int);


	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator+=/
	*/
	reverse_iterator& operator+= (difference_type n);


	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator-/
	*/
	reverse_iterator operator- (difference_type n) const;

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator--/
	*/
	reverse_iterator& operator--();
	reverse_iterator  operator--(int);

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator-=/
	*/
	reverse_iterator& operator-= (difference_type n);

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator-%3E/
	*/
	pointer operator->() const;

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator[]/
	*/
	reference operator[] (difference_type n) const;

 private:
	iterator_type	_base;

/*
	https://www.cplusplus.com/reference/iterator/reverse_iterator/operators/
*/
template <class Iterator>
bool operator==	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs);

template <class Iterator>
bool operator!=	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs);

template <class Iterator>
bool operator<	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs);

template <class Iterator>
bool operator<=	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs);

template <class Iterator>
bool operator>	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs);

template <class Iterator>
bool operator>=	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs);
};
}  // namespace ft

#endif  // ITERATOR_REVERSE_ITERATOR_HPP_
