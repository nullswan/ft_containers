/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_trait.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 02:34:53 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/30 11:00:05 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Links:
	https://en.cppreference.com/w/cpp/types/enable_if

	* Implementation is given.

	If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.
	This metafunction is a convenient way to leverage SFINAE to conditionally remove functions from overload resolution based on type traits and to provide separate function overloads and specializations for different type traits. std::enable_if can be used as an additional function argument (not applicable to operator overloads), as a return type (not applicable to constructors and destructors), or as a class template or function template parameter.
	The behavior of a program that adds specializations for enable_if is undefined. 

	https://en.cppreference.com/w/cpp/types/is_integral

	* Implementation of types is also given.

	Checks whether T is an integral type. 
	Provides the member constant value which is equal to true, if T is the type bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long long, or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants. Otherwise, value is equal to false.

	Used by:
		- vector.hpp
*/

#ifndef TYPES_TYPE_TRAIT_HPP_
#define TYPES_TYPE_TRAIT_HPP_

#include <uchar.h>

namespace ft {
template <typename T>
struct is_integral {
	const static bool value = false;
};

template <>
struct is_integral<char> {
	const static bool value = true;
};

template <>
struct is_integral<char16_t> {
	const static bool value = true;
};

template <>
struct is_integral<char32_t> {
	const static bool value = true;
};

template <>
struct is_integral<wchar_t> {
	const static bool value = true;
};

template <>
struct is_integral<short> {
	const static bool value = true;
};

template <>
struct is_integral<int> {
	const static bool value = true;
};

template <>
struct is_integral<long> {
	const static bool value = true;
};

template <>
struct is_integral<long long> {
	const static bool value = true;
};

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> {
	typedef T type;
};
}  // namespace ft

#endif  // TYPES_TYPE_TRAIT_HPP_
