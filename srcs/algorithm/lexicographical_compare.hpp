/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:48:37 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/11 02:34:33 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Link: 
	https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare

	Used by: 
		- vector.hpp

	* Discard constexpr as it doesn't exist in C++98
	* Code is provided in possible implementation of the algorithm.
*/

#ifndef ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_
#define ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_

namespace ft {
template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, \
	InputIt2 first2, InputIt2 last2) {
    for (; (first1 != last1) && (first2 != last2); \
		++first1, (void) ++first2) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, \
    InputIt2 first2, InputIt2 last2, \
    Compare comp) {
	for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}
}  // namespace ft

#endif  // ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_
