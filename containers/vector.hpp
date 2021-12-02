#pragma once

#include "../ft.hpp"

namespace ft
{
	template <class T>
	struct vector_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {

		//CONSTRUCTOR
		vector_iterator() ptr(NULL){}
		template<class U>
		vector_iterator(const vector_iterator<U>& other): ptr(other.ptr){}
		template<class U>
		vector_iterator& operator=(const vector_iterator<U>& other){ptr = other.ptr; return *this;}
		~vector_iterator() {};

		//EQUIVALENCE COMPARISONS
		template<class I1, class I2>
		bool operator==(const vector_iterator<I1>& lhs, const vector_iterator<I2>& rhs) const {
			return (lhs.ptr == rhs.ptr);
		}
		template<class I1, class I2>
		bool operator!=(const vector_iterator<I1>& lhs, const vector_iterator<I2>& rhs) const {
			return (lhs.ptr != rhs.ptr);
		}
		value_type operator*() {return *ptr};
		value_type operator->() {return *ptr}

		private:
			pointer ptr;
	}

	template < class T, class Alloc = std::allocator<T> >
	class vector{
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

};
