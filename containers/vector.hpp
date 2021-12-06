#pragma once

#include "../ft.hpp"

namespace ft
{
	template <	typename T, typename Distance = ptrdiff_t,
				typename Pointer = T*, typename Reference = T&>
	struct random_access_iterator{

		typedef T																	iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference				reference;

		//CONSTRUCTOR
		random_access_iterator() : _ptr(NULL){}
		random_access_iterator(pointer _val) : _ptr(_val) {}
		template<class U>
		random_access_iterator(const random_access_iterator<U>& other): _ptr(*other){}
		template<class U>
		random_access_iterator& operator=(const random_access_iterator<U>& other){_ptr = *other; return *this;}
		~random_access_iterator() {};


		//DEREFERENCE
		reference operator*() const {return *_ptr;}
		pointer operator->() const {return _ptr;}

		//INCREMENT
		random_access_iterator &operator++(){_ptr++; return *this;}
		random_access_iterator operator++(int){random_access_iterator tmp(*this); _ptr++; return tmp;}

		//DECREMENT
		random_access_iterator &operator--(){_ptr--; return *this;}
		random_access_iterator operator--(int){random_access_iterator tmp(*this); _ptr--; return tmp;}

		//ARITHMETIC
		random_access_iterator operator+( difference_type n ) const { return random_access_iterator(_ptr + n); }
		random_access_iterator operator-( difference_type n ) const { return random_access_iterator(_ptr - n); }

		//EQUAL ARITHMETIC
		random_access_iterator& operator+=( difference_type n ) { _ptr += n; return *this; }
		random_access_iterator& operator-=( difference_type n ) { _ptr -= n; return *this; }

		//OFFSET DEREFERENCE
		pointer *operator[](difference_type n) const { return _ptr + n; }

		private:
			pointer _ptr;
	};

	//EQUIVALENCE COMPARISONS
	template<class I1, class I2>
	bool operator==(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (*_lhs == *_rhs);
	}
	template<class I1, class I2>
	bool operator!=(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (*_lhs != *_rhs);
	}
	template<class I1, class I2>
	bool operator<(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (&(*_lhs) < &(*_rhs));
	}
	template<class I1, class I2>
	bool operator>(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (&(*_lhs) > &(*_rhs));
	}
	template<class I1, class I2>
	bool operator<=(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (&(*_lhs) <= &(*_rhs));
	}
	template<class I1, class I2>
	bool operator>=(const random_access_iterator<I1>& _lhs, const random_access_iterator<I2>& _rhs) {
		return (&(*_lhs) >= &(*_rhs));
	}

	//DIFFERENCE
	template <class It>
	typename ft::random_access_iterator<It>::difference_type
	operator- ( const ft::random_access_iterator<It>& a , const ft::random_access_iterator<It>&b ) {
		return *a - *b;
	}


	template < class T, class Alloc = std::allocator<T> >
	class vector{
		public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef const ft::random_access_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef const ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		//CONSTRUCTORS
		vector() :	_capacity(0),
					_size(0),
					_array(NULL),
					_allocator(allocator_type()),
					_begin(NULL),
					_end(NULL){}
		explicit vector(	const allocator_type& _alloc) :
							_array(NULL),
							_capacity(0),
							_size(0),
							_allocator(_alloc),
							_begin(NULL),
							_end(NULL){}

		explicit vector(	size_type _count,
							const T& _value,
							const allocator_type& _alloc) :
							_capacity(_count),
							_size(_count),
							_allocator(_alloc),
							_begin(NULL),
							_end(NULL){
			try{
				_array = _allocator.allocate(_capacity + 1);
			} catch (std::bad_alloc &e) {
				std::cerr << e.what() << std::endl;
				_size = 0;
				_capacity = 0;
				return ;
			}

			for (size_type i = 0; i < _size; i++)
				_array[i] = _value;
			_array[_size] = NULL;
			_begin = iterator(_array);
			_end = iterator(&_array[_size]);
		}

		template< class InputIt >
		vector(	InputIt _first, InputIt _last,
				const allocator_type& _alloc) :
				_capacity(_size * 2),
				_size(_last - _first),
				_array(NULL),
				_begin(NULL),
				_end(NULL){
			try{
				_array = _alloc.allocate(_capacity + 1);
			} catch (std::bad_alloc &e) {
				std::cerr << e.what() << std::endl;
				_size = 0;
				_capacity = 0;
				return ;
			}
			for (size_type i = 0; i < _size; i++){
				_array[i] = _first;
				_first++;
			}
			_array[_size] = NULL;
			_begin = iterator(_array);
			_end = iterator(&_array[_size]);
		}

		vector(	const vector& _other ) :
				_capacity(_other.capacity()),
				_size(_other.size()),
				_array(NULL),
				_begin(NULL),
				_end(NULL){
			try{
				_array = _allocator.allocate(_other.size() + 1);
			} catch (std::bad_alloc &e) {
				_size = 0;
				_capacity = 0;
				std::cerr << e.what() << std::endl;
				return ;
			}
			for (size_type i = 0; i < _other.size(); i++)
				_array[i] = _other[i];
		}

		//DESTRUCTOR
		~vector() {
			if (_capacity) {
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(&_array[i]);
				_allocator.deallocate(_array, _capacity + 1);
			}
		}

		//OPERATOR OVERLOADS
		vector	&operator=(const vector &_other) {
			assign(_other.begin(), _other.end());
			return *this;
		}

		//ASSIGN
		void assign( size_type _count, const T& _value ){
			clear();
			_end = _begin;
			if (_count <= 0)
				return ;
			reserve(_count);
			for (size_type i = 0; i < _count; i++)
				push_back(_value);
		}

		template< class InputIt >
		void assign( InputIt _first, InputIt _last ){
			clear();
			for (; _first < _last; _first++)
				push_back(*_first);
		}

		allocator_type get_allocator() const {return _allocator;}

		//AT
		reference	at( size_type pos ) {return _array[pos];}
		const_reference at( size_type pos ) const {return _array[pos];}

		//DEREFERENCE OPERATOR
		reference	operator[](size_type pos) {return _array[pos];}
		const_reference operator[](size_type pos) const {return _array[pos];}

		//FRONT
		reference front() {_array[0];}
		const_reference front() const {_array[0];}

		//BACK
		reference back() {_array[_size - 1];}
		const_reference back() const {_array[_size - 1];}

		//BEGIN
		iterator begin() {return _begin;}
		const_iterator begin() const {return _begin;}

		//END
		iterator end() {return _end;}
		const_iterator end() const {return _end;}

		//RBEGIN
		reverse_iterator rbegin() {return reverse_iterator(begin());}
		const_reverse_iterator rbegin() const {return reverse_iterator(begin());}

		//REND
		reverse_iterator rend() {return reverse_iterator(end());}
		const_reverse_iterator rend() const {return reverse_iterator(end());}

		bool empty() const {return (begin() == end());}
		size_type size() const {return _size;}
		size_type max_size() const {return _allocator.max_size();}

		//RESERVE
		void reserve(size_type _new_cap){
			if (_new_cap <= _capacity)
				return ;
			if (_new_cap >= max_size())
				throw std::length_error("reserve");

			pointer new_array;
			try {
				new_array = _allocator.allocate(_new_cap + 1);
			} catch (std::bad_alloc &e) {
				throw e;
				return;
			}

			for (size_type i = 0; i < _size; i++)
				new_array[i] = _array[i];
			size_type old_size = _size;
			clear();
			_size = old_size;
			_capacity = _new_cap;
			_array = new_array;
			_begin = iterator(_array);
			_end = _begin + _size;
		}

		size_type capacity() const {return _capacity;}

		//CLEAR
		void clear() {
			if (!_size)
				return;
			erase(begin(), end());
		}

		//INSERT
		iterator insert( iterator pos, const T& value ) {
			//if (_size >)
			reserve();
		}

		//ERASE
		iterator erase( iterator pos ) {
			if (pos < begin() || end() <= pos) {
				throw std::length_error("iterator not in range");
				return (iterator(NULL));
			}
			_allocator.destroy(&(*pos));
			for (size_type i = pos - _begin; i < _size; i++)
				_array[i] = _array[i + 1];
			_size--;
			_end--;
			return pos;
		}

		iterator erase( iterator first, iterator last ) {
			if (first > last || first < begin() || end() < last) {
				throw std::length_error("iterator not in range");
				return (iterator(NULL));
			}
			iterator ret(first);
			size_type diff = last - first;

			for(; first < last; first++){
				_allocator.destroy(&(*first));
				*first = *(first + 1);
			}
			_size -= diff;
			_end -= diff;
			return ret;
		}

		//PUSH BACK
		void push_back( const T& value ) {
			size_type	new_size = _size + 1;
			size_type	new_capacity = _capacity;
			pointer		new_array = _array;

			if (new_size > new_capacity){
				new_capacity = _capacity + new_size;
				try {
					new_array = _allocator.allocate(new_capacity + 1);
				} catch (std::bad_alloc &e) {
					std::cerr << e.what() << std::endl;
					return ;
				}
				for (size_type i = 0; i < _size; i++) {
					new_array[i] = _array[i];
				}
				clear();
				_allocator.deallocate(_array, _capacity + 1);
			}

			_size = new_size;
			_capacity = new_capacity;
			_array = new_array;
			_array[_size - 1] = value;
			_begin = iterator(_array);
			_end = _begin + _size;
		}

		//POP BACK
		void pop_back() {
			if (!_size)
				return ;
			_size--;
			_allocator.destroy(&_array[_size]);
			_end--;
		}

		//RESIZE
		void resize( size_type count, T value = T() ){ //TODO: posiblemente haya que gestionar count > _cappacity
			for (size_type i = 0; i < _size; i++)
				_array[i] = value;
			_size = count;
			_allocator.destroy(_end);
			_end = _begin + _size;
		}

		void swap( vector& _other ) {
			pointer		tmp_arr;
			size_type	tmp_size;

			tmp_arr = _array;
			_other._array = _array;
			tmp_size = _size;

			_other._size = _size;
			_array = tmp_arr;
			_size = tmp_size;

			_other._begin = _other._array;
			_other._end = _other._begin + _other._size;

			_begin = _array;
			_end = _begin + _size;
		}

		private:
		size_type		_capacity;
		size_type		_size;
		pointer			_array;
		allocator_type	_allocator;
		iterator		_begin;
		iterator		_end;
	};

	//NON MEMBER FUNCTIONS
	template< class T, class Alloc >
	bool operator==(	const vector<T,Alloc>& lhs,
						const vector<T,Alloc>& rhs ) {
		if (lhs != rhs)
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template< class T, class Alloc >
	bool operator!=(	const vector<T,Alloc>& lhs,
						const vector<T,Alloc>& rhs ) {
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<(	const vector<T,Alloc>& lhs,
					const vector<T,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class T, class Alloc >
	bool operator<=(	const vector<T,Alloc>& lhs,
						const vector<T,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

	template< class T, class Alloc >
	bool operator>(	const vector<T,Alloc>& lhs,
					const vector<T,Alloc>& rhs ) {
		return (lhs < rhs);
	}

	template< class T, class Alloc >
	bool operator>=(	const vector<T,Alloc>& lhs,
						const vector<T,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

};

//TODO: reimplementar NULL (NULL es de C++11), implementar operador < en iterador
