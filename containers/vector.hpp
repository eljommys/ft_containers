#pragma once

#include "../ft.hpp"

namespace ft
{
	template <	typename T, typename Distance = ptrdiff_t,
				typename Pointer = T*, typename Reference = T&>
	struct vector_iterator{

		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef typename ft::random_access_iterator_tag	iterator_category;

		//CONSTRUCTOR
		vector_iterator() : _ptr(NULL){}
		vector_iterator(pointer _val) : _ptr(_val) {}
		template<class U>
		vector_iterator(const vector_iterator<U>& other): _ptr(*other){}
		template<class U>
		vector_iterator& operator=(const vector_iterator<U>& other){_ptr = *other; return *this;}
		~vector_iterator() {};


		//DEREFERENCE
		pointer &operator*() const {return _ptr;}
		pointer operator->() const {return _ptr;}

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

	//EQUIVALENCE COMPARISONS
	template<class I1, class I2>
	bool operator==(const vector_iterator<I1>& _lhs, const vector_iterator<I2>& _rhs) {
		return (*_lhs == *_rhs);
	}
	template<class I1, class I2>
	bool operator!=(const vector_iterator<I1>& _lhs, const vector_iterator<I2>& _rhs) {
		return (*_lhs != *_rhs);
	}


	template < class T, class Alloc = std::allocator<T> >
	class vector{
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::vector_iterator<value_type> iterator;
		typedef const ft::vector_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef const ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		private:
		size_type	_capacity;
		size_type	_size;
		pointer		_array;

		public:
		//CONSTRUCTORS
		//vector() : _array(NULL), _size(0), _capacity(0){}
		explicit vector(	const allocator_type& _alloc = allocator_type()) :
							_array(NULL),
							_capacity(0),
							_size(0){}

		explicit vector(	size_type _count,
							const T& _value = T(),
							const allocator_type& _alloc = allocator_type()) :
							_size(_count),
							_capacity(_count * 2){
			try{
				_array = allocator_type.allocate(_capacity);
			} catch (std::bad_alloc &e) {
				std::cerr << e.what() << std::endl;
				_size = 0;
				_capacity = 0;
				return ;
			}
		}

		template< class InputIt >
		vector(	InputIt _first, InputIt _last,
				const allocator_type& _alloc = allocator_type() ) :
				_size(_last - _first),
				_capacity(_size * 2){
			try{
				_array = allocator_type.allocate(_capacity);
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
		}

		vector(	const vector& _other ) :
				_size(_other.size()),
				_capacity(_other.capacity()){
			try{
				_array = allocator_type.allocate(_other.size());
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
			if (_array && _capacity)
				allocator_type::deallocate(_array);
		}

		//OPERATOR OVERLOADS
		vector	&operator=(const vector &_other) {
			size_type	new_size = _other.size();
			size_type	new_capacity = _other.capacity();
			pointer		new_array;

			try{
				new_array = allocator_type.allocate(new_capacity);
			} catch (std::bad_alloc &e) {
				std::cerr << e.what() << std::endl;
				return *this;
			}

			if (_array && new_capacity != _capacity)
				allocator_type::deallocate(_array, new_capacity);
			_array = new_array;
			_size = new_size;
			_capacity = new_capacity;

			for (size_type i = 0; i < _size; i++)
				_array[i] = _other[i];
			return *this;
		}

		//ASSIGN
		void assign( size_type _count, const T& _value ){

			size_type new_size = _size + _count;
			size_type new_capacity = _capacity;
			pointer new_array;

			if (new_size >= new_capacity) {
				new_capacity *= 2;
				try{
					new_array = allocator_type.allocate(new_capacity);
				} catch (std::bad_alloc &e) {
					std::cerr << e.what() << std::endl;
					return;
				}
			}

			if (_array && new_capacity != _capacity)
				allocator_type::deallocate(_array, _capacity);
			_array = new_array;
			_size = new_size;
			_capacity = new_capacity;

			for (size_type i = 0; i < _size; i++)
				_array[i++] = _value;
		}

		template< class InputIt >
		void assign( InputIt _first, InputIt _last ){
			size_type new_size = _last - _first;
			size_type new_capacity = _capacity;
			pointer new_array;

			if (new_size >= new_capacity) {
				new_capacity *= 2;
				try{
					new_array = allocator_type.allocate(new_capacity);
				} catch (std::bad_alloc &e) {
					std::cerr << e.what() << std::endl;
					return ;
				}
			}

			if (_array && new_capacity != _capacity)
				allocator_type::deallocate(_array, _capacity);
			_array = new_array;
			_size = new_size;
			_capacity = new_capacity;

			for (size_type i = 0; i < _size; i++){
				_array[i] = _first;
				_first++;
			}
		}

		allocator_type get_allocator() const {return allocator_type();}

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
		iterator begin() {return iterator(_array[0]);}
		const_iterator begin() const {return iterator(_array[0]);}

		//END
		iterator end() {return iterator(_array[_size]);}
		const_iterator end() const {return iterator(_array[_size]);}

		//RBEGIN
		reverse_iterator rbegin() {return reverse_iterator(begin());}
		const_reverse_iterator rbegin() const {return reverse_iterator(begin());}

		//REND
		reverse_iterator rend() {return reverse_iterator(end());}
		const_reverse_iterator rend() const {return reverse_iterator(end());}

		bool empty() const {return (begin() == end());}
		size_type size() const {return _size;}
		size_type max_size() const {return std::distance(begin(), end());}

		//RESERVE
		void reserve(size_type _new_cap){
			if (_new_cap <= _capacity)
				return ;
			if (_new_cap > max_size())
				throw std::length_error();

			pointer new_array;
			try {
				new_array = allocator_type.allocate(_new_cap);
			} catch (std::bad_alloc &e) {
				throw e;
				return;
			}

			for (size_type i = 0; i < _size; i++)
				new_array[i] = _array[i];
			if (_array && _new_cap != _capacity)
				allocator_type::deallocate(_array);
			_array = new_array;
		}

		size_type capacity() const {return _capacity;}
		void clear() {erase(begin(), end());}

		//INSERT
		iterator insert( iterator pos, const T& value ) {
			size_type	new_size = _size + 1;
			size_type	new_capacity = _capacity;
			pointer		new_array = _array;

			if (new_size >= new_capacity) {
				new_capacity *= 2;
				try {
					new_array = allocator_type.allocate(new_capacity);
				} catch (std::bad_alloc &e) {
					std::cerr << e.what() << std::endl;
					return iterator();
				}
				for (size_type i = 0; i < _size; i++)
					new_array[i] = _array[i];
			}

			_size = new_size;
			_capacity = new_capacity;
			if (_array && new_capacity != _capacity)
				allocator_type::deallocate(_array);
			_array = new_array;

			for (iterator i = end(); pos < i ; i--)
				_array[i] = _array[i - 1];
			_array[pos] = value;
		}

		//ERASE
		iterator erase( iterator pos ) {		//TODO: gestionar iteradores no validos, probablemente de leaks
			iterator ret(*pos);

			for (pos; pos < end(); pos++)
				_array[pos] = _array[pos + 1];
			_size--;
			*pos = NULL;
			return ret;
		}

		iterator erase( iterator first, iterator last ) {
			iterator ret(*first);

			for(first; first < last; first++)
				_array[first] = _array[first + 1];
			_size -= last - first;
			*first = NULL;
			*last = NULL;
			return ret;
		}

		//PUSH BACK
		void push_back( const T& value ) {		//TODO: gestionar iteradores no validos
			size_type	new_size = _size + 1;
			size_type	new_capacity = _capacity;
			pointer		new_array = _array;

			if (new_size >= new_capacity){
				new_capacity *= 2;
				try {
					new_array = allocator_type.allocate(new_capacity);
				} catch (std::bad_alloc &e)  {
					std::cerr << e.what() << std::endl;
					return ;
				}
				for (size_type i = 0; i < _size; i++)
					new_array[i] = _array[i];
			}

			if (_array && new_capacity != _capacity)
				allocator_type::deallocate(_array);
			_size = new_size;
			_capacity = new_capacity;

			_array[_size - 1] = value;
		}

		//POP BACK
		void pop_back() {
			if (!_size)
				return ;
			_size--;
			_array[size] = NULL;
		}

		//RESIZE
		void resize( size_type count, T value = T() ){ //TODO: posiblemente haya que gestionar count > _cappacity
			for (size_type i = 0; i < _size; i++)
				_array[i] = value;
			_size = count;
		}

		void swap( vector& other ) {
			value_type aux;
			size_type i;

			for (i = 0; i < _size && i < other.size(); i++){
				aux = _array[i];
				_array[i] = other[i];
				other[i] = aux;
			}
			if (i > _size && i < other.size()){
				while (i < other.size()){
					push_back(other[i]);
					other[i] = NULL;
				}
			} else if (i > other.size() && i < _size){
				while (i < _size) {
					other.push_back(_array[i]);
					_array[i] = NULL;
				}
			}
		}

		//NON MEMBER FUNCTIONS
	};
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

//TODO: reimplementar NULL (NULL es de C++11)
