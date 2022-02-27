#pragma once

namespace ft {

	template < class T1, class T2 >
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair()
			: first() , second() {};

		pair (first_type const& t1, second_type const& t2)
			: first(t1), second(t2){}

		template < class S1, class S2 >
		pair (const pair< S1, S2 > & other)
			: first(other.first) , second (other.second) {}

		pair& operator= (pair const& other) {
			first = other.first;
			second = other.second;
			return *this;
		}
	};

	//NON MEMBER FUNCIONS
	template <class T1, class T2>
	ft::pair < T1, T2 > make_pair(T1 lhs, T2 rhs) {
		return ft::pair< T1, T2 >(lhs, rhs);
	}

	template <class T1, class T2>
	bool operator== (const ft::pair < T1, T2 >& lhs, const ft::pair < T1, T2 > & rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!= (const ft::pair < T1, T2 >& lhs, const ft::pair < T1, T2 > & rhs) {
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator< (const ft::pair < T1, T2 >& lhs, const ft::pair < T1, T2 > & rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator>= (const ft::pair < T1, T2 >& lhs, const ft::pair < T1, T2> & rhs) {
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	bool operator> (const ft::pair < T1, T2 >& lhs, const ft::pair < T1, T2 > & rhs) {
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator<= (const ft::pair < T1, T2 >& lhs, const ft::pair < T1, T2> & rhs) {
		return !(rhs < lhs);
	}
}
