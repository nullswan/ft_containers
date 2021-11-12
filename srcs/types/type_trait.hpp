/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_trait.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 02:34:53 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/12 02:43:14 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Link:
	https://en.cppreference.com/w/cpp/types/enable_if

	* Implementation is given.

	If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.
	This metafunction is a convenient way to leverage SFINAE to conditionally remove functions from overload resolution based on type traits and to provide separate function overloads and specializations for different type traits. std::enable_if can be used as an additional function argument (not applicable to operator overloads), as a return type (not applicable to constructors and destructors), or as a class template or function template parameter.
	The behavior of a program that adds specializations for enable_if is undefined. 

	Used by:
		- vector.hpp
*/

#ifndef TYPES_TYPE_TRAIT_HPP_
#define TYPES_TYPE_TRAIT_HPP_

namespace ft {
/*
	https://en.cppreference.com/w/cpp/types/is_integral
*/
template<class T>
struct is_integral;

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> {
	typedef T type;
};
}  // namespace ft

#endif  // TYPES_TYPE_TRAIT_HPP_
