#pragma once

#include "ft.hpp"

namespace ft {

	template < typename T >
	struct	Tree {
		Tree<T>	*prev;
		T		val;
		Tree<T>	*left;
		Tree<T>	*right;
	};

	template <typename T>
	class bidirectional_iterator {
		public:
		typedef T																				iterator_type;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::pointer				pointer;
		typedef typename ft::bidirectional_iterator_traits<iterator_type>::reference			reference;

		bidirectional_iterator() : it(ft::nullptr_t) {};
		bidirectional_iterator(const bidirectional_iterator &other) : //
			it(other.it) {}

		bidirectional_iterator(Tree<iterator_type> *ptr) : it(ptr) {}

		//template <class S>
		//bidirectional_iterator(const bidirectional_iterator<S>& other) : it(other) {}

		//bidirectional_iterator(const iterator_type & other) : it(other) {}

		virtual ~bidirectional_iterator() {}

		bidirectional_iterator & operator=(const bidirectional_iterator& other) {
			if (this == &other)
				return *this;
			it = other.it;
			return *this;
		}

		reference	operator*()		const {return it->val ;}
		pointer		operator->()	const {return &( this->operator*());}

		bidirectional_iterator operator++ (int) {
			bidirectional_iterator ret = *this;
			_increment();
			return ret;
		}
		bidirectional_iterator& operator++() {
			_increment();
			return *this;
		}

		bidirectional_iterator operator-- (int) {
			bidirectional_iterator ret = *this;
			_decrement();
			return ret;
		}
		bidirectional_iterator& operator--() {
			_decrement();
			return *this;
		}

		protected:
		Tree<iterator_type>						*it;

		private:
		void	_increment() {
			Tree<iterator_type> *ret = it;

			if (it->right)
				it = it->right;
			else {
				Tree<iterator_type>	*aux = it;
				it = it->prev;
				while (it && aux == it->right) {
					aux = it;
					it = it->prev;
				}
				if (!it)
					it = ret;
			}
		}

		void	_decrement() {
			Tree<iterator_type> *ret = it;

			if (it->left)
				it = it->left;
			else {
				Tree<iterator_type>	*aux = it;
				it = it->prev;
				while (it && aux == it->left) {
					aux = it;
					it = it->prev;
				}
				if (!it)
					it = ret;
			}
		}
	};
}
