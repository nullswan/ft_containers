/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:31:00 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/26 16:31:20 by c3b5aw           ###   ########.fr       */
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
#include "random_access_iterator.hpp"

namespace ft {
template <class Iterator>
class reverse_iterator {
 public:
	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/

		member				definition in reverse_iterator					description
		iterator_type		Iterator										Iterator's type
		iterator_category	iterator_traits<Iterator>::iterator_category	Preserves Iterator's category
		value_type			iterator_traits<Iterator>::value_type			Preserves Iterator's value type
		difference_type		iterator_traits<Iterator>::difference_type		Preserves Iterator's difference type
		pointer				iterator_traits<Iterator>::pointer				Preserves Iterator's pointer type
		reference			iterator_traits<Iterator>::reference			Preserves Iterator's reference type
	*/

	typedef Iterator iterator_type;
	typedef typename \
		iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

 private:
	iterator_type	_base;

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

	explicit reverse_iterator(pointer ptr)
		: _base(ptr) {}

	/*
		(3) copy / type-cast constructor
    	Constructs a reverse iterator from some other reverse iterator. The constructed object keeps the same sense of iteration as rev_it.
	*/
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it)
		: _base(rev_it.base()) {}

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
	reverse_iterator& operator++() {
		--_base;
		return *this;
	}
	/*
		The post-increment version (2) is implemented with a behavior equivalent to:
		reverse_iterator operator++(int) {
			reverse_iterator temp = *this;
			++(*this);
			return temp;
		}
	*/
	reverse_iterator  operator++(int) {
		reverse_iterator temp = *this;
		++(*this);  // Will call reverse_iterator& operator++()
		return temp;
	}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator+=/

		Advances the reverse_iterator by n element positions.
		Internally, the function decreases by n the base iterator kept by the object (as if applying operator-= to it).
	*/
	reverse_iterator& operator+= (difference_type n) {
		_base -= n;
		return *this;
	}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator-/

		Returns a reverse iterator pointing to the element located n positions before the element the iterator currently points to.
		Internally, the function applies the binary operator+ on the base iterator and returns a reverse iterator constructed with the resulting iterator value.
	*/
	reverse_iterator operator- (difference_type n) const {
		return reverse_iterator(_base + n);
	}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator--/

		Decreases the reverse_iterator by one position.
		Internally, the pre-decrement version (1) increments the base iterator kept by the object (as if applying operator++ to it).
	*/
	reverse_iterator& operator--() {
		++_base;
		return *this;
	}
	/*
		The post-decrement version (2) is implemented with a behavior equivalent to:
		reverse_iterator operator--(int) {
			reverse_iterator temp = *this;
			--(*this);
			return temp;
		}
	*/
	reverse_iterator  operator--(int) {
		reverse_iterator temp = *this;
		--(*this);  // Will call reverse_iterator& operator--()
		return temp;
	}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator-=/
		
		Descreases the reverse_iterator by n element positions.
		Internally, the function increases by n the base iterator kept by the object (as if applying operator+= to it).
	*/
	reverse_iterator& operator-= (difference_type n) {
		_base += n;
		return *this;
	}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator-%3E/
	
		Returns a pointer to the element pointed to by the iterator (in order to access one of its members).
		Internally, the function calls operator* and returns its address, as if implemented as:
		pointer operator->() const {
			return &(operator*());
		}
	*/
	pointer operator->() const {
		return &(operator*());
	}

	/*
		https://www.cplusplus.com/reference/iterator/reverse_iterator/operator[]/
	
		Dereference iterator with offset
		Accesses the element located n positions away from the element currently pointed to by the iterator.
		If such an element does not exist, it causes undefined behavior.
		Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].
	*/
	reference operator[] (difference_type n) const {
		return base()[-n-1];
	}
};
/*
	https://www.cplusplus.com/reference/iterator/reverse_iterator/operators/

	Relational operators for reverse_iterator
	Performs the appropriate comparison operation between the reverse_iterator objects lhs and rhs.

	Internally, the function compares directly the base iterators using the reflexively equivalent relational operator:

	operator on
	reverse iterators	equivalent used on base iterators
	==					==
	!=					!=
	<					>
	<=					>=
	>					<
	>=					<=
*/
template <class Iterator>
bool operator==	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs) {
	return lhs.base() == rhs.base();
}
template <class IteratorA, class IteratorB>
bool operator==	(const reverse_iterator<IteratorA>& lhs, \
	const reverse_iterator<IteratorB>& rhs) {
	return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs) {
	return lhs.base() != rhs.base();
}
template <class IteratorA, class IteratorB>
bool operator!=	(const reverse_iterator<IteratorA>& lhs, \
	const reverse_iterator<IteratorB>& rhs) {
	return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs) {
	return lhs.base() > rhs.base();
}
template <class IteratorA, class IteratorB>
bool operator<	(const reverse_iterator<IteratorA>& lhs, \
	const reverse_iterator<IteratorB>& rhs) {
	return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator<=	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs) {
	return lhs.base() >= rhs.base();
}
template <class IteratorA, class IteratorB>
bool operator<=	(const reverse_iterator<IteratorA>& lhs, \
	const reverse_iterator<IteratorB>& rhs) {
	return lhs.base() >= rhs.base();
}

template <class Iterator>
bool operator>	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs) {
	return lhs.base() < rhs.base();
}
template <class IteratorA, class IteratorB>
bool operator>	(const reverse_iterator<IteratorA>& lhs, \
	const reverse_iterator<IteratorB>& rhs) {
	return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator>=	(const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs) {
	return lhs.base() <= rhs.base();
}
template <class IteratorA, class IteratorB>
bool operator>=	(const reverse_iterator<IteratorA>& lhs, \
	const reverse_iterator<IteratorB>& rhs) {
	return lhs.base() <= rhs.base();
}

/*
	https://www.cplusplus.com/reference/iterator/reverse_iterator/operator_plus-free/

	Addition operator
	Returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it.
	The function returns the same as: rev_it+n (see reverse_iterator::operator+).
	This operator is also overloaded as a member function to return a reverse iterator offset by -n element positions (see reverse_iterator::operator-).

*/

template <class Iterator>
reverse_iterator<Iterator> operator+ ( \
	typename reverse_iterator<Iterator>::difference_type n, \
	const reverse_iterator<Iterator>& rev_it) {
	return rev_it + n;
}

/*
	https://www.cplusplus.com/reference/iterator/reverse_iterator/operator_minus-free/

	Subtraction operator
	Returns the distance between lhs and rhs.
	The function returns the same as subtracting lhs's base iterator from rhs's base iterator.

*/

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- ( \
	const reverse_iterator<Iterator>& lhs, \
	const reverse_iterator<Iterator>& rhs) {
	return rhs._base - lhs._base;
}
}  // namespace ft

#endif  // ITERATOR_REVERSE_ITERATOR_HPP_
