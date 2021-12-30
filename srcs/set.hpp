/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:50:22 by c3b5aw            #+#    #+#             */
/*   Updated: 2021/12/30 16:48:17 by c3b5aw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP_
#define SET_HPP_

/*
	Link:
	https://www.cplusplus.com/reference/set/set/
*/

#include <memory>		// provides std::allocator
#include <functional>   // provides std::less

#include "tree/rb_tree.hpp"

namespace ft {
template <
	class T,							// set::key_type/value_type
	class Compare = std::less<T>,		// set::key_compare/value_compare
	class Alloc = std::allocator<T>		// set::allocator_type
>
class set {
 public:
	typedef T	key_type;
	typedef T	value_type;

	typedef Compare	key_compare;
	typedef Compare	value_compare;
	typedef Alloc	allocator_type;

	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	typedef typename ft::rb_tree<value_type, key_compare>::iterator iterator;
	typedef typename ft::rb_tree
		<value_type, key_compare>::const_iterator const_iterator;
	typedef typename ft::rb_tree
		<value_type, key_compare>::reverse_iterator reverse_iterator;
	typedef typename ft::rb_tree
		<value_type, key_compare>::const_reverse_iterator const_reverse_iterator;

	typedef std::ptrdiff_t	difference_type;
	typedef std::size_t		size_type;

 private:
	allocator_type	_alloc;
	key_compare		_key_compare;
	value_compare	_value_compare;

	ft::rb_tree<value_type, key_compare> _tree;

 public:
	/*
		- [ CONSTRUCTORS ] -

		Construct set
		Constructs a set container object, initializing its contents depending on the constructor version used:

		(1) empty container constructor (default constructor)
   		Constructs an empty container, with no elements.
	*/
	explicit set(const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	:	_alloc(alloc),
		_key_compare(comp),
		_value_compare(comp),
		_tree(_alloc) {}

	/*
		(2) range constructor
    	Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range.
	*/
	template <class InputIterator>
	set(InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type(),
	   typename ft::enable_if<!ft::is_integral<InputIterator>::value,
		InputIterator>::type* = NULL)
	:	_alloc(alloc),
		_key_compare(comp),
		_value_compare(comp),
		_tree(_alloc) {
		insert(first, last);
	}

	/*
		(3) copy constructor
    	Constructs a container with a copy of each of the elements in x.
	*/
	set(const set& x)
	:	_alloc(x._alloc),
		_key_compare(x._key_compare),
		_value_compare(x._value_compare),
		_tree(x._tree) {}

	/*
		- [ ASSIGNEMENT OPERATOR ] -
		https://www.cplusplus.com/reference/set/set/operator=/

		Copy container content
		Assigns new contents to the container, replacing its current content.
	*/
	set &operator= (const set &x) {
		if (this != &x) {
			_alloc = x._alloc;
			_key_compare = x._key_compare;
			_value_compare = x._value_compare;
			_tree = x._tree;
		}
		return *this;
	}

	/*
		- [ DESTRUCTORS ] -

		Set destructor
		Destroys the container object.
	*/
	~set() {}

	/*
		- [ ITERATORS ] -
	
		https://www.cplusplus.com/reference/set/set/begin/

		Return iterator to beginning
		Returns an iterator referring to the first element in the set container.

		Because set containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
	*/
	iterator begin() {
		return _tree.begin();
	}
	const_iterator begin() const {
		return _tree.begin();
	}

	/*
		https://www.cplusplus.com/reference/set/set/end/


		Return iterator to end
		Returns an iterator referring to the past-the-end element in the set container.

		The past-the-end element is the theoretical element that would follow the last element in the set container. It does not point to any element, and thus shall not be dereferenced.
	*/
	iterator end() {
		return _tree.end();
	}
	const_iterator end() const {
		return _tree.end();
	}

	/*
		https://www.cplusplus.com/reference/set/set/rbegin/

		Return reverse iterator to reverse beginning
		Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).

		Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
	*/
	reverse_iterator rbegin() {
		return _tree.rbegin();
	}
	const_reverse_iterator rbegin() const {
		return _tree.rbegin();
	}

	/*
		https://www.cplusplus.com/reference/set/set/rend/

		Return reverse iterator to reverse end
		Returns a reverse iterator pointing to the theoretical element right before the first element in the set container (which is considered its reverse end).
	*/
	reverse_iterator rend() {
		return _tree.rend();
	}
	const_reverse_iterator rend() const {
		return _tree.rend();
	}

	/*
		- [ CAPACITY ] -
	
		https://www.cplusplus.com/reference/set/set/empty/

		Test whether container is empty
		Returns whether the set container is empty (i.e. whether its size is 0).
	*/
	bool empty() const {
		return _tree.empty();
	}

	/*
		https://www.cplusplus.com/reference/set/set/size/

		Return container size
		Returns the number of elements in the set container.
	*/
	size_type size() const {
		return _tree.size();
	}

	/*
		https://www.cplusplus.com/reference/set/set/max_size/

		Return maximum size
		Returns the maximum number of elements that the set container can hold.
	*/
	size_type max_size() const {
		return _tree.max_size();
	}

	/*
		- [ MODIFIERS ] -

		https://www.cplusplus.com/reference/set/set/insert/

		Insert element
		Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.

		Because elements in a set are unique, the insertion operation checks whether each inserted element is equivalent to an element already in the container, and if so, the element is not inserted, returning an iterator to this existing element (if the function returns a value).

		For a similar container allowing for duplicate elements, see multiset.

		Internally, set containers keep all their elements sorted following the criterion specified by its comparison object. The elements are always inserted in its respective position following this ordering.
		
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
		https://www.cplusplus.com/reference/set/set/erase/


		Erase elements
		Removes from the set container either a single element or a range of elements ([first,last)).

		This effectively reduces the container size by the number of elements removed, which are destroyed.
	*/
	void erase(iterator position) {
		return _tree.erase(position);
	}
	size_type erase(const key_type& k) {
		return _tree.erase(k);
	}
	void erase(iterator first, iterator last) {
		return _tree.erase(first, last);
	}

	/*
		https://www.cplusplus.com/reference/set/set/swap/

		Swap content
		Exchanges the content of the container by the content of x, which is another set of the same type. Sizes may differ.

		After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
	*/
	void swap(set &x) {
		std::swap(_alloc, x._alloc);
		std::swap(_key_compare, x._key_compare);
		std::swap(_value_compare, x._value_compare);
		_tree.swap(x._tree);
	}

	/*
		https://www.cplusplus.com/reference/set/set/clear/

		Clear content
		Removes all elements from the set container (which are destroyed), leaving the container with a size of 0.
	*/
	void clear() {
		return _tree.clear();
	}

	/*
		- [ OBSERVERS ] -
	
		https://www.cplusplus.com/reference/set/set/key_comp/
	
		Return comparison object
		Returns a copy of the comparison object used by the container.

		By default, this is a less object, which returns the same as operator<.

		This object determines the order of the elements in the container: it is a function pointer or a function object that takes two arguments of the same type as the container elements, and returns true if the first argument is considered to go before the second in the strict weak ordering it defines, and false otherwise.
	*/
	key_compare key_comp() const {
		return _key_compare;
	}

	/*
		https://www.cplusplus.com/reference/set/set/value_comp/

		Return comparison object
		Returns a copy of the comparison object used by the container.

		By default, this is a less object, which returns the same as operator<.

		This object determines the order of the elements in the container: it is a function pointer or a function object that takes two arguments of the same type as the container elements, and returns true if the first argument is considered to go before the second in the strict weak ordering it defines, and false otherwise.

		Two elements of a set are considered equivalent if value_comp returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
	*/
	value_compare value_comp() const {
		return _value_compare;
	}

	/*
		- [ OPERATIONS ] -

		https://www.cplusplus.com/reference/set/set/find/
		
		Get iterator to element
		Searches the container for an element equivalent to val and returns an iterator to it if found, otherwise it returns an iterator to set::end.
	*/
	iterator find(const value_type &val) {
		return _tree.find(val);
	}
	const_iterator find(const value_type &val) const {
		return _tree.find(val);
	}

	/*
		https://www.cplusplus.com/reference/set/set/count/

		Count elements with a specific value

		Searches the container for elements equivalent to val and returns the number of matches.
		Because all elements in a set container are unique, the function can only return 1 (if the element is found) or zero (otherwise).
	*/
	size_type count(const value_type& val) const {
		const_iterator it = find(val);

		return it == end() ? 0 : 1;
	}

	/*
		https://www.cplusplus.com/reference/set/set/lower_bound/

		Return iterator to lower bound
		Returns an iterator pointing to the first element in the container which is not considered to go before val (i.e., either it is equivalent or goes after).

		The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the first element for which key_comp(element,val) would return false.

		If the set class is instantiated with the default comparison type (less), the function returns an iterator to the first element that is not less than val.
	*/
	iterator lower_bound(const value_type& val) const {
		return _tree.lower_bound(val);
	}

	/*
		https://www.cplusplus.com/reference/set/set/upper_bound/

		Return iterator to upper bound
		Returns an iterator pointing to the first element in the container which is considered to go after val.

		The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the first element for which key_comp(val,element) would return true.

		If the set class is instantiated with the default comparison type (less), the function returns an iterator to the first element that is greater than val.
	*/
	iterator upper_bound(const value_type& val) const {
		return _tree.upper_bound(val);
	}

	/*
		https://www.cplusplus.com/reference/set/set/equal_range/

		Get range of equal elements
		Returns the bounds of a range that includes all the elements in the container that are equivalent to val.

		Because all elements in a set container are unique, the range returned will contain a single element at most.

		If no matches are found, the range returned has a length of zero, with both iterators pointing to the first element that is considered to go after val according to the container's internal comparison object (key_comp).
	*/
	ft::pair<iterator, iterator> equal_range(const value_type& val) const {
		return _tree.equal_range(val);
	}

	/*
		- [ ALLOCATOR ] -

		https://www.cplusplus.com/reference/set/set/get_allocator/

		Get allocator
		Returns a copy of the allocator object associated with the set.
	*/
	allocator_type get_allocator() const {
		return _alloc;
	}
};
}  // namespace ft

#endif  // SET_HPP_
