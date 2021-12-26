# Result

[![.github/workflows/docs.yml](https://github.com/c3b5aw/ft_containers/actions/workflows/docs.yml/badge.svg?branch=main)](https://github.com/c3b5aw/ft_containers/actions/workflows/docs.yml) <br />
[![.github/workflows/cpplint.yml](https://github.com/c3b5aw/ft_containers/actions/workflows/cpplint.yml/badge.svg?branch=main)](https://github.com/c3b5aw/ft_containers/actions/workflows/cpplint.yml) <br />
[![.github/workflows/docs.yml](https://github.com/c3b5aw/ft_containers/actions/workflows/unit_test.yml/badge.svg?branch=main)](https://github.com/c3b5aw/ft_containers/actions/workflows/unit_test.yml)

# Mandatory part

### vector

| **Member** | **State** | **Description** |
|:--------------------:|:-----:|:-----:|
| *Member types* | 1/1 | * |
| *Member function* | 3/3 | **  |
| (constructor) | OK | Construct vector (public member function ) 	|
| (destructor) 	| OK | Vector destructor (public member function ) 	|
| operator= 	| OK | Assign content (public member function ) 		|
| *Iterators* | 4/4 | * |
| begin 	| OK | Return iterator to beginning (public member function ) 						|
| end 		| OK | Return iterator to end (public member function ) 								|
| rbegin 	| OK | Return reverse iterator to reverse beginning (public member function ) 		|
| rend 		| OK | Return reverse iterator to reverse end (public member function ) 				|
| *Capacity* | 6/6 | ** |
| size 			| OK |  Return size (public member function )									|
| max_size 		| OK |  Return maximum size (public member function )						|
| resize 		| OK |  Change size (public member function )								|
| capacity 		| OK |  Return size of allocated storage capacity (public member function )	|
| empty 		| OK |  Test whether vector is empty (public member function )				|
| reserve 		| OK |  Request a change in capacity (public member function )				|
| *Element access* | 4/4 | * |
| operator[] 	| OK | Access element (public member function ) 			|
| at 			| OK | Access element (public member function ) 			|
| front 		| OK | Access first element (public member function )	|
| back 			| OK | Access last element (public member function )		|
| *Modifiers* | 5/7 | *** |
| assign 	| OK | Assign vector content (public member function )	|
| push_back | OK | Add element at the end (public member function )	|
| pop_back 	| OK | Delete last element (public member function )		|
| insert 	| OK | Insert elements (public member function )			|
| erase 	| OK | Erase elements (public member function )			|
| swap 		| OK | Swap content (public member function )			|
| clear 	| OK | Clear content (public member function )			|
| *Allocator* | 1/1 | * |
| get_allocator | OK | Get allocator (public member function ) |
| *Non-member function overloads* | 2/2 | * |
| relational  	| OK | operators Relational operators for vector (function template )|
| swap Exchange | OK | contents of vectors (function template )						|

### map

### stack

| **Member** | **State** | **Description** |
|:--------------------:|:-----:|:-----:|
| *Member types* | 1/1 | * |
| *Member function* | 11/11 | **  |
| (constructor) | OK | Construct stack (public member function ) 	|
| (copy-constructor) | OK | Construct by Copy stack (public member function ) 	|
| (destructor) 	| OK | Stack destructor (public member function ) 	|
| operator= 	| OK | Assign content (public member function ) 		|
| empty 		| OK | Test whether container is empty (public member function ) |
| size 			| OK | Return size (public member function ) |
| top			| OK | Access next element (public member function ) |
| push 			| OK | Insert element (public member function ) |
| emplace 		| OK | Construct and insert element (public member function ) |
| pop 			| OK | Remove top element (public member function ) |
| swap 			| OK | Swap content (public member function ) |

# Bonus

### set

---

# Additional classes

### iterator	
- random_access_iterator
- reverse_iterator

### algorithm
- equal
- lexigraphical_compare

### types
- type_trait
	- is_integral
	- enable_if

### tree
- rb_tree
