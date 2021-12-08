#pragma once

#include "iterators.hpp"

namespace ft {
	template <	typename T, typename Distance = ptrdiff_t,
				typename Pointer = T*, typename Reference = T&>
	struct random_access_iterator{

		typedef T																	iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference				reference;

		//CONSTRUCTOR
		random_access_iterator() : _ptr(NULL){}
		random_access_iterator(pointer _val) : _ptr(_val) {}
		template<class U>
		random_access_iterator(const random_access_iterator<U>& other): _ptr(*other){}
		template<class U>
		random_access_iterator& operator=(const random_access_iterator<U>& other){_ptr = *other; return *this;}
		~random_access_iterator() {};


		//DEREFERENCE
		reference operator*() const {return *_ptr;}
		pointer operator->() const {return _ptr;}

		//INCREMENT
		random_access_iterator &operator++(){_ptr++; return *this;}
		random_access_iterator operator++(int){random_access_iterator tmp(*this); _ptr++; return tmp;}

		//DECREMENT
		random_access_iterator &operator--(){_ptr--; return *this;}
		random_access_iterator operator--(int){random_access_iterator tmp(*this); _ptr--; return tmp;}

		//ARITHMETIC
		random_access_iterator operator+( difference_type n ) const { return random_access_iterator(_ptr + n); }
		random_access_iterator operator-( difference_type n ) const { return random_access_iterator(_ptr - n); }

		//EQUAL ARITHMETIC
		random_access_iterator& operator+=( difference_type n ) { _ptr += n; return *this; }
		random_access_iterator& operator-=( difference_type n ) { _ptr -= n; return *this; }

		//OFFSET DEREFERENCE
		pointer *operator[](difference_type n) const { return _ptr + n; }

		private:
			pointer _ptr;
	};

	//EQUIVALENCE COMPARISONS
	template<class I1, class I2>
	bool operator==(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (*_lhs == *_rhs);
	}
	template<class I1, class I2>
	bool operator!=(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (*_lhs != *_rhs);
	}
	template<class I1, class I2>
	bool operator<(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (&(*_lhs) < &(*_rhs));
	}
	template<class I1, class I2>
	bool operator>(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (&(*_lhs) > &(*_rhs));
	}
	template<class I1, class I2>
	bool operator<=(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (&(*_lhs) <= &(*_rhs));
	}
	template<class I1, class I2>
	bool operator>=(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (&(*_lhs) >= &(*_rhs));
	}

	//DIFFERENCE
	template <class It>
	int	operator- ( const ft::random_access_iterator<It>& a , const ft::random_access_iterator<It>&b ) {
		return &(*a) - &(*b);
	}
};