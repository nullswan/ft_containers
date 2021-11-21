/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:13:29 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/12 14:25:34 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Link:
	https://www.cplusplus.com/reference/iterator/iterator_traits/

	Member types
	member				generic definition			T* specialization			const T* specialization
	difference_type		Iterator::difference_type	ptrdiff_t					ptrdiff_t
	value_type			Iterator::value_type		T							T
	pointer				Iterator::pointer			T*							const T*
	reference			Iterator::reference			T&							const T&
	iterator_category	Iterator::iterator_category	random_access_iterator_tag	random_access_iterator_tag

	Used by:
		- reverse_iterator.hpp
*/
#ifndef ITERATOR_ITERATOR_TRAITS_HPP_
#define ITERATOR_ITERATOR_TRAITS_HPP_

#include <iterator>  // provide std::random_access_iterator_tag

namespace ft {
template <class Iterator>
class iterator_traits {
 public:
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*> {
	typedef ptrdiff_t	difference_type;
	typedef T	value_type;
	typedef T*	pointer;
	typedef T&	reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*> {
 public:
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef std::random_access_iterator_tag iterator_category;
};
}  // namespace ft

#endif  // ITERATOR_ITERATOR_TRAITS_HPP_
