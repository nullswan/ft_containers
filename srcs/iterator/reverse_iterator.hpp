/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:31:00 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/10 18:09:05 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Link:
	https://en.cppreference.com/w/cpp/iterator/reverse_iterator

	Used by:
		- vector.hpp
*/

#ifndef ITERATOR_REVERSE_ITERATOR_HPP_
#define ITERATOR_REVERSE_ITERATOR_HPP_

namespace ft {
template <class Iter>
class reverse_iterator {
 public:
	typedef Iter iterator_type;

 public:
	reverse_iterator();
};
}  // namespace ft

#endif  // ITERATOR_REVERSE_ITERATOR_HPP_
