/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:47:19 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/26 20:28:37 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Link:
	https://www.cplusplus.com/reference/stack/stack/
*/

#ifndef STACK_HPP_
#define STACK_HPP_

#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> > class stack {
 public:
	/*
		Member types
		https://www.cplusplus.com/reference/stack/stack/
	*/
	typedef T 			value_type;
	typedef Container 	container_type;

	typedef typename Container::size_type size_type;

 private:
	container_type _container;

 public:
	/*
		https://www.cplusplus.com/reference/stack/stack/stack/

		Constructs a stack container adaptor object.
	*/
	explicit stack(const container_type& ctnr = container_type())
		: _container(ctnr) {}

	stack(const stack &rhs) : _container(rhs._container) {}
	~stack() {}
	stack &operator=(const stack &rhs) {
		if (this != &rhs)
			_container = rhs._container;
		return *this;
	}

	/*
		https://www.cplusplus.com/reference/stack/stack/empty/

		Returns whether the stack is empty: i.e. whether its size is zero.
		This member function effectively calls member empty of the underlying container object.
	*/
	bool empty() const {
		return _container.empty();
	}

	/*
		https://www.cplusplus.com/reference/stack/stack/size/
	
		Returns the number of elements in the stack.
		This member function effectively calls member size of the underlying container object.
	*/
	size_type size() const {
		return _container.size();
	}

	/*
		https://www.cplusplus.com/reference/stack/stack/top/

		Returns a reference to the top element in the stack.
		Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
		This member function effectively calls member back of the underlying container object.
	*/

    value_type& top() {
		return _container.back();
	}
	const value_type& top() const {
		return _container.back();
	}

	/*
		https://www.cplusplus.com/reference/stack/stack/push/

		Inserts a new element at the top of the stack, above its current top element. The content of this new element is initialized to a copy of val.
		This member function effectively calls the member function push_back of the underlying container object.
	*/
	void push(const value_type& val) {
		_container.push_back(val);
	}

	/*
		https://www.cplusplus.com/reference/stack/stack/pop/

		Removes the element on top of the stack, effectively reducing its size by one.
		The element removed is the latest element inserted into the stack, whose value can be retrieved by calling member stack::top.
		This calls the removed element's destructor.
		This member function effectively calls the member function pop_back of the underlying container object.
	*/
	void pop() {
		_container.pop_back();
	}

	friend bool operator== (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs) {
		return lhs._container == rhs._container;
	}

	friend bool operator!= (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs) {
		return lhs._container != rhs._container;
	}

	friend bool operator<  (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs) {
		return lhs._container < rhs._container;
	}

	friend bool operator<= (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs) {
		return lhs._container <= rhs._container;
	}

	friend bool operator>  (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs) {
		return lhs._container > rhs._container;
	}

	friend bool operator>= (const stack<T, Container>& lhs,
		const stack<T, Container>& rhs) {
		return lhs._container >= rhs._container;
	}
};
}  // namespace ft

#endif  // STACK_HPP_
