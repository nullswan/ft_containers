# Result

[![.github/workflows/cpplint.yml](https://github.com/c3b5aw/ft_containers/actions/workflows/cpplint.yml/badge.svg?branch=main)](https://github.com/c3b5aw/ft_containers/actions/workflows/cpplint.yml) <br />

# Mandatory part

### vector

| **Member** | **State** | **Description** |
|:--------------------:|:-----:|:-----:|
| *Member types* | 1/1 | 2021/11/11 |
| *Member function* | 1/3 |  |
| (constructor) | x | Construct vector (public member function ) 	|
| (destructor) 	| OK | Vector destructor (public member function ) 	|
| operator= 	| x | Assign content (public member function ) 		|
| *Iterators* | 4/4 | 2021/11/11 |
| begin 	| OK | Return iterator to beginning (public member function ) 						|
| end 		| OK | Return iterator to end (public member function ) 								|
| rbegin 	| OK | Return reverse iterator to reverse beginning (public member function ) 		|
| rend 		| OK | Return reverse iterator to reverse end (public member function ) 				|
| *Capacity* | 4/6 | |
| size 			| OK |  Return size (public member function )									|
| max_size 		| OK |  Return maximum size (public member function )						|
| resize 		| x |  Change size (public member function )								|
| capacity 		| OK |  Return size of allocated storage capacity (public member function )	|
| empty 		| OK |  Test whether vector is empty (public member function )				|
| reserve 		| x |  Request a change in capacity (public member function )				|
| *Element access* | 4/4 | 2021/11/11 |
| operator[] 	| OK | Access element (public member function ) 			|
| at 			| OK | Access element (public member function ) 			|
| front 		| OK | Access first element (public member function )	|
| back 			| OK | Access last element (public member function )		|
| *Modifiers* | 1/7 | |
| assign 	| x | Assign vector content (public member function )	|
| push_back | x | Add element at the end (public member function )	|
| pop_back 	| x | Delete last element (public member function )		|
| insert 	| x | Insert elements (public member function )			|
| erase 	| x | Erase elements (public member function )			|
| swap 		| x | Swap content (public member function )			|
| clear 	| OK | Clear content (public member function )			|
| *Allocator* | 1/1 | 2021/11/11 |
| get_allocator | OK | Get allocator (public member function ) |
| *Non-member function overloads* | 2/2 | 2021/11/11 |
| relational  	| OK | operators Relational operators for vector (function template )|
| swap Exchange | OK | contents of vectors (function template )						|

### map

### stack

# Bonus

### set

---

# Additional containers

### iterator

- random_access_iterator
- reverse_iterator

### algorithm

- equal
- lexigraphical_compare