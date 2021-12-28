/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:21:46 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/28 13:45:08 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_TEST_HPP_
#define SET_TEST_HPP_

#include <set>

#include "set.hpp"

#include "utility/logger.hpp"
#include "utility/run_test.hpp"

namespace ft_test {
ft_test::Logger *st_log;

void	set() {
	s_log = new ft_test::Logger("set ");
}

}  // namespace ft_test

#endif  // SET_TEST_HPP_
