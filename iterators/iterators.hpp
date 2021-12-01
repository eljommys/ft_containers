/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:39:15 by marvin            #+#    #+#             */
/*   Updated: 2021/11/28 16:39:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft{

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
		typedef std::random_access_iterator_tag iterator_category;
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
	class reverse_iterator : public std::iterator <
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

		protected:
			iterator_type current;
	};

	template< bool B, class T = void >
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<class T>
	struct is_integral {
		static const bool value = false;

		typedef bool value_type;
		typedef std::integral_constant<bool, value> type;

		operator bool()
	};

	template<>	struct is_integral<bool> {static const bool value = true;};
	template<>	struct is_integral<char> {static const bool value = true;};
	template<>	struct is_integral<char8_t> {static const bool value = true;};
	template<>	struct is_integral<char16_t> {static const bool value = true;};
	template<>	struct is_integral<char32_t> {static const bool value = true;};
	template<>	struct is_integral<wchar_t> {static const bool value = true;};
	template<>	struct is_integral<short> {static const bool value = true;};
	template<>	struct is_integral<int> {static const bool value = true;};
	template<>	struct is_integral<long> {static const bool value = true;};
	template<>	struct is_integral<long long> {static const bool value = true;};
	// añadir el resto de tipos integrales
};
