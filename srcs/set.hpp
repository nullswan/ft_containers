/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:50:22 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/26 18:44:10 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP_
#define SET_HPP_

/*
	Link:
	https://www.cplusplus.com/reference/set/set/
*/

#include <memory>		// provides std::allocator
#include <functional>   // provides std::less

namespace ft {
template <
	class T,							// set::key_type/value_type
	class Compare = std::less<T>,		// set::key_compare/value_compare
	class Alloc = std::allocator<T>		// set::allocator_type
>
class set {
};
}  // namespace ft

#endif  // SET_HPP_
