/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:21:46 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/29 22:05:08 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_TEST_HPP_
#define SET_TEST_HPP_

#include <set>

#include "set.hpp"

#include "utility/logger.hpp"
#include "utility/run_test.hpp"

bool fncomp(int lhs, int rhs) {
	return lhs < rhs;
}

struct classcomp {
	bool operator()(const int& lhs, const int& rhs) const {
		return lhs < rhs;
	}
};

namespace ft_test {
ft_test::Logger *st_log;

bool	test_set_constructor() {
	ft::set<int> first;
	if (first.size() != 0 || !first.empty())
		return st_log->err("1: size failed");

	int myints[]= {10, 20, 30, 40, 50};
	ft::set<int> second(myints, myints+5);        // range
	if (second.size() != 5 || second.empty())
		return st_log->err("2: size failed");

	ft::set<int> third(second);                  // a copy of second
	if (third.size() != 5 || third.empty())
		return st_log->err("3: size failed");

	std::cout << "test 4" << std::endl;
	ft::set<int> fourth(second.begin(), second.end());
	if (fourth.size() != 5 || fourth.empty()) {
		std::cout << fourth.size() << std::endl;
		return st_log->err("4: size failed");
	}

	ft::set<int, classcomp> fifth;
	if (fifth.size() != 0 || !fifth.empty())
		return st_log->err("5: size failed");

	bool(*fn_pt)(int, int) = fncomp;
	ft::set<int, bool(*)(int, int)> sixth(fn_pt);
	if (sixth.size() != 0 || !sixth.empty())
		return st_log->err("6: size failed");
	return true;
}

// bool	test_set_copy_constructor() {
// 	int myints[]= {10,20,30,40,50};
// 	ft::set<int> first (myints,myints+5);	// range
// 	ft::set<int> second (first);			// a copy of first

// 	if (first.size() != 5 || first.empty())
// 		return st_log->err("1: size failed");

// 	if (second.size() != 5 || second.empty())
// 		return st_log->err("2: size failed");

// 	ft::set<int>::iterator it = first.begin();
// 	for (; it != first.end(); ++it) {
// 		if (second.find(*it) == second.end())
// 			return st_log->err("3: find failed");
// 	}
// 	return true;
// }

// bool	test_set_assignement_operator() {
// 	int myints[]={ 12,82,37,64,15 };
// 	ft::set<int> first (myints,myints+5);		// set with 5 ints
// 	ft::set<int> second;						// empty set

// 	second = first;								// now second contains the 5 ints
// 	if (second.size() != 5 || second.empty())
// 		return st_log->err("1: size failed");

// 	first = std::set<int>();					// and first is empty
// 	if (first.size() != 0 || !first.empty())
// 		return st_log->err("2: size failed");
//
//  std::set<int>::iterator it = second.begin();
// 	for (; it != second.end(); ++it) {
// 		if (first.find(*it) == first.end())
// 			return st_log->err("3: find failed");
// 	}
// 	return true;
// }

// bool	test_set_destructor() {
// 	ft::set<int>	*first = new std::set<int>();

// 	first->insert(10);
// 	first->insert(20);
// 	first->insert(30);
// 	delete first;

// 	ft::set<int>	second;
// 	second.insert(10);
// 	second.insert(20);
// 	second.insert(30);

// 	return true;
// }

// bool	test_set_empty() {
// 	ft::set<int> first;

// 	if (!first.empty())
// 		return st_log->err("1: empty failed");

// 	first.insert(10);

// 	if (first.empty())
// 		return st_log->err("2: empty failed");

// 	first.erase(10);

// 	if (!first.empty())
// 		return st_log->err("3: empty failed");

// 	first.insert(20);
// 	first.insert(30);
// 	first.insert(40);

// 	if (first.empty())
// 		return st_log->err("4: empty failed");

// 	while (!first.empty())
// 		first.erase(first.begin());

// 	if (!first.empty())
// 		return st_log->err("5: empty failed");

// 	return true;
// }
// bool	test_set_size() {
// 	ft::set<int> first;

// 	if (first.size() != 0)
// 		return st_log->err("1: size failed");

// 	first.insert(10);
// 	if (first.size() != 1)
// 		return st_log->err("2: size failed");

// 	first.insert(20);
// 	if (first.size() != 2)
// 		return st_log->err("3: size failed");

// 	for (int i = 0; i < 10; ++i)
// 		first.insert(i);

// 	if (first.size() != 12)
// 		return st_log->err("4: size failed");

// 	first.erase(first.begin());
// 	if (first.size() != 11)
// 		return st_log->err("5: size failed");

// 	while (!first.empty())
// 		first.erase(first.begin());

// 	if (first.size() != 0)
// 		return st_log->err("6: size failed");
// 	return true;
// }
bool	test_set_max_size() {
	std::set<int> r;
	ft::set<int> c;

	if (r.max_size() != c.max_size())
		return st_log->err("1: max_size failed");
	return true;
}

void	set() {
	st_log = new ft_test::Logger("set ");

	st_log->section("CONSTRUCTORS");
	ft_test::run(st_log, test_set_constructor, "constructor");
	// ft_test::run(st_log, test_set_copy_constructor, "copy constructor");
	// ft_test::run(st_log, test_set_assignement_operator, "assignment operator");

	// st_log->section("DESTRUCTOR");
	// ft_test::run(st_log, test_set_destructor, "destructor");

	st_log->section("ITERATORS");
	// ft_test::run(st_log, "begin", test_set_begin);
	// ft_test::run(st_log, "end", test_set_end);
	// ft_test::run(st_log, "rbegin", test_set_rbegin);
	// ft_test::run(st_log, "rend", test_set_rend);
	// ft_test::run(st_log, "empty", test_set_empty);

	st_log->section("CAPACITY");
	// ft_test::run(st_log, test_set_empty, "empty");
	// ft_test::run(st_log, test_set_size, "size");
	// ft_test::run(st_log, test_set_max_size, "max_size");

	st_log->section("MODIFIERS");
	// ft_test::run(st_log, "insert", test_set_insert);
	// ft_test::run(st_log, "erase", test_set_erase);
	// ft_test::run(st_log, "swap", test_set_swap);
	// ft_test::run(st_log, "clear", test_set_clear);

	st_log->section("OBSERVERS");
	// ft_test::run(st_log, "key_comp", test_set_key_comp);
	// ft_test::run(st_log, "value_comp", test_set_value_comp);

	st_log->section("OPERATIONS");
	// ft_test::run(st_log, "find", test_set_find);
	// ft_test::run(st_log, "count", test_set_count);
	// ft_test::run(st_log, "lower_bound", test_set_lower_bound);
	// ft_test::run(st_log, "upper_bound", test_set_upper_bound);
	// ft_test::run(st_log, "equal_range", test_set_equal_range);

	st_log->section("ALLOCATORS");
	// ft_test::run(st_log, "allocator", test_set_allocator);

	#ifndef FT_BENCHMARK
	st_log->section("BENCHMARK");
	#endif
	delete st_log;
}

}  // namespace ft_test

#endif  // SET_TEST_HPP_
