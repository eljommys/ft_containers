#pragma once

#include "iterators/iterators.hpp"

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector{
		public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<pointer> iterator;
		typedef ft::random_access_iterator<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		//CONSTRUCTORS
		explicit vector(	const allocator_type& _alloc = allocator_type()) :
							_capacity(0),
							_size(0),
							_array(0),
							_allocator(_alloc),
							_begin(0),
							_end(0){}

		explicit vector(	size_type _count,
							const T& _value = value_type(),
							const allocator_type& _alloc = allocator_type()) :
							_capacity(0),
							_size(0),
							_allocator(_alloc),
							_begin(NULL),
							_end(NULL){
			_mod_capacity(_count);
			_size = _count;
			for (size_type i = 0; i < _size; i++){
				_array[i] = _value;
			}
			_end += _size;
		}

		template< class InputIt >
		vector(	InputIt _first, InputIt _last,
				const allocator_type& _alloc = allocator_type()) :
				_capacity(0),
				_size(0),
				_array(NULL),
				_allocator(_alloc),
				_begin(NULL),
				_end(NULL){
			size_type new_size = _distance(_first, _last);
			_mod_capacity(new_size);
			_size = new_size;
			for (size_type i = 0; i < _size; i++){
				_array[i] = *_first;
				_first++;
			}
			_end += _size;
		}

		vector(	const vector& _other ) :
				_capacity(0),
				_size(0),
				_array(NULL),
				_begin(NULL),
				_end(NULL){
			//std::cout << "despues" << std::endl;
			_mod_capacity(_other.capacity());
			for (size_type i = 0; i < _other.size(); i++)
				_array[i] = _other[i];
			_size = _other.size();
			_end +=_size;
		}

		//DESTRUCTOR
		~vector() {
			if (_array) {
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(&_array[i]);
				_allocator.deallocate(_array, _capacity);
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
		void assign(	InputIt _first, InputIt _last,
						typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = NULL){
			clear();

			size_type new_size = _distance(_first, _last);
			reserve(new_size);
			for (size_type i = 0; i < new_size; i++){
				push_back(*_first);
				_first++;
			}
		}

		allocator_type get_allocator() const {return _allocator;}

		//AT
		reference	at( size_type pos ) {
			if (pos >= _size)
				throw std::out_of_range("out of range");
			return _array[pos];
		}
		const_reference at( size_type pos ) const {
			if (pos >= _size)
				throw std::out_of_range("out of range");
			return _array[pos];
		}

		//DEREFERENCE OPERATOR
		reference	operator[](size_type pos) {return _array[pos];}
		const_reference operator[](size_type pos) const {return _array[pos];}

		//FRONT
		reference front() {return _array[0];}
		const_reference front() const {return _array[0];}

		//BACK
		reference back() {return _array[_size - 1];}
		const_reference back() const {return _array[_size - 1];}

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
			if (_new_cap > max_size())
				throw std::length_error("reserve");
			try {
				_mod_capacity(_new_cap);
			} catch (std::bad_alloc &e) {
				throw e;
			}
		}

		size_type capacity() const {return _capacity;}

		//CLEAR
		void clear() {
			if (!_array)
				return;
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(&(_array[i]));
			/* if (_array)
				_allocator.deallocate(_array, _capacity);
			_array = NULL; */
			_size = 0;
			//_capacity = 0;
			//_begin = iterator(NULL);
			_begin = iterator(_array);
			_end = _begin;
		}

		//INSERT
		iterator insert( iterator pos, const T& value ) { //TOOD: sustiuir contenido por la de abajo simplemente usando "count = 1"

			/* size_type s_pos = _distance(_begin, pos);
			try {
				reserve(_size + 1);
			} catch (std::bad_alloc &e) {
				std::cerr << e.what() << std::endl;
				return pos;
			}

			_size++;
			for (size_type i = _size; s_pos < i; i--)
				_array[i] = _array[i - 1];
			_array[s_pos] = value; */

			insert(pos, 1, value);

			return iterator(pos);
		}

		void insert( iterator pos, size_type count, const T& value ) {
			try {
				reserve(_size + count);
			} catch (std::bad_alloc &e) {
				std::cerr << e.what() << std::endl;
				return ;
			}

			_size += count;
			_end += count;
			size_type s_pos = (_array) ? _distance(_begin, pos) : 0;
			for (size_type i = _size - 1; s_pos + count - 1 < i; i--)
				_array[i] = _array[s_pos + count + i];
			for (size_type i = 0; i < count; i++)
				_array[s_pos + i] = value;
		}

		template< class InputIt >
		void insert(	iterator pos, InputIt first, InputIt last,
						typename ft::enable_if
						<
							!ft::is_integral<InputIt>::value, InputIt
						>::type * = NULL) {
			size_type count = _distance(first, last);
			size_type s_pos = _distance(_begin, pos);

			try {
				reserve(_size + count);
			} catch (std::bad_alloc &e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
			_size += count;
			_begin = iterator(_array);
			_end = _begin + _size;
			for (size_type i = _size; s_pos < i - count + 1; i--)
				_array[i] = _array[i - count + 1];
			for (size_type i = 0; i < count; i++){
				_array[s_pos + i] = *first;
				first++;
			}

			return ;
		}

		//ERASE
		iterator erase( iterator pos ) {
			try {
				pos = erase(pos, pos + 1);
			} catch (std::length_error &e) {
				throw e;
			}
			return pos;
		}

		iterator erase( iterator first, iterator last ) {
			if (first > last || first < begin() || end() < last) {
				throw std::length_error("iterator not in range");
				return (iterator(NULL));
			}
			size_type diff = _distance(first, last);
			size_type s_first = _distance(_begin, first);

			for(size_type i = s_first; i < _size; i++){
				_allocator.destroy(&_array[i]);
				_array[i] = _array[i + diff];
				_allocator.destroy(&_array[i + diff]);
			}
			_size -= diff;
			_end -= diff;
			return first;
		}

		//PUSH BACK
		void push_back( const T& value ) {

			if (_size + 1 > _capacity)
				_mod_capacity(_size + 1);
			_size++;
			_array[_size - 1] = value;
			_end++;
		}

		//POP BACK
		void pop_back() {
			if (!_size)
				return ;
			/* try {
				_mod_capacity(_capacity - 1);
			} catch (std::bad_alloc &e) {
				std::cerr << e.what() << std::endl;
				return ;
			} */
			_allocator.destroy(_array[_size - 1]);
			_size--;
			_end--;
		}

		//RESIZE
		void resize( size_type count, T value = T() ){ //TODO: posiblemente haya que gestionar count > _cappacity
			for (size_type i = 0; i < _size; i++)
				_array[i] = value;
			_size = count;
			//_allocator.destroy(_end);
			_end = _begin + _size;
		}

		void swap( vector& _other ) {
			pointer		tmp_arr;
			size_type	tmp_size;

			tmp_arr = _array;
			_array = _other._array;
			_other._array = tmp_arr;

			tmp_size = _size;
			_size = _other._size;
			_other._size = tmp_size;

			tmp_size = _capacity;
			_capacity = _other._capacity;
			_other._capacity = tmp_size;

			_begin = iterator(_array);
			_end = _begin + _size;

			_other._begin = iterator(_other._array);
			_other._end = _other._begin + _other._size;
		}

	private:
		size_type		_capacity;
		size_type		_size;
		pointer			_array;
		allocator_type	_allocator;
		iterator		_begin;
		iterator		_end;

		void			_mod_capacity(size_type new_capacity) {
			if (new_capacity <= 0 || new_capacity == _capacity)
				return ;

			pointer new_array;
			
			try {
				new_array = _allocator.allocate(new_capacity);
			} catch (std::bad_alloc &e) {
				throw e;
				return ;
			}
			//std::cout << "size = " << _size << std::endl;
			if (_array){
				_size = (new_capacity < _size) ? new_capacity : _size;
				for (size_type i = 0; i < _size; i++) {
					new_array[i] = _array[i];
					_allocator.destroy(&_array[i]);
				}
				_allocator.deallocate(_array, _capacity);
			}
			_array = new_array;
			_capacity = new_capacity;
			_begin = iterator(_array);
			_end = _begin + _size;
		}

		template<typename InputIt>
		size_type		_distance(	InputIt _first, InputIt _last){
			size_type i = 0;
			for (; _first != _last; _first++)
				i++;
			return i;
		}
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

