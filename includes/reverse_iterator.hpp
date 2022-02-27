#pragma once

#include "ft.hpp"

namespace ft {

	template <typename T>
	class reverse_iterator {
		public:
		typedef T																	iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference				reference;

		reverse_iterator() : it() {}
		explicit reverse_iterator(iterator_type it) : it(it) {}

		template <typename S>
		reverse_iterator(const reverse_iterator<S>& other) : it(other.base()) {}

		iterator_type base() const{ return it; }

		reference			operator*() const { iterator_type aux = it; return *--aux; }
		pointer				operator->() const { return &(operator*()) ;}

		reverse_iterator	operator++(int)	{ reverse_iterator aux(*this); --it; return aux; }
		reverse_iterator&	operator++()		{ --it; return *this ; }

		reverse_iterator	operator--(int)	{ reverse_iterator aux(*this); ++it; return aux; }
		reverse_iterator&	operator--()		{ ++it; return *this; }

		reverse_iterator	operator+ (difference_type n) const { return reverse_iterator(it - n); }
		reverse_iterator&	operator+=(difference_type n)		{ it -= n; return *this ; }

		reverse_iterator	operator- (difference_type n) const { return reverse_iterator(it + n); }
		reverse_iterator&	operator-=(difference_type n)		{ it += n; return *this ; }

		reference			operator[](difference_type n) const { return *(*this + n) ; }

		protected:
		iterator_type	it;
	};

	//EQUIVALENCE COMPARATORS
	template< class _Iter1>
	bool operator== (const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter1>& rhs) {
		return lhs.base() == rhs.base();
	}
	template< class _Iter1, class _Iter2>
	bool operator== (const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template< class _Iter1>
	bool operator!=(const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter1>& rhs) {
		return !(lhs.base() == rhs.base()) ;
	}
	template < class _Iter1, class _Iter2>
	bool operator!= (const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator<_Iter2>&  rhs) {
		return  !(lhs.base() == rhs.base());
	}
	template < class _Iter1, class _Iter2 >
	bool operator< (const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator <_Iter2>& rhs) {
		return lhs.base() > rhs.base();
	}
	template < class _Iter1 >
	bool operator< (const ft::reverse_iterator<_Iter1>& lhs, const ft::reverse_iterator <_Iter1>& rhs) {
		return lhs.base() > rhs.base();
	}
	template < class _Iter1, class _Iter2 >
	bool operator> (const reverse_iterator<_Iter1>& lhs , const reverse_iterator <_Iter2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template < class _Iter1 >
	bool operator> (const reverse_iterator<_Iter1>& lhs , const reverse_iterator <_Iter1>& rhs) {
		return lhs.base() < rhs.base();
	}
	template < class _Iter1, class _Iter2 >
	bool operator>= (const reverse_iterator<_Iter1>& lhs , const reverse_iterator <_Iter2>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template < class _Iter1 >
	bool operator>= (const reverse_iterator<_Iter1>& lhs , const reverse_iterator <_Iter1>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template < class _Iter1, class _Iter2 >
	bool operator<= (const reverse_iterator<_Iter1>& lhs , const reverse_iterator <_Iter2>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template < class _Iter1 >
	bool operator<= (const reverse_iterator<_Iter1>& lhs , const reverse_iterator <_Iter1>& rhs) {
		return lhs.base() >= rhs.base();
	}

	//DIFFERENCE
	template< class _Iter1, class _Iter2>
	typename reverse_iterator<_Iter1>::difference_type
	operator-(const reverse_iterator<_Iter1>& lhs , const reverse_iterator<_Iter2>& rhs) {
		return rhs.base() - lhs.base() ;
	}
	template< class _Iter1>
	typename reverse_iterator<_Iter1>::difference_type
	operator-(const reverse_iterator<_Iter1>& lhs , const reverse_iterator<_Iter1>& rhs) {
		return lhs.base() - rhs.base() ;
	}
	template< class _Iter>
	reverse_iterator<_Iter>
	operator+(typename reverse_iterator<_Iter>::difference_type n , const reverse_iterator<_Iter>& lhs) {
		return  reverse_iterator<_Iter> (lhs.base() - n);
	}
};
