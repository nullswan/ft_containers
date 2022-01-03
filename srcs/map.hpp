/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:50:07 by c3b5aw            #+#    #+#             */
/*   Updated: 2022/01/03 19:20:26 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP_
#define MAP_HPP_

/*
	Link:
	https://www.cplusplus.com/reference/map/map/
*/

#include <memory>		// provides std::allocator
#include <functional>   // provides std::less

#include "utility/pair.hpp"

#include "algorithm/equal.hpp"
#include "algorithm/lexicographical_compare.hpp"

#include "tree/rb_tree.hpp"

namespace ft {
template <
	class Key,  // map::key_type
	class T,    // map::mapped_type
	class Compare = std::less<Key>,  // map::key_compare
	class Alloc = std::allocator<ft::pair<Key, T> >  // map::allocator_type
>
class map {
 public:
	typedef Key		key_type;
	typedef T		mapped_type;

	typedef Compare	key_compare;
	typedef Alloc	allocator_type;
	typedef ft::pair<key_type, mapped_type>	value_type;

	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

class value_compare {
	public:
	bool operator()(const value_type &a, const value_type &b) const {
		return (key_compare()(a.first, b.first));
	}

	value_compare &operator=(const value_compare &) {
		return *this;
	}
};

	typedef typename ft::rb_tree<value_type, value_compare>::iterator iterator;
	typedef typename ft::rb_tree
		<value_type, value_compare>::const_iterator const_iterator;
	typedef typename ft::rb_tree
		<value_type, value_compare>::reverse_iterator reverse_iterator;
	typedef typename ft::rb_tree
		<value_type, value_compare>::const_reverse_iterator const_reverse_iterator;

	typedef std::ptrdiff_t	difference_type;
	typedef std::size_t		size_type;

 private:
	allocator_type	_alloc;
	key_compare		_key_compare;
	value_compare	_value_compare;

	rb_tree<value_type, value_compare>	_tree;

 public:
	/*
			- [ CONSTRUCTORS ] -
		https://www.cplusplus.com/reference/map/map/map/

		(1) empty container constructor (default constructor)
    	Constructs an empty container, with no elements.
	*/
	explicit map(const key_compare &comp = key_compare(),
		const allocator_type &alloc = allocator_type())
	:	_alloc(alloc),
		_key_compare(comp),
		_value_compare(value_compare()),
		_tree(_alloc) {}

	/* 
		(2) range constructor
    	Constructs a container with as many elements as the range [first,last), 
		with each element constructed from its corresponding element in that range.
	*/
	template <class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<
			!ft::is_integral<InputIterator>::value
		>::type * = NULL)
	:	_alloc(alloc),
		_key_compare(comp),
		_value_compare(value_compare()),
		_tree(_alloc) {
		insert(first, last);
	}

	/*
		(3) copy constructor
    	Constructs a container with a copy of each of the elements in x.
	*/
	map(const map &x)
	:	_alloc(x._alloc),
		_key_compare(x._key_compare),
		_value_compare(x._value_compare),
		_tree(x._tree) {}

	/*
		- [ DESTRUCTOR ] -
		https://www.cplusplus.com/reference/map/map/~map/

		Destroys the container object.
	*/
	~map() {}

	/*
		- [ ASSIGNEMENT OPERATOR ] -
		https://www.cplusplus.com/reference/map/map/operator=/
		
		Assigns new contents to the container, replacing its current content.
	*/
	map &operator=(const map &x) {
		if (this != &x) {
			_alloc = x._alloc;
			_key_compare = x._key_compare;
			_value_compare = x._value_compare;
			_tree = x._tree;
		}
		return *this;
	}

	/*
		- [ ITERATORS ] -

		https://www.cplusplus.com/reference/map/map/begin/

		Return iterator to beginning
		Returns an iterator referring to the first element in the map container.
	*/
	iterator begin() {
		return _tree.begin();
	}
	const_iterator begin() const {
		return _tree.begin();
	}

	/*
		https://www.cplusplus.com/reference/map/map/end/

		Return iterator to end
		Returns an iterator referring to the past-the-end element in the map container.

		The past-the-end element is the theoretical element that would follow the last element in the map container. It does not point to any element, and thus shall not be dereferenced.
	*/
	iterator end() {
		return _tree.end();
	}
	const_iterator end() const {
		return _tree.end();
	}

	/*
		https://www.cplusplus.com/reference/map/map/rbegin/

		Return reverse iterator to reverse beginning
		Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
	*/
	reverse_iterator rbegin() {
		return _tree.rbegin();
	}
	const_reverse_iterator rbegin() const {
		return _tree.rbegin();
	}

	/*
		https://www.cplusplus.com/reference/map/map/rend/

		Return reverse iterator to reverse end
		Returns a reverse iterator pointing to the theoretical element right before the first element in the map container (which is considered its reverse end).
	*/
	reverse_iterator rend() {
		return _tree.rend();
	}
	const_reverse_iterator rend() const {
		return _tree.rend();
	}

	/*
		- [ SIZE ] -

		https://www.cplusplus.com/reference/map/map/empty/
	
		Test whether container is empty
		Returns whether the map container is empty (i.e. whether its size is 0).
	*/
	bool	empty() const {
		return _tree.empty();
	}

	/*
		https://www.cplusplus.com/reference/map/map/size/

		Return container size
		Returns the number of elements in the map container.
	*/
	size_type size() const {
		return _tree.size();
	}

	/*
		https://www.cplusplus.com/reference/map/map/max_size/

		Return maximum size
		Returns the maximum number of elements that the map container can hold.
	*/
	size_type max_size() const {
		return _tree.max_size();
	}

	/*
		- [ ELEMENT ACCESS ] -

		https://www.cplusplus.com/reference/map/map/operator[]/
	
		If k matches the key of an element in the container, the function returns a reference to its mapped value.
		If k does not match the key of any element in the container, the function inserts a new element with that key and returns a reference to its mapped value. Notice that this always increases the container size by one, even if no mapped value is assigned to the element (the element is constructed using its default constructor).
	*/
	mapped_type &operator[](const key_type &key) {
		iterator	ret = _tree.find(ft::make_pair(key, mapped_type()));

		if (ret != end())
			return ret.base->value.second;

		ft::pair<iterator, bool> tmp = insert(ft::make_pair(key, mapped_type()));
		return tmp.first.base->value.second;
	}

	/*
		- [ MODIFIERS ] -

		https://www.cplusplus.com/reference/map/map/insert/

		Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.

		Because element keys in a map are unique, the insertion operation checks whether each inserted element has a key equivalent to the one of an element already in the container, and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).

		(1) single element
	*/
	ft::pair<iterator, bool> insert(const value_type& val) {
		return _tree.insert(val);
	}

	/*
		(2) with hint
	*/
	iterator insert(iterator position, const value_type& val) {
		return _tree.insert(position, val);
	}

	/*
		(3) range
	*/
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last,
				typename ft::enable_if<
					!ft::is_integral<InputIterator>::value
				>::type * = NULL) {
		return _tree.insert(first, last);
	}

	/*
		https://www.cplusplus.com/reference/map/map/erase/

		Erase elements
		Removes from the map container either a single element or a range of elements ([first,last)).

		This effectively reduces the container size by the number of elements removed, which are destroyed.
	*/
	void erase(iterator position) {
		return _tree.erase(position);
	}
	size_type erase(const key_type& k) {
		return _tree.erase(ft::make_pair(k, mapped_type()));
	}
	void erase(iterator first, iterator last) {
		return _tree.erase(first, last);
	}

	/*
		https://www.cplusplus.com/reference/map/map/swap/

		Swap content
		Exchanges the content of the container by the content of x, which is another map of the same type. Sizes may differ.

		After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
	*/
	void swap(map& x) {
		std::swap(_alloc, x._alloc);
		std::swap(_key_compare, x._key_compare);
		std::swap(_value_compare, x._value_compare);
		_tree.swap(x._tree);
	}

	/*
		https://www.cplusplus.com/reference/map/map/clear/

		Clear content
		Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
	*/
	void clear() {
		return _tree.clear();
	}

	/*
		- [ OBSERVERS ] -

		https://www.cplusplus.com/reference/map/map/key_comp/
	
		Return key comparison object
		Returns a copy of the comparison object used by the container to compare keys.

		The comparison object of a map object is set on construction. Its type (member key_compare) is the third template parameter of the map template. By default, this is a less object, which returns the same as operator<.
	*/
	key_compare key_comp() const {
		return _key_compare;
	}

	/*
		https://www.cplusplus.com/reference/map/map/value_comp/

		Return value comparison object
		Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second.

		The arguments taken by this function object are of member type value_type (defined in map as an alias of pair<const key_type,mapped_type>), but the mapped_type part of the value is not taken into consideration in this comparison.
	*/
	value_compare value_comp() const {
		return _value_compare;
	}

	/*
		- [ OPERATIONS ] -

		https://www.cplusplus.com/reference/map/map/find/
	
		Get iterator to element
		Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.

		Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
	*/
	iterator find(const key_type &k) {
		return _tree.find(ft::make_pair(k, mapped_type()));
	}
	const_iterator find(const key_type &k) const {
		return _tree.find(ft::make_pair(k, mapped_type()));
	}

	/*
		https://www.cplusplus.com/reference/map/map/count/

		Count elements with a specific key
		Searches the container for elements with a key equivalent to k and returns the number of matches.

		Because all elements in a map container are unique, the function can only return 1 (if the element is found) or zero (otherwise).
	*/
	size_type count(const key_type& k) const {
		iterator it = find(k);

		return it == end() ? 0 : 1;
	}

	/*
		https://www.cplusplus.com/reference/map/map/lower_bound/	
	
		Return iterator to lower bound
		Returns an iterator pointing to the first element in the container whose key is not considered to go before k (i.e., either it is equivalent or goes after).

		The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the first element for which key_comp(element_key,k) would return false.
	*/
	iterator lower_bound(const key_type& k) {
		return _tree.lower_bound(ft::make_pair(k, mapped_type()));
	}
	const_iterator lower_bound(const key_type& k) const {
		return _tree.lower_bound(ft::make_pair(k, mapped_type()));
	}

	/*
		https://www.cplusplus.com/reference/map/map/upper_bound/

		Return iterator to upper bound
		Returns an iterator pointing to the first element in the container whose key is considered to go after k.

		The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the first element for which key_comp(k,element_key) would return true.
	*/
	iterator upper_bound(const key_type& k) {
		return _tree.upper_bound(ft::make_pair(k, mapped_type()));
	}
	const_iterator upper_bound(const key_type& k) const {
		return _tree.upper_bound(ft::make_pair(k, mapped_type()));
	}

	/*
		https://www.cplusplus.com/reference/map/map/equal_range/

		Get range of equal elements
		Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.

		Because the elements in a map container have unique keys, the range returned will contain a single element at most.

		If no matches are found, the range returned has a length of zero, with both iterators pointing to the first element that has a key considered to go after k according to the container's internal comparison object (key_comp).
	*/
	ft::pair<const_iterator, const_iterator>
	equal_range(const key_type& k) const {
		return _tree.equal_range(ft::make_pair(k, mapped_type()));
	}
	ft::pair<iterator, iterator> equal_range(const key_type& k) {
		return _tree.equal_range(ft::make_pair(k, mapped_type()));
	}

	/*
		- [ ALLOCATOR ] -

		https://www.cplusplus.com/reference/map/map/get_allocator/

		Get allocator
		Returns a copy of the allocator object associated with the map.
	*/
	allocator_type	get_allocator() const {
		return _alloc;
	}
};

/*
		- [ COMPARISON OPERATORS ] -
	
	https://en.cppreference.com/w/cpp/container/map/operator_cmp
*/

template<class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
	const ft::map<Key, T, Compare, Alloc>& rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
	const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs == rhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
	const ft::map<Key, T, Compare, Alloc>& rhs) {
	return ft::lexicographical_compare(
		lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
	const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
	const ft::map<Key, T, Compare, Alloc>& rhs) {
	return rhs < lhs;
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
	const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs < rhs);
}

}  // namespace ft

#endif  // MAP_HPP_
