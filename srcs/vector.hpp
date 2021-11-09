/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:47:01 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/11/09 23:10:43 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

namespace ft {
class vector {
 public:
	// 		- [ CONSTRUCTORS ] -
	// explicit vector(const allocator_type& alloc = allocator_type());
	// explicit vector(size_type n, const value_type& val = value_type(), \
	// 	const allocator_type& alloc = allocator_type());
	// template <class InputIterator>
	// vector(InputIterator first, InputIterator last, \
	// 	const allocator_type& alloc = allocator_type());
	vector(const vector& x);

	//		- [ DESTRUCTOR ] -
	~vector();

	// 		- [ ASSIGNEMENT OPERATOR ] -
	vector& operator=(const vector& x);

	// 		- [ ITERATORS ] -
	// iterator 		begin();
	// const_iterator 	begin() const;

	// iterator 		end();
	// const_iterator 	end() const;

	// reverse_iterator 		rbegin();
	// const_reverse_iterator 	rbegin() const;

	// reverse_iterator 		rend();
	// const_reverse_iterator 	rend() const;

	// Capacity
	// size_type size() const;

	// size_type max_size() const;

	// void resize(size_type n, value_type val = value_type());

	// size_type capacity() const;

	bool empty() const;

	// void reserve(size_type n);

	//		- [ ELEMENT ACCESS ] -

	//		- [ MODIFIERS ] -

	//		- [ ALLOCATOR ] -

	//		- [ NON-MEMBER FUNCTION OVERLOADS ] -

 private:
};
};  // namespace ft

#endif  // VECTOR_HPP_
