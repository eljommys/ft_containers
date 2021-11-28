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

	template<
		typename Category,
		typename T,
		typename Distance = std::ptrdiff_t,
		typename Pointer = T*,
		typename Reference = T&
	> struct iterator {
		using	iterator_category = Category;
		using	value_type = T;
		using	difference_type = Distance;
		using	pointer = Pointer;
		using	reference = Reference;

		iterator(pointer ptr) : m_ptr(ptr) {}

		reference	operator*() const	{return *m_ptr;}
		poiner		operator->()		{return m_ptr;}
		iterator&	operator++()		{m_ptr++; return *this;}
		iterator	operator++(int)		{Iterator tmp = *this; ++(*this); return tmp;}

		friend bool	operator==(const iterator& a, const iterator& b)	{return a.m_ptr == b.m_ptr;}
		friend bool	operator!=(const iterator& a, const iterator& b)	{return a.m_ptr != b.m_ptr;}

		private:
		pointer m_ptr;
	};

	template <class Iter>
	struct iterator_traits {
		using	difference_type = Iter::difference_type;
		using	value_type = Iter::value_type;
		using	pointer = Iter::pointer;
		using	reference = Iter::reference;
		using	iterator_category = Iter::iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*> {
		using	difference_type = std::ptrdiff_t;
		using	value_type = T;
		using	pointer = T*;
		using	reference = T&;
		using	iterator_category = std::random_access_iterator_tag;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		using	difference_type = std::ptrdiff_t;
		using	value_type = T;
		using	pointer = const T*;
		using	reference = const T&;
		using	iterator_category = std::random_access_iterator_tag;
	};

	template <class Iter>
	class reverse_iterator : public iterator <
		typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference
	> {
		using	value_type = iterator_traits<Iter>::value_type;
		using	difference_type = iterator_traits<Iter>::difference_type;
		using	pointer = iterator_traits<Iter>::pointer;
		using	reference = iterator_traits<Iter>::reference;
		using	iterator_category = iterator_traits<Iter>::iterator_category;
		using	iterator_type = Iter;

		reverse_iterator()	{}
		explicit reverse_iterator(iterator_type x)	{}
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other)	{}

		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other) {return *this;}
		iterator_type base() const {return iterator_type;}

	};
};
