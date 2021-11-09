/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:47:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/09 23:38:05 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.cplusplus.com/reference/vector/vector/
#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <memory>

#include "reverse_iterator.hpp"

namespace ft {
template <typename T, class Alloc = std::allocator<T> >
class vector {
 public:
	typedef T value_type;
	typedef Alloc allocator_type;

	typedef ft::reverse_iterator<iterator> 			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

	typedef size_t 			size_type;

 public:
	// 		- [ CONSTRUCTORS ] -
	explicit vector(const allocator_type& alloc = allocator_type());
	explicit vector(size_type n, const value_type& val = value_type(), \
		const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, \
		const allocator_type& alloc = allocator_type());
	vector(const vector& x);

	//		- [ DESTRUCTOR ] -
	~vector();

	// 		- [ ASSIGNEMENT OPERATOR ] -
	vector& operator=(const vector& x);

	// 		- [ ITERATORS ] -
	iterator 		begin();
	const_iterator 	begin() const;

	iterator 		end();
	const_iterator 	end() const;

	reverse_iterator 		rbegin();
	const_reverse_iterator 	rbegin() const;

	reverse_iterator 		rend();
	const_reverse_iterator 	rend() const;

	// Capacity
	size_type size() const;

	size_type max_size() const;

	void resize(size_type n, value_type val = value_type());

	size_type capacity() const;

	bool empty() const;

	void reserve(size_type n);

	//		- [ ELEMENT ACCESS ] -
	reference		operator[] (size_type n);
	const_reference	operator[] (size_type n) const;

	reference		at(size_type n);
	const_reference	at(size_type n) const;

	reference		front();
	const_reference	front() const;

	reference		back();
	const_reference	back() const;

	//		- [ MODIFIERS ] -

	//		- [ ALLOCATOR ] -
	allocator_type get_allocator() const;

	//		- [ NON-MEMBER FUNCTION OVERLOADS ] -
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y);

 private:
};
};  // namespace ft

#endif  // VECTOR_HPP_
