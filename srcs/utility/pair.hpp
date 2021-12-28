/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 03:40:17 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/28 17:29:33 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_PAIR_HPP_
#define UTILITY_PAIR_HPP_

namespace ft {
template <typename A, typename B>
class pair {
 public:
	typedef A		first_type;
	typedef B		second_type;

	first_type	first;
	second_type	second;

	pair()
	:	first(first_type()),
		second(second_type()) {}

	pair(const pair &x) {
		if (this != &x) {
			first = x.first;
			second = x.second;
		}
	}

	pair(first_type a, second_type b) {
		first = a;
		second = b;
	}

	~pair() {}

	pair &operator=(const pair &x) {
		if (this != &x) {
			first = x.first;
			second = x.second;
		}
		return *this;
	}
};

template <typename A, typename B>
ft::pair<A, B> make_pair(const A &a, const B &b) {
	return ft::pair<A, B>(a, b);
}

}  // namespace ft

#endif  // UTILITY_PAIR_HPP_
