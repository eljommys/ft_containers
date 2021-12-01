#pragma once

#include "../ft.hpp"

namespace ft
{

	struct random_access_iterator_tag {}:

	template < class T, class Alloc = std::allocator<T> > class vector{
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		typedef ft::vector_iterator iterator;
		typedef const ft::vector_iterator const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef const ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ft::iterator_traits<iterator>::difference_type difference_type;
		typedef std::size_t size_type;
	}

}