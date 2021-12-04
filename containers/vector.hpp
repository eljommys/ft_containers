#pragma once

#include "../ft.hpp"

namespace ft
{
	template <class T>
	struct vector_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {

		//CONSTRUCTOR
		vector_iterator() : _ptr(NULL){}
		vector_iterator(pointer _val) : _ptr(_val) {}
		template<class U>
		vector_iterator(const vector_iterator<U>& other): _ptr(*other){}
		template<class U>
		vector_iterator& operator=(const vector_iterator<U>& other){_ptr = *other; return *this;}
		~vector_iterator() {};

		//EQUIVALENCE COMPARISONS
		template<class I1, class I2>
		bool operator==(const vector_iterator<I1>& _lhs, const vector_iterator<I2>& _rhs) const {
			return (*_lhs == *_rhs);
		}
		template<class I1, class I2>
		bool operator!=(const vector_iterator<I1>& _lhs, const vector_iterator<I2>& _rhs) const {
			return (*_lhs != *_rhs);
		}

		//DEREFERENCE
		pointer &operator*() const {return _ptr}
		pointer operator->() const {return _ptr}
		
		//INCREMENT
		vector_iterator &operator++(){_ptr++; return *this;}
		vector_iterator operator++(int){vector_iterator tmp(*this); _ptr++; return tmp;}

		//DECREMENT
		vector_iterator &operator--(){_ptr--; return *this;}
		vector_iterator operator--(int){vector_iterator tmp(*this); _ptr--; return tmp;}

		//ARITHMETIC
		vector_iterator operator+( difference_type n ) const { return vector_iterator(_ptr + n); }
		vector_iterator operator-( difference_type n ) const { return vector_iterator(_ptr - n); }

		//EQUAL ARITHMETIC
		vector_iterator& operator+=( difference_type n ) { _ptr += n; return *this; }
		vector_iterator& operator-=( difference_type n ) { _ptr -= n; return *this; }

		//OFFSET DEREFERENCE
		pointer *operator[](difference_type n) const { return _ptr + n; }

		private:
			pointer _ptr;
	};

	template < class T, class Alloc = std::allocator<T> >
	class vector{
		public:
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef Alloc allocator_type;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		typedef ft::vector_iterator<value_type> iterator;
		typedef const ft::vector_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef const ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ft::iterator_traits<iterator>::difference_type difference_type;
		typedef std::size_t size_type;

		//CONSTRUCTORS
		vector() : _array(NULL), _size(0){}
		explicit vector(	const allocator_type& _alloc = allocator_type()) :
							_array(NULL),
							_size(0){}

		explicit vector(	size_type _count,
							const T& _value = T(),
							const allocator_type& _alloc = allocator_type()) :
							_size(0),
							_array(new value_type[_count]){}

		template< class InputIt >
		vector(	InputIt _first, InputIt _last, 
				const allocator_type& _alloc = allocator_type() ) :
				_size(_last - _first){
			_array = new value_type[_size];
			for (size_type i = 0; i < _size; i++){
				_array[i] = _first;
				_first++;
			}
		}

		vector(	const vector& _other ) :
				_size(_other.size()),
				array(new value_type[_other.size()]){
			for (size_type i = 0; i < _other.size(); i++)
				_array[i] = _other[i];
		}

		//DESTRUCTOR
		~vector() {
			delete[] _array;
		}

		//OPERATOR OVERLOADS
		vector	&operator=(const vector &_other) {
			_size = other.size();

			delete[] _array;
			_array = new value_type[_size];
			for (size_type i = 0; i < _size; i++)
				_array[i] = _other[i];
			return *this;
		}

		//ASSIGN
		void assign( size_type _count, const T& _value ){
			delete[] _array;
			_size = _count;

			_array = new value_type[_size];
			for (size_type = 0; i < _size; i++)
				_array[i++] = _value;
		}

		template< class InputIt >
		void assign( InputIt _first, InputIt _last ){
			delete[] _array;
			_size = _last - _first;
			_array = new value_type[_size];
			for (size_type i = 0; i < _size; i++){
				_array[i] = _first;
				_first++;
			}
		}

		allocator_type get_allocator() const {return allocator_type;}

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
		iterator begin() {return iterator<value_type>(_array[0]);}
		const_iterator begin() const {return iterator<value_type>(_array[0]);}

		//END
		iterator end() {return iterator<value_type>(_array[_size]);}
		const_iterator end() const {return iterator<value_type>(_array[_size]);}

		//RBEGIN
		reverse_iterator rbegin() {return reverse_iterator<value_type>(begin());}
		const_reverse_iterator rbegin() const {return reverse_iterator<value_type>(begin());}

		//REND
		reverse_iterator rend() {return reverse_iterator<value_type>(end());}
		const_reverse_iterator rend() const {return reverse_iterator<value_type>(end());}

		bool empty() const {return (begin() == end());}
		size_type size() const {return _size;}
		size_type max_size() const {return std::distance(begin(), end());}

		void reserve(size_type _new_cap){
			if (_new_cap <= _capacity)
				return ;
			if (_new_cap > max_size())
				throw std::length_error;
			_capacity = _new_cap;
			_array = realloc(_array, _capacity);
		}

		size_type capacity() const {return _capacity;}
		void clear() {delete[] _array; _size = 0;}

		//INSERT
		iterator insert( iterator pos, const T& value ) {
			for (size_type i = _size - 1; pos <= i ; i--) //TODO: gestionar capacity (puede dar seg fault todavia)
				_array[i + 1] = _array[i];
			_array[pos - begin()] = value;
			_size++;
		}

		private:
		size_type	_capacity;
		size_type	_size;
		pointer		_array;
	};

};

//TODO: usar std::alocator en lugar de new y delete