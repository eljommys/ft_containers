#pragma once

#include "iterators.hpp"

namespace ft {

	/* template <	typename Category, typename T, typename Distance = ptrdiff_t,
				typename Pointer = T*, typename Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <typename Iter>
	class reverse_iterator : public ft::iterator <
		typename ft::iterator_traits<Iter>::iterator_category,
		typename ft::iterator_traits<Iter>::value_type,
		typename ft::iterator_traits<Iter>::difference_type,
		typename ft::iterator_traits<Iter>::pointer,
		typename ft::iterator_traits<Iter>::reference
	> {
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::referencertgf reference;
		typedef typename ft::iterator_traits<Iter>::iteradfttor_category iterator_category;
		typedef Iter iterator_type;

		reverse_iterator(){}
		explicit reverse_iterator(iterator_type x): it(x)	{}
		template<typename U>
		reverse_iterator(const reverse_iterator<U>& other): it(other.base()){}

		template<typename U>
		reverse_iterator& operator=(const reverse_iterator<U>& other) {it = other.base(); return *this;}
		iterator_type base() const {return it;}
		reference operator*() const {Iter tmp = it; return *--tmp;}
		pointer operator->() const {return std::addressof(operator*());}
		reference operator[](difference_type n) const {return base()[-n-1];}

		reverse_iterator& operator++() { it--; return *this; }
		reverse_iterator operator++(int) { reverse_iterator tmp(*this); it--; return tmp; }
		reverse_iterator& operator--() { it++; return *this; }
		reverse_iterator operator--(int) { reverse_iterator tmp(*this); it++; return tmp; }
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(it - n); }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(it + n); }
		reverse_iterator& operator+=(difference_type n) { it -= n; return *this; }
		reverse_iterator& operator-=(difference_type n) { it += n; return *this; }

		template< typename Iterator >
		reverse_iterator<Iterator> operator+(difference_type n) const {
			return reverse_iterator(it - n);
		}
		template< typename Iterator >
		reverse_iterator<Iterator> operator-	(difference_type n) const {
			return reverse_iterator(it + n);
		}
		protected:
			iterator_type it;
	};

	template< typename Iterator1, typename Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs,	const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template< typename Iterator1, typename Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template< typename Iterator1, typename Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() > rhs.base());
	}
	template< typename Iterator1, typename Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() >= rhs.base());
	}
	template< typename Iterator1, typename Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}
	template< typename Iterator1, typename Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() <= rhs.base());
	};

	template< bool B, class T = void >
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T> { typedef T type; };

	template< typename T >
	struct is_integral { static const bool value = false; };

	template<> struct is_integral<bool> {static const bool value = true;};
	template<> struct is_integral<char> {static const bool value = true;};
	template<> struct is_integral<char16_t> {static const bool value = true;};
	template<> struct is_integral<char32_t> {static const bool value = true;};
	template<> struct is_integral<wchar_t> {static const bool value = true;};
	template<> struct is_integral<short> {static const bool value = true;};
	template<> struct is_integral<int> {static const bool value = true;};
	template<> struct is_integral<long> {static const bool value = true;};
	template<> struct is_integral<long long> {static const bool value = true;};

	template< typename T1, typename T2> struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair(): first(), second(){};
		pair(const T1& x, const T2& y): first(x), second(y){}
		template<typename U1, typename U2>
		pair(const pair<U1, U2>& p): first(p.first), second(p.second){}

		pair& operator=(const pair& pr){first = pr.first; second = pr.second; return *this;}

	};

	template <typename T1, typename T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <typename T1, typename T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <typename T1, typename T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <typename T1, typename T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <typename T1, typename T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <typename T1, typename T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	template <typename T1,typename T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
		return (pair<T1,T2>(x,y));
	} */
	template <typename T>
	class reverse_iterator {
		public:
		typedef T																	iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference				reference;

		reverse_iterator() : it(NULL) {}
		explicit reverse_iterator(iterator_type _it) : it(_it) {}

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

	//EQUIVALENCE COMPARISONS
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
