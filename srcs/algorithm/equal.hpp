/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:50:26 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/11 02:27:40 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Link:
	https://en.cppreference.com/w/cpp/algorithm/equal

	Used by:
		- vector.hpp
*/

#ifndef ALGORITHM_EQUAL_HPP_
#define ALGORITHM_EQUAL_HPP_

namespace ft {
template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	for (; first1 != last1; ++first1, ++first2) {
		if (*first1 != *first2)
			return false;
	}
	return true;
}

template< class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, \
	InputIt2 first2, BinaryPredicate p) {
	for (; first1 != last1; ++first1, ++first2) {
		if (!p(*first1, *first2))
			return false;
	}
	return true;
}
}  // namespace ft

#endif  // ALGORITHM_EQUAL_HPP_
