/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:39:15 by marvin            #+#    #+#             */
/*   Updated: 2021/12/01 23:22:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <type_traits>
#include <algorithm>
#include <memory>

namespace ft{

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	struct contiguous_iterator_tag: public random_access_iterator_tag { };

	template <	class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class Iter>
	struct iterator_traits {
		typedef	 Iter::difference_type difference_type;
		typedef	 Iter::value_type value_type;
		typedef	 Iter::pointer pointer;
		typedef	 Iter::reference reference;
		typedef	 Iter::iterator_category iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category; //no se si esto esta bien
	};

	template <typename T>
	struct iterator_traits<const T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class Iter>
	class reverse_iterator : public ft::iterator <
		typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference
	> {
		typedef	iterator_traits<Iter>::value_type value_type;
		typedef iterator_traits<Iter>::difference_type difference_type;
		typedef iterator_traits<Iter>::pointer pointer;
		typedef iterator_traits<Iter>::referencertgf reference;
		typedef iterator_traits<Iter>::iteradfttor_category iterator_category;
		typedef Iter iterator_type;

		reverse_iterator(){}
		explicit reverse_iterator(iterator_type x): current(x)	{}
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other)current(other.base()){}

		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other) {current = other.base(); return *this;}
		iterator_type base() const {return current;}
		reference operator*() const {Iter tmp = current; return *--tmp;}
		pointer operator->() const {return std::addressof(operator*());}
		operator[](difference_type n) const {base()[-n-1];}

		reverse_iterator& operator++() { current--; return *this }
		reverse_iterator operator++(int) { reverse_iterator tmp(*this); current--; return tmp; }
		reverse_iterator& operator--() { current++; return *this }
		reverse_iterator operator--(int) { reverse_iterator tmp(*this); current++; return tmp; }
		reverse_iterator operator+( difference_type n ) const { return reverse_iterator(current - n); }
		reverse_iterator operator-( difference_type n ) const { return reverse_iterator(current + n); }
		reverse_iterator& operator+=( difference_type n ) { current -= n; return *this; }
		reverse_iterator& operator-=( difference_type n ) { current += n; return *this; }

		template< class Iterator1, class Iterator2 >
		bool operator==(const reverse_iterator<Iterator1>& lhs,	const reverse_iterator<Iterator2>& rhs) {
			return (lhs.base() == rhs.base());
		}
		template< class Iterator1, class Iterator2 >
		bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
			return (lhs.base() != rhs.base());
		}
		template< class Iterator1, class Iterator2 >
		bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
			return (lhs.base() > rhs.base());
		}
		template< class Iterator1, class Iterator2 >
		bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
			return (lhs.base() >= rhs.base());
		}
		template< class Iterator1, class Iterator2 >
		bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
			return (lhs.base() < rhs.base());
		}
		template< class Iterator1, class Iterator2 >
		bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
			return (lhs.base() <= rhs.base());
		}
		template< class Iterator >
		reverse_iterator<Iterator> operator+	(difference_type n) const {
			return reverse_iterator(current - n);
		}
		template< class Iterator >
		reverse_iterator<Iterator> operator-	(difference_type n) const {
			return reverse_iterator(current + n);
		}

		protected:
			iterator_type current;
	};

	template< bool B, class T = void >
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template< class T >
	struct is_integral { static const bool value = false; };

	struct is_integral<bool> {static const bool value = true;};
	struct is_integral<char> {static const bool value = true;};
	struct is_integral<char16_t> {static const bool value = true;};
	struct is_integral<char32_t> {static const bool value = true;};
	struct is_integral<wchar_t> {static const bool value = true;};
	struct is_integral<short> {static const bool value = true;};
	struct is_integral<int> {static const bool value = true;};
	struct is_integral<long> {static const bool value = true;};
	struct is_integral<long long> {static const bool value = true;};

	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare(	InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2 ) {
		while (first1!=last1) {
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
	/* template< class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(	InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2,
									Compare comp) {
		while (first1!=last1) {
			if (comp(first1, first2)) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	} */

	template< class T1, class T2> struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair(): first(), second(){};
		pair(const T1& x, const T2& y): first(x), second(y){}
		template<class U1, class U2>
		pair(const pair<U1, U2>& p): first(p.first), second(p.second){}

		pair& operator=(const pair& pr){first = pr.first; second = pr.second; return *this;}

		template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

		template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

		template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

		template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

		template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

		template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }
	};

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
		return ( pair<T1,T2>(x,y) );
	}

};
