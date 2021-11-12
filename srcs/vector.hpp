/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:47:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/10 19:12:09 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Link:
	https://www.cplusplus.com/reference/vector/vector/
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <stddef.h>  // Provide size_t

#include <string>
#include <memory>
#include <exception>

#include "utils/ft_itoa.hpp"

#include "algorithm/equal.hpp"
#include "algorithm/lexicographical_compare.hpp"

#include "iterator/reverse_iterator.hpp"
#include "iterator/random_access_iterator.hpp"

namespace ft {
template <typename T, class Alloc = std::allocator<T> >
class vector {
/*
	https://www.cplusplus.com/reference/vector/vector
	Member types
*/
 public:
	typedef T value_type;
	typedef Alloc allocator_type;

	/*
		https://stackoverflow.com/a/8246213
		typename keyword before MyTemplate<T>::Inner 
		because MyTemplate<T> is a dependent scope.
	*/
	typedef typename allocator_type::reference 		 reference;
	typedef typename allocator_type::const_reference const_reference;

	typedef typename allocator_type::pointer		pointer;
	typedef typename allocator_type::const_pointer	const_pointer;

	typedef ft::random_access_iterator<value_type> 			iterator;
	typedef ft::random_access_iterator<const value_type> 	const_iterator;

	typedef ft::reverse_iterator<iterator> 			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

	typedef ptrdiff_t	difference_type;
	typedef size_t 		size_type;

 private:
	allocator_type	_alloc;

	pointer	_data;

	size_type	_size;
	size_type	_capacity;

 public:
	// 		- [ CONSTRUCTORS ] -
	/* 
		https://www.cplusplus.com/reference/vector/vector/vector/

		(1) empty container constructor (default constructor)
		Constructs an empty container, with no elements. 
	*/
	explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(0), _capacity(0) {
		_data = NULL;
	}

	/*
		(2) fill constructor
    	Constructs a container with n elements. Each element is a copy of val.
	*/
	explicit vector(size_type n, const value_type& val = value_type(), \
		const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _size(n), _capacity(n) {
		_data = NULL;

		reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(&_data[i], val);
	}
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, \
	/*
		(4) copy constructor
    	Constructs a container with a copy of each of the elements in x, in the same order.
	*/
	vector(const vector& x)
		: _alloc(x._alloc), _size(x._size), _capacity(x._capacity) {
		_data = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; i++)
			_alloc.construct(&_data[i], x._data[i]);
	}

	//		- [ DESTRUCTOR ] -
	~vector() {
		clear();
		_alloc.deallocate(_data, _capacity);
	}

	// 		- [ ASSIGNEMENT OPERATOR ] -
	vector& operator=(const vector& x);

	// 		- [ ITERATORS ] -
	/*
		https://www.cplusplus.com/reference/vector/vector/begin/

		Returns an iterator pointing to the first element in the vector.
		Notice that, unlike member vector::front, which returns a reference to the first element, this function returns a random access iterator pointing to it.
	*/
	iterator 		begin() {
		return iterator(_data);
	}
	const_iterator 	begin() const {
		return const_iterator(_data);
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/end/

		Returns an iterator referring to the past-the-end element in the vector container.
		The past-the-end element is the theoretical element that would follow the last element in the vector. It does not point to any element, and thus shall not be dereferenced.
		If the container is empty, this function returns the same as vector::begin.
	*/
	iterator 		end() {
		return iterator(_data + _size);
	}
	const_iterator 	end() const {
		return const_iterator(_data + _size);
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/rbegin/

		Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
		Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
		rbegin points to the element right before the one that would be pointed to by member end.
	*/
	reverse_iterator 		rbegin() {
		return reverse_iterator(_data + _size);
	}
	const_reverse_iterator 	rbegin() const {
		return const_reverse_iterator(_data + _size);
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/rend/

		Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (which is considered its reverse end).
		The range between vector::rbegin and vector::rend contains all the elements of the vector (in reverse order).
	*/
	reverse_iterator 		rend() {
		return reverse_iterator(_data);
	}
	const_reverse_iterator 	rend() const {
		return const_reverse_iterator(_data);
	}

	//		- [ CAPACITY ] -
	/*
		https://www.cplusplus.com/reference/vector/vector/size/

		Returns the number of elements in the vector.
		This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
	*/
	size_type size() const {
		return _size;
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/max_size/

		Returns the maximum number of elements that the vector can hold.
		This is the maximum potential size the container can reach due to known system or library implementation limitations, but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at any point before that size is reached.
	*/
	size_type max_size() const {
		return _alloc.max_size();
	}

	void resize(size_type n, value_type val = value_type());

	/*
		https://www.cplusplus.com/reference/vector/vector/capacity/

		Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
	*/
	size_type capacity() const {
		return _capacity;
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/empty/

		Returns whether the vector is empty (i.e. whether its size is 0).
	*/
	bool empty() const {
		return _size == 0;
	}

	void reserve(size_type n);

	//		- [ ELEMENT ACCESS ] -
	reference		operator[] (size_type n) {
		return _data[n];
	}
	const_reference	operator[] (size_type n) const {
		return _data[n];
	}

	reference		at(size_type n) {
		__range_check(n);
		return _data[n];
	}
	const_reference	at(size_type n) const {
		__range_check(n);
		return _data[n];
	}

	reference		front() {
		return _data[0];
	}
	const_reference	front() const {
		return _data[0];
	}

	reference		back() {
		return _data[_size - 1];
	}
	const_reference	back() const {
		return _data[_size - 1];
	}

	//		- [ MODIFIERS ] -
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last);
	void assign(size_type n, const value_type& val);

	void push_back(const value_type& val);

	void pop_back();

	iterator insert(iterator position, const value_type& val);
	void insert(iterator position, size_type n, const value_type& val);
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last);

	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);

	void swap(vector& x);

	/*  
		https://www.cplusplus.com/reference/vector/vector/clear/

		Removes all elements from the vector (which are destroyed), 
		leaving the container with a size of 0. 
	*/
	void clear() {
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(&_data[i]);
		_size = 0;
	}

	//		- [ ALLOCATOR ] -
	/*
		https://www.cplusplus.com/reference/vector/vector/get_allocator/

		Returns a copy of the allocator object associated with the vector.
	*/
	allocator_type get_allocator() const {
		return _alloc;
	}

 private:
	void	__range_check(size_type n) {
		if (n >= _size)
			throw std::out_of_range(
				std::string("ft::vector::__range_check: ") + \
				std::string("n (which is ") + ft_itoa(n) + \
				std::string(") >= this->size() (which is ") + \
				ft_itoa(_size) + std::string(")"));
	}
};
	//		- [ NON-MEMBER FUNCTION OVERLOADS ] -
	/*
		https://www.cplusplus.com/reference/vector/vector/operators/

		The equality comparison (operator==) is performed by first comparing sizes, and if they match, the elements are compared sequentially using operator==, stopping at the first mismatch (as if using algorithm equal).
		The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare, which compares the elements sequentially using operator< in a reciprocal manner (i.e., checking both a<b and b<a) and stopping at the first occurrence.
		The other operations also use the operators == and < internally to compare the elements, behaving as if the following equivalent operations were performed:
		
		operation	equivalent operation
		a!=b		!(a==b)
		a>b			b<a
		a<=b		!(b<a)
		a>=b		!(a<b)
	*/
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return ft::lexicographical_compare(
			lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/swap-free/

		The contents of container x are exchanged with those of y. Both container objects must be of the same type (same template parameters), although sizes may differ.
		After the call to this member function, the elements in x are those which were in y before the call, and the elements of y are those which were in x. All iterators, references and pointers remain valid for the swapped objects.
	*/
	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
		x.swap(y);
	}
};  // namespace ft

#endif  // VECTOR_HPP_
