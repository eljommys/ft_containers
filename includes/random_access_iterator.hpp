#pragma once

#include "ft.hpp"

namespace ft
{
	template < typename T>
	class random_access_iterator {
		public:
		typedef T																	iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference				reference;

		random_access_iterator() : it(ft::nullptr_t){}

		template <class S>
		random_access_iterator( const random_access_iterator<S>& other) : it( other.base()) {}

		random_access_iterator( const iterator_type & other) : it( other) {}

		virtual ~random_access_iterator(){/* std::cout << "~random access iterator" << std::endl; */}

		random_access_iterator & operator=( const random_access_iterator& other) {
			if (this == &other)
				return *this;
			it = other.base();
			return *this;
		}

		iterator_type base() const { return it; }

		reference	operator*()		const { return *it ;}
		pointer		operator->()	const { return &( this->operator*());}

		random_access_iterator operator++ (int) { random_access_iterator aux( *this); ++(*this); return aux;}
		random_access_iterator& operator++() { ++it; return *this; }

		random_access_iterator operator-- (int) { random_access_iterator aux( *this); --(*this); return aux;}
		random_access_iterator& operator--() { --it; return *this; }

		random_access_iterator operator+ (difference_type n) const { return  it  + n; }
		random_access_iterator& operator+= (difference_type n) { it += n; return *this; }

		random_access_iterator operator- (difference_type n) const { return *this + (-n) ;}
		random_access_iterator& operator-= (difference_type n) { *this += -n; return *this; }

		reference 	operator[] ( difference_type n) const { return it[n]; }

		protected:
		iterator_type it;
	};

	//EQUIVALENCE COMPARISONS
	template<typename I1, typename I2>
	bool operator== (const random_access_iterator<I1>& lhs , const random_access_iterator<I2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template<typename I1, typename I2>
	bool operator< (const random_access_iterator<I1>& lhs, const random_access_iterator<I2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template<typename I1, typename I2>
	bool operator!= (const random_access_iterator<I1>& lhs, random_access_iterator<I2>& rhs) {
		return !(lhs == rhs) ;
	}
	template<typename I1, typename I2>
	bool operator> (const random_access_iterator<I1>& lhs, const random_access_iterator<I2>& rhs) {
		return rhs < lhs;
	}
	template<typename I1, typename I2>
	bool operator>= (const random_access_iterator<I1>& lhs, const random_access_iterator<I2>& rhs) {
		return !(lhs < rhs);
	}
	template<typename I1, typename I2>
	bool operator<= (const random_access_iterator<I1>& lhs, const random_access_iterator<I2>& rhs) {
		return !(rhs < lhs);
	}
	template <typename I1>
	bool operator!= (const random_access_iterator<I1>& lhs, const random_access_iterator<I1> rhs) {
		return !(lhs == rhs);
	}
	template<typename I1>
	bool operator> (const random_access_iterator<I1>& lhs, const random_access_iterator<I1>& rhs) {
		return rhs < lhs;
	}
	template<typename I1>
	bool operator>= (const random_access_iterator<I1>& lhs, const random_access_iterator<I1>& rhs) {
		return !(lhs < rhs);
	}
	template<typename I1>
	bool operator<= (const random_access_iterator<I1>& lhs, const random_access_iterator<I1>& rhs) {
		return !(rhs < lhs);
	}

	template <typename I1, typename I2>
	typename random_access_iterator<I1>::difference_type
	operator- (const random_access_iterator<I1>& lhs , const random_access_iterator<I2>&rhs) {
		return lhs.base() - rhs.base();
	}

	template <typename It>
	random_access_iterator<It>
	operator+ (typename  random_access_iterator<It>::difference_type n, random_access_iterator<It> lhs) {
		lhs += n;
		return lhs;
	}


	//DIFFERENCE
	template <class It>
	int	operator- (const random_access_iterator<It>& a , const random_access_iterator<It>&b) {
		return &(*a) - &(*b);
	}

	template< class It >
	std::ostream &operator<<(std::ostream &out, const random_access_iterator<It> &value){
		out << value;
		return out;
	}
};
