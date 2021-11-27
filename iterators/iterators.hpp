#pragma once

namespace ft{
	template<
		typename Category,
		typename T,
		typename Distance = ptrdiff_t,
		typename Pointer = T*,
		typename Reference = T&
	> struct iterator {
		Category	iterator_category;
		T			value_type;
		Distance	difference_type;
		Pointer		pointer;
		Reference	reference;
	}

	template <typename Iter>
	struct iterator_traits {
		using	Iter::difference_type;
		using	Iter::value_type;
		using	Iter::pointer;
		using	Iter::reference;
		using	Iter::iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*> {
		using	Iter::difference_type;
		using	Iter::value_type;
		using	Iter::pointer;
		using	Iter::reference;
		using	Iter::iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		using	Iter::difference_type;
		using	Iter::value_type;
		using	Iter::pointer;
		using	Iter::reference;
		using	Iter::iterator_category;
	};

	template <typename Iter>
	class reverse_iterator : public iterator <
		typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference
	> {

	};
};
