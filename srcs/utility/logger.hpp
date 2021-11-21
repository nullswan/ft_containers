#ifndef UTILITY_LOGGER_HPP_
#define UTILITY_LOGGER_HPP_

#include <string>
#include <iostream>

namespace ft_test {
class Logger {
 private:
  std::string _prefix;

 public:
	explicit Logger(std::string const &prefix) : _prefix(prefix) {
		_announce();
	}

	void success(const char *test_name) {
		std::cout << "\033[1;42mPASSED\033[0m " << test_name << std::endl;
	}
	void error(const char *test_name) {
		std::cerr << "\033[1;41mFAILED\033[0m " << test_name << std::endl;
	}

 private:
	void	_announce() {
		int div_spaces = (22 - _prefix.size()) / 2;
		std::cout << "======================" << std::endl << "|";
		for (int i = 1; i < div_spaces; i++)
			std::cout << " ";
		std::cout << "\033[1;36m" << _prefix << "\033[0m";
		for (int i = 1; i < div_spaces; i++)
			std::cout << " ";
		std::cout << "|" << std::endl << "======================" << std::endl;
	}
};
}  // namespace ft_test

#endif  // UTILITY_LOGGER_HPP_
