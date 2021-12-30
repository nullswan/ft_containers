/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:47:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/28 18:05:26 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Link:
	https://www.cplusplus.com/reference/vector/vector/
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <stddef.h>		// Provide size_t

#include <string>
#include <memory>		// provides std::allocator
#include <exception>

#include "utility/ft_itoa.hpp"
#include "types/type_trait.hpp"

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
		: _alloc(alloc), _data(0), _size(0), _capacity(0) {}

	/*
		(2) fill constructor
    	Constructs a container with n elements. Each element is a copy of val.
	*/
	explicit vector(size_type n, const value_type& val = value_type(), \
		const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _data(0), _size(0), _capacity(0) {
		reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(_data + i, val);
		_size = n;
	}

	/*
		(3) range constructor
    	Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
	*/
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, \
		const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			InputIterator>::type* = NULL)
		: _alloc(alloc), _data(0), _size(0), _capacity(0) {
		size_type n = last - first;

		reserve(n);
		for (size_type i = 0; i < n; i++)
			_alloc.construct(_data + i, *(first + i));
		_size = n;
	}

	/*
		(4) copy constructor
    	Constructs a container with a copy of each of the elements in x, in the same order.
	*/
	vector(const vector& x)
		: _alloc(x._alloc), _size(x._size), _capacity(x._capacity) {
		_data = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; i++)
			_alloc.construct(_data + i, x._data[i]);
	}

	//		- [ DESTRUCTOR ] -
	/*
		https://www.cplusplus.com/reference/vector/vector/~vector/

		This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
	*/
	~vector() {
		clear();  // Apparently not cleared in original stl container
		_alloc.deallocate(_data, _capacity);
	}

	// 		- [ ASSIGNEMENT OPERATOR ] -
	/*
		https://www.cplusplus.com/reference/vector/vector/operator=/

		Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
		- C++98:
			Copies all the elements from x into the container.
			* Using: https://en.cppreference.com/w/cpp/memory/allocator/construct
			The container preserves its current allocator, which is used to allocate storage in case of reallocation.
	*/
	vector& operator=(const vector& x) {
		if (this != &x) {
			clear();
			if (_capacity < x._size)
				reserve(x._size);
			_size = x._size;
			if (_data)
				_alloc.deallocate(_data, _size);
			if (x._data) {
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_data + i, x._data[i]);
			} else {
				_data = NULL;
			}
		}
		return *this;
	}

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

	/*
		https://www.cplusplus.com/reference/vector/vector/resize/

		Resizes the container so that it contains n elements.
		If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
		If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
		If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
	*/

	void resize(size_type n, value_type val = value_type()) {
		if (n < _size) {
			for (size_type i = n; i < _size; i++)
				_alloc.destroy(_data + i);
			_size = n;
		} else if (n > _size) {
			/* We must allocate here even though it comes after in reference */
			if (n > _capacity * 2)
				reserve(n);
			else
				reserve(__new_size());
			for (size_type i = _size; i < n; i++)
				_alloc.construct(_data + i, val);
			_size = n;
		}
	}

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

	/*
		https://www.cplusplus.com/reference/vector/vector/reserve/
		Requests that the vector capacity be at least enough to contain n elements.
		If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
		In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
		
	*/

	void reserve(size_type n) {
		if (n > _alloc.max_size())
			throw std::length_error("vector::reserve::bad_alloc");
		if (n > _capacity) {
			pointer tmp = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(tmp + i, _data[i]);
				_alloc.destroy(_data + i);
			}

			_alloc.deallocate(_data, _capacity);
			_data = tmp;
			_capacity = n;
		}
	}

	//		- [ ELEMENT ACCESS ] -
	/*
		https://www.cplusplus.com/reference/vector/vector/operator[]/

		Returns a reference to the element at position n in the vector container.
	*/
	reference		operator[] (size_type n) {
		return _data[n];
	}
	const_reference	operator[] (size_type n) const {
		return _data[n];
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/at/

		Returns a reference to the element at position n in the vector.

		The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
	*/
	reference		at(size_type n) {
		__range_check(n);
		return _data[n];
	}
	const_reference	at(size_type n) const {
		__range_check(n);
		return _data[n];
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/front/

		Returns a reference to the first element in the vector.
	*/
	reference		front() {
		return _data[0];
	}
	const_reference	front() const {
		return _data[0];
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/back/

		Returns a reference to the last element in the vector.
	*/
	reference		back() {
		return _data[_size - 1];
	}
	const_reference	back() const {
		return _data[_size - 1];
	}

	//		- [ MODIFIERS ] -
	/*
		https://www.cplusplus.com/reference/vector/vector/assign/

		Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		In the range version (1), the new contents are elements constructed from each of the elements in the range between first and last, in the same order.
		In the fill version (2), the new contents are n elements, each initialized to a copy of val.
	*/

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last, \
		typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			InputIterator>::type* = NULL) {
		size_type n = last - first;

		if (n > _capacity)
			reserve(n);
		for (size_type i = 0; i < n; i++, first++) {
			_alloc.destroy(_data + i);
			_alloc.construct(_data + i, *first);
		}
		_size = n;
	}
	void assign(size_type n, const value_type& val) {
		if (n > _capacity)
			reserve(n);
		for (size_type i = 0; i < n; i++) {
			_alloc.destroy(_data + i);
			_alloc.construct(_data + i, val);
		}
		_size = n;
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/push_back/

		Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
		This effectively increases the container size by one, which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
	*/
	void push_back(const value_type& val) {
		if (_size == _capacity)
			reserve(__new_size());
		_alloc.construct(_data + _size++, val);
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/pop_back/

		Removes the last element in the vector, effectively reducing the container size by one.
		This destroys the removed element.
	*/
	void pop_back() {
		_alloc.destroy(_data + --_size);
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/insert/

		The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
		This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
	*/

	iterator insert(iterator position, const value_type& val) {
		size_type elem_pos = position - begin();

		if (_size + 1 > _capacity)
			reserve(__new_size());
		__translate_asc(elem_pos, 1);
		_alloc.construct(_data + elem_pos, val);
		++_size;
		return iterator(_data);
	}

	void insert(iterator position, size_type n, const value_type &val) {
		size_type elem_pos = position - begin();

		if (_size + n > _capacity)
			reserve(_capacity + n);
		__translate_asc(elem_pos, n);

		for (size_type i = 0; i < n; i++)
			_alloc.construct(&_data[elem_pos + i], val);
		_size += n;
	}

	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			InputIterator>::type* = NULL) {
		size_type elem_pos = position - begin();
		size_type n = last - first;
		if (_size + n > _capacity) {
			if (__new_size() < _size + n)
				reserve(__new_size());
			else
				reserve(_size + n);
		}

		__translate_asc(elem_pos, n);
		for (size_type i = 0; i < n; i++, first++)
			_alloc.construct(&_data[elem_pos + i], *first);
		_size += n;
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/erase/

		Removes from the vector either a single element (position) or a range of elements ([first,last)).
		This effectively reduces the container size by the number of elements removed, which are destroyed.
	*/
	iterator erase(iterator position) {
		size_type	n = position - begin();

		_alloc.destroy(_data + n);
		__translate_dsc(n, 1);
		--_size;
		return iterator(_data + n);
	}
	iterator erase(iterator first, iterator last) {
		size_type	diff = last - first;
		size_type	n = first - begin();
		size_type	i = last - begin();

		__destroy_range(first, last);
		__translate_dsc(n, i - n);
		_size -= diff;
		return (iterator(_data + n));
	}

	/*
		https://www.cplusplus.com/reference/vector/vector/swap/

		Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
		After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
	*/
	void swap(vector& x) {
		std::swap(_data, x._data);
		std::swap(_size, x._size);
		std::swap(_capacity, x._capacity);
		/* Unsure about _alloc but we must probably swap every variables */
		std::swap(_alloc, x._alloc);
	}

	/*  
		https://www.cplusplus.com/reference/vector/vector/clear/

		Removes all elements from the vector (which are destroyed), 
		leaving the container with a size of 0. 
	*/
	void clear() {
		if (_data) {
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
		}
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

	size_type	__new_size() {
		return _size == 0 ? 1 : _size * 2;
	}

	void	__destroy_range(iterator first, iterator last) {
		while (*first != *last) {
			_alloc.destroy(&(*first));
			++first;
		}
	}

	void	__translate_dsc(size_type elem_pos, size_type n) {
		for (; elem_pos < _size; elem_pos++) {
			_alloc.construct(_data + elem_pos, _data[elem_pos + n]);
			_alloc.destroy(_data + elem_pos + n);
		}
	}

	void	__translate_asc(size_type elem_pos, size_type n) {
		for (size_type i = _size - 1; i >= elem_pos; i--) {
			_alloc.construct(_data + i + n, _data[i]);
			_alloc.destroy(_data + i);
			if (i == 0)
				break;
		}
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
	bool operator==	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return ft::lexicographical_compare(
			lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
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
