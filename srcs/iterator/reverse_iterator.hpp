/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:31:00 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/09 23:36:19 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://en.cppreference.com/w/cpp/iterator/reverse_iterator
#ifndef REVERSE_ITERATOR_HPP_
#define REVERSE_ITERATOR_HPP_

namespace ft {
template <class Iter>
class reverse_iterator {
 public:
	typedef Iter iterator_type;

 public:
	reverse_iterator();
};
};

#endif  // REVERSE_ITERATOR_HPP_
