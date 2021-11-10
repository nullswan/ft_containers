/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:47:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/10 17:40:41 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.cplusplus.com/reference/vector/vector/
#ifndef VECTOR_HPP_
#define VECTOR_HPP_

// For size_t
#include <stddef.h>

#include <memory>

#include "iterator/reverse_iterator.hpp"

namespace ft {
template <typename T, class Alloc = std::allocator<T> >
class vector {
 public:
	typedef T value_type;
	typedef Alloc allocator_type;

	// typedef ft::reverse_iterator<iterator> 			reverse_iterator;
	// typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

	typedef size_t 				size_type;
	typedef value_type* 		pointer;
	typedef const value_type*	const_pointer;

 private:
	allocator_type	_alloc;

	pointer	_data;

	size_type	_size;
	size_type	_capacity;

 public:
	// 		- [ CONSTRUCTORS ] -
	explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(0), _capacity(0) {}
	explicit vector(size_type n, const value_type& val = value_type(), \
		const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(n), _capacity(n) {
		reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(&_data[i], val);
	}
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, \
		const allocator_type& alloc = allocator_type());
	vector(const vector& x);

	//		- [ DESTRUCTOR ] -
	~vector() {
	}

	// 		- [ ASSIGNEMENT OPERATOR ] -
	vector& operator=(const vector& x);

	// 		- [ ITERATORS ] -
	// iterator 		begin() {
	// 	return iterator();
	// }
	// const_iterator 	begin() const {
	// 	return iterator();
	// }

	// iterator 		end() {
	// 	return iterator();
	// }
	// const_iterator 	end() const {
	// 	return iterator();
	// }

	// reverse_iterator 		rbegin() {
	// 	return reverse_iterator();
	// }
	// const_reverse_iterator 	rbegin() const {
	// 	return const_reverse_iterator();
	// }

	// reverse_iterator 		rend() {
	// 	return reverse_iterator();
	// }
	// const_reverse_iterator 	rend() const {
	// 	return const_reverse_iterator();
	// }

	// Capacity
	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

	void resize(size_type n, value_type val = value_type());

	size_type capacity() const {
		return _capacity;
	}

	bool empty() const {
		return _size == 0;
	}

	void reserve(size_type n);

	//		- [ ELEMENT ACCESS ] -
	// reference		operator[] (size_type n);
	// const_reference	operator[] (size_type n) const;

	// reference		at(size_type n);
	// const_reference	at(size_type n) const;

	// reference		front();
	// const_reference	front() const;

	// reference		back();
	// const_reference	back() const;

	//		- [ MODIFIERS ] -
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last);
	void assign(size_type n, const value_type& val);

	void push_back(const value_type& val);

	void pop_back();

	// iterator insert(iterator position, const value_type& val);
	// void insert(iterator position, size_type n, const value_type& val);
	// template <class InputIterator>
	// void insert(iterator position, InputIterator first, InputIterator last);

	// iterator erase(iterator position);
	// iterator erase(iterator first, iterator last);

	void swap(vector& x);

	/*  
		https://www.cplusplus.com/reference/vector/vector/clear/
		Removes all elements from the vector (which are destroyed), 
		leaving the container with a size of 0. 
	*/
	void clear() {
		for (size_type i = 0; i < _size; i++, _size--)
			_alloc.destroy(&_data[i]);
	}

	//		- [ ALLOCATOR ] -
	allocator_type get_allocator() const;

 private:
};
	//		- [ NON-MEMBER FUNCTION OVERLOADS ] -

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		(void)lhs;
		(void)rhs;
		return true;
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		(void)lhs;
		(void)rhs;
		return true;
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return ((lhs < rhs) || (lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		(void)lhs;
		(void)rhs;
		return true;
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return ((lhs > rhs) || (lhs == rhs));
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
		x.swap(y);
	}
};  // namespace ft

#endif  // VECTOR_HPP_
