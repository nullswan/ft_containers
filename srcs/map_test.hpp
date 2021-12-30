#ifndef MAP_TEST_HPP_
#define MAP_TEST_HPP_

#include <map>

#include "map.hpp"

#include "utility/logger.hpp"
#include "utility/run_test.hpp"
#include "utility/compare_test.hpp"

namespace ft_test {

ft_test::Logger *m_log;

bool	test_map_default_constructor() {
	ft::map<int, char> intcharmap;
	ft::map<char, int> charintmap;

	ft::map<bool, bool> boolboolmap;

	ft::map<char, int, classcomp> fourth;  // class as Compare

	bool(*fn_pt)(int, int) = fncomp;
	ft::map<char, int, bool(*)(int, int)>
		fifth(fn_pt);  // function pointer as Compare
	return true;
}
bool	test_map_range_constructor() {
	ft::map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	ft::map<char, int> second(first.begin(), first.end());
	if (second.size() != 4 || second.empty())
		return false;

	ft::map<char, int> third(second.begin(), second.end());
	if (third.size() != 4 || third.empty())
		return m_log->err("1: range constructor failed");

	if (third.find('a')->second != 10)
		return m_log->err("2: range constructor failed");

	if (third.find('b')->second != 30)
		return m_log->err("3: range constructor failed");

	if (third.find('c')->second != 50)
		return m_log->err("4: range constructor failed");

	if (third.find('d')->second != 70)
		return m_log->err("5: range constructor failed");

	if (third['d'] != 70)
		return m_log->err("6: range constructor failed");
	return true;
}
bool	test_map_copy_constructor() {
	return true;
}

bool	test_map_destructor() {
	return true;
}

bool	test_map_assignement_operator() {
	return true;
}

bool	test_map_begin() {
	return true;
}
bool	test_map_end() {
	return true;
}
bool	test_map_rbegin() {
	return true;
}
bool	test_map_rend() {
	return true;
}

bool	test_map_empty() {
	return true;
}
bool	test_map_size() {
	return true;
}
bool	test_map_max_size() {
	return true;
}

bool	test_map_operator_access() {
	return true;
}
bool	test_map_at() {
	return true;
}

bool	test_map_insert() {
	return true;
}
bool	test_map_erase() {
	return true;
}
bool	test_map_swap() {
	return true;
}
bool	test_map_clear() {
	return true;
}

bool	test_map_key_comp() {
	return true;
}
bool	test_map_value_comp() {
	return true;
}

bool	test_map_find() {
	return true;
}
bool	test_map_count() {
	return true;
}
bool	test_map_lower_bound() {
	return true;
}
bool	test_map_upper_bound() {
	return true;
}
bool	test_map_equal_range() {
	return true;
}

bool	test_map_allocator() {
	return true;
}

void	map() {
	m_log = new ft_test::Logger("map ");

	m_log->section("CONSTRUCTORS");
	ft_test::run(m_log, test_map_default_constructor, "default constructor");
	ft_test::run(m_log, test_map_range_constructor, "range constructor");
	ft_test::run(m_log, test_map_copy_constructor, "copy constructor");

	m_log->section("DESTRUCTORS");
	ft_test::run(m_log, test_map_destructor, "destructor");

	m_log->section("ASSIGNEMENT OPERATOR");
	ft_test::run(m_log, test_map_assignement_operator, "operator=");

	m_log->section("ITERATORS");
	ft_test::run(m_log, test_map_begin, "begin");
	ft_test::run(m_log, test_map_end, "end");
	ft_test::run(m_log, test_map_rbegin, "rbegin");
	ft_test::run(m_log, test_map_rend, "rend");

	m_log->section("CAPACITY");
	ft_test::run(m_log, test_map_empty, "empty");
	ft_test::run(m_log, test_map_size, "size");
	ft_test::run(m_log, test_map_max_size, "max_size");

	m_log->section("ELEMENTS ACCESS");
	ft_test::run(m_log, test_map_operator_access, "operator[]");
	ft_test::run(m_log, test_map_at, "at");

	m_log->section("MODIFIERS");
	ft_test::run(m_log, test_map_insert, "insert");
	ft_test::run(m_log, test_map_erase, "erase");
	ft_test::run(m_log, test_map_swap, "swap");
	ft_test::run(m_log, test_map_clear, "clear");

	m_log->section("OBSERVERS");
	ft_test::run(m_log, test_map_key_comp, "key_comp");
	ft_test::run(m_log, test_map_value_comp, "value_comp");

	m_log->section("OPERATIONS");
	ft_test::run(m_log, test_map_find, "find");
	ft_test::run(m_log, test_map_count, "count");
	ft_test::run(m_log, test_map_lower_bound, "lower_bound");
	ft_test::run(m_log, test_map_upper_bound, "upper_bound");
	ft_test::run(m_log, test_map_equal_range, "equal_range");

	m_log->section("ALLOCATOR");
	ft_test::run(m_log, test_map_allocator, "allocator");

	#ifdef FT_BENCHMARK
	m_log->section("BENCHMARK");
	#endif
	delete m_log;
}

}  // namespace ft_test

#endif  // MAP_TEST_HPP_
