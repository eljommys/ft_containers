#pragma once

#include "includes/ft.hpp"
#include "vector.hpp"

namespace ft {
	template< class T, class Container = ft::vector<T> >
	class stack {
		public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		explicit stack( const Container& cont = Container() ) : c(cont){}
		stack( const stack& other ) : c(other.c) {}
		~stack() {}

		stack& operator=( const stack& other ) {
			c = other.c;
			return *this;
		}

		//TOP
		reference top() {
			return c.back();
		}

		const_reference top() const {
			return c.back();
		}

		//EMPTY
		bool empty() const {
			if (c.size())
				return false;
			return true;
		}

		//SIZE
		size_type size() const {
			return c.size();
		}

		//PUSH
		void push( const value_type& value ) {
			return c.push_back(value);
		}

		//POP
		void pop() {
			c.pop_back();
		}

		template <typename T1, typename C1>
		friend bool operator==(	const stack<T1,C1>& lhs,
								const stack<T1,C1>& rhs );

		template <typename T1, typename C1>
		friend bool operator<(	const stack<T1,C1>& lhs,
								const stack<T1,C1>& rhs );

		template <typename T1, typename C1>
		friend void swap( stack<T1,C1>& lhs, stack<T1,C1>& rhs );

		private:
		container_type	c;
	};

	//NON MEMBER FUNCTIONS
	template< class T, class Container >
	bool operator==(const stack<T,Container>& lhs,
					const stack<T,Container>& rhs ) {
		return (lhs.c == rhs.c);
	}

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs,
					const stack<T,Container>& rhs ) {
		return !(lhs == rhs);
	}

	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs,
					const stack<T,Container>& rhs ) {
		return (lhs.c < rhs.c);
	}

	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs,
					const stack<T,Container>& rhs ) {
		return !(lhs < rhs);
	}

	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs,
					const stack<T,Container>& rhs ) {
		return (rhs < lhs);
	}

	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs,
					const stack<T,Container>& rhs ) {
		return !(rhs < lhs);
	}

	template< class T, class Container >
	void swap( stack<T,Container>& lhs, stack<T,Container>& rhs ) { //GESTIONAR EXCEPCIONES
		lhs.c.swap(rhs);
	}
}
