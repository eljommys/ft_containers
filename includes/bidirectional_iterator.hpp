#pragma once

#include "ft.hpp"

namespace ft {
	template <typename T>
	class bidirectional_iterator {
		public:
		typedef T																				iterator_type;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::pointer				pointer;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::reference			reference;

		bidirectional_iterator() : it(NULL) {};
		bidirectional_iterator(const bidirectional_iterator &other) :
			it(other.it) {}

		//template <class S>
		//bidirectional_iterator(const bidirectional_iterator<S>& other) : it(other) {}

		//bidirectional_iterator(const iterator_type & other) : it(other) {}

		virtual ~bidirectional_iterator(){}

		bidirectional_iterator & operator=(const bidirectional_iterator& other) {
			if (this == &other)
				return *this;
			it = other.it;
			return *this;
		}

		reference	operator*()		const {return *it ;}
		pointer		operator->()	const {return &( this->operator*());}

		bidirectional_iterator operator++ (int) {bidirectional_iterator aux(*this); (*this) = next; return aux;}
		bidirectional_iterator& operator++() {(*this) = next; return *this; }

		bidirectional_iterator operator-- (int) {bidirectional_iterator aux(*this); (*this) = prev; return aux;}
		bidirectional_iterator& operator--() {(*this) = prev; return *this; }

		protected:
		bidirectional_iterator<iterator_type> &prev;
		iterator_type it;
		bidirectional_iterator<iterator_type> &next;
	};
}
