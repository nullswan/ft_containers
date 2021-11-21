#ifndef VECTOR_TEST_HPP_
#define VECTOR_TEST_HPP_

#include <string>
#include <iostream>

#include "vector.hpp"
#include "utility/logger.hpp"

namespace ft_test {
class VectorTest {
	typedef	ft_test::Logger	Logger;

 private:
	Logger	log;

 public:
	VectorTest() : log("ft_vector") {
		test_constructor_default();
		log.success("constructor_default");

		test_constructor_alloc();
		log.success("constructor_alloc");
	}

	~VectorTest() {}

 private:
	void test_constructor_default() {
		ft::vector<int> v;
		ft::vector<bool> t;
		ft::vector<std::string> s;
	}

	void test_constructor_alloc() {
		ft::vector<int> *v = new ft::vector<int>();
		delete v;

		ft::vector<bool> *t = new ft::vector<bool>;
		delete t;
	}
};
}  // namespace ft_test

#endif  // VECTOR_TEST_HPP_
