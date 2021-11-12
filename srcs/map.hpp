/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:50:07 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/12 03:42:32 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <memory>		// provides std::allocator
#include <functional>   // provides std::less

#include "utility/pair.hpp"

namespace ft {
template <
	class Key,												// map::key_type
	class T,												// map::mapped_type
	class Compare = std::less<Key>,							// map::key_compare
	class Alloc = std::allocator<ft::pair<const Key, T> >   // map::allocator_type
>
class map {
 public:
 private:
};
}  // namespace ft

#endif  // MAP_HPP_
