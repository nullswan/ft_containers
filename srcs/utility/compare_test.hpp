#ifndef UTILITY_COMPARE_TEST_HPP_
#define UTILITY_COMPARE_TEST_HPP_

namespace ft_test {
bool fncomp(int lhs, int rhs) {
	return lhs < rhs;
}

struct classcomp {
	bool operator()(const int& lhs, const int& rhs) const {
		return lhs < rhs;
	}
};
}  // namespace ft_test

#endif  // UTILITY_COMPARE_TEST_HPP_
