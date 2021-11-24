#ifndef VECTOR_TEST_HPP_
#define VECTOR_TEST_HPP_

#include <string>
#include <vector>
#include <iostream>

#include "vector.hpp"
#include "utility/logger.hpp"
#include "utility/run_test.hpp"

namespace ft_test {
ft_test::Logger *v_log = new ft_test::Logger("vector");

bool	test_empty_constructor() {
	ft::vector<int>		i;
	std::vector<int>	i_og;

	if (i.size() != 0 || i.capacity() != 0)
		return false;
	if (i_og.size() != i.size() || i_og.capacity() != i.capacity())
		return v_log->err("size differs from original container");

	ft::vector<bool> 	b;
	std::vector<bool> 	b_og;

	if (b.size() != 0 || b.capacity() != 0)
		return false;
	if (b_og.size() != b.size() || b_og.capacity() != b.capacity())
		return v_log->err("size differs from original container");
	return true;
}
bool	test_fill_constructor() {
	ft::vector<int> i(10);
	std::vector<int> i_og(10);
	if (i.size() != i_og.size() || i.capacity() != i_og.capacity())
		return v_log->err("size differs from original container");

	ft::vector<int> i1(10, 42);
	std::vector<int> i1_og(10, 42);
	if (i1.size() != i1_og.size() || i1.capacity() != i1_og.capacity())
		return v_log->err("size differs from original container");
	for (size_t i = 0; i < i1.size(); i++)
		if (i1[i] != i1_og[i])
			return v_log->err("content differs from original container");

	ft::vector<int> i2(112, 42);
	std::vector<int> i2_og(112, 42);
	if (i2.size() != i2_og.size() || i2.capacity() != i2_og.capacity())
		return v_log->err("size differs from original container");
	for (size_t i = 0; i < i2.size(); i++)
		if (i2[i] != i2_og[i])
			return v_log->err("content differs from original container");
	return true;
}
bool	test_range_constructor() {
	ft::vector<int> ref(10, 42);
	std::vector<int> ref_og(10, 42);

	ft::vector<int> v(ref.begin(), ref.end());
	std::vector<int> v_og(ref_og.begin(), ref_og.end());
	if (v.size() != v_og.size() || v.capacity() != v_og.capacity())
		return v_log->err("size differs from original container");
	for (size_t i = 0; i < v.size(); i++)
		if (v[i] != v_og[i])
			return v_log->err("content differs from original container");
	return true;
}
bool	test_copy_constructor() {
	ft::vector<int> ref(10, 42);
	std::vector<int> ref_og(10, 42);

	ft::vector<int> v(ref);
	std::vector<int> v_og(ref_og);

	if (v.size() != v_og.size() || v.size() != ref.size()
		|| v.capacity() != v_og.capacity() || v.capacity() != ref.capacity())
		return v_log->err("size differs from original container");
	for (size_t i = 0; i < v.size(); i++)
		if (v[i] != v_og[i])
			return v_log->err("content differs from original container");
	return true;
}

bool	test_destructor() {
	ft::vector<int> *v = new ft::vector<int>(100, 42);

	delete v;
	return true;
}

bool	test_assignement_operator() {
	ft::vector<int> ref(10, 42);
	std::vector<int> ref_og(10, 42);

	ft::vector<int> v = ref;
	std::vector<int> v_og = ref_og;

	if (v.size() != v_og.size() || v.capacity() != v_og.capacity())
		return v_log->err("size differs from original container");

	for (size_t i = 0; i < v.size(); i++)
		if (v[i] != v_og[i])
			return v_log->err("content differs from original container");
	return true;
}

bool	test_allocator() {
	ft::vector<int> v;
	int	*p = 0;
	unsigned int i = 0;

	p = v.get_allocator().allocate(5);
	for (i = 0; i < 5; i++)
		v.get_allocator().construct(&p[i], i);
	for (i = 0; i < 5; i++)
		if (p[i] != static_cast<int>(i))
			return v_log->err("allocator failed");
	for (i = 0; i < 5; i++)
		v.get_allocator().destroy(&p[i]);
  	v.get_allocator().deallocate(p, 5);
	return true;
}

bool	benchmark_constructor() {
	time_t start = clock();
	ft::vector<int> *v = new ft::vector<int>(1000000, 42);
	time_t end = clock();
	delete v;

	time_t start_og = clock();
	std::vector<int> *v_og = new std::vector<int>(1000000, 42);
	time_t end_og = clock();
	delete v_og;

	return v_log->benchmark(end - start, end_og - start_og);
}
bool	benchmark_destructor() {
	ft::vector<int> *v = new ft::vector<int>(1000000, 42);
	time_t start = clock();
	delete v;
	time_t end = clock();

	std::vector<int> *v_og = new std::vector<int>(1000000, 42);
	time_t start_og = clock();
	delete v_og;
	time_t end_og = clock();

	return v_log->benchmark(end - start, end_og - start_og);
}
bool	benchmark_assignement_operator() {
	ft::vector<int> *v = new ft::vector<int>(1000000, 42);
	std::vector<int> *v_og = new std::vector<int>(1000000, 42);

	time_t start = clock();
	ft::vector<int> *v2 = new ft::vector<int>(*v);
	time_t end = clock();

	time_t start_og = clock();
	std::vector<int> *v2_og = new std::vector<int>(*v_og);
	time_t end_og = clock();


	delete v;
	delete v_og;

	for (size_t i = 0; i < v2->size(); i++)
		if (v2->at(i) != v2_og->at(i))
			return v_log->err("content differs from original container");
	delete v2;
	delete v2_og;
	return v_log->benchmark(end - start, end_og - start_og);
}

void	vector() {
	v_log->section("CONSTRUCTORS");
	ft_test::run(v_log, &test_empty_constructor, "Empty Constructor");
	ft_test::run(v_log, &test_fill_constructor, "Fill Constructor");
	ft_test::run(v_log, &test_range_constructor, "Range Constructor");
	ft_test::run(v_log, &test_copy_constructor, "Copy Constructor");

	v_log->section("DESTRUCTOR");
	ft_test::run(v_log, &test_destructor, "Destructor");

	v_log->section("ASSIGNEMENT OPERATOR");
	ft_test::run(v_log, &test_assignement_operator, "Assignement Operator");


	v_log->section("ITERATORS");


	v_log->section("ELEMENT ACCESS");


	v_log->section("MODIFIERS");


	v_log->section("ALLOCATOR");
	ft_test::run(v_log, &test_allocator, "Allocator");

	v_log->section("NON-MEMBER FUNCTION OVERLOADS");


	v_log->section("BENCHMARKS");
	ft_test::run(v_log, &benchmark_constructor, "Benchmark Constructor");
	ft_test::run(v_log, &benchmark_destructor, "Benchmark Destructor");
	ft_test::run(v_log, &benchmark_assignement_operator, "Benchmark Assignement Operator");

	delete v_log;
}
}  // namespace ft_test

#endif  // VECTOR_TEST_HPP_
