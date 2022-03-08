#pragma once

#include "includes/ft.hpp"

namespace ft {

	template<
		class Key,
		class T,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator< ft::pair< const Key, T > >
	>
	class map {
		public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Allocator								allocator_type;

		class value_compare {
			protected:
				key_compare comp;
			public:
				bool operator()(const value_type& lhs, const value_type& rhs) const {
					return comp(lhs.first, rhs.first);
				}
		};

		private:
		typedef ft::tree< value_type, value_compare, allocator_type >	base;

		base tree;
		ft::pair<key_compare, allocator_type>			comp_allocator;

		template < typename Sw >
		void swap(Sw &a, Sw  &b) {
			Sw  c;
			c = a;
			a = b;
			b = c;
		}

		public:
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	deifference_type;
		typedef typename base::iterator						iterator;
		typedef typename base::const_iterator 				const_iterator;
		typedef typename base::reverse_iterator				reverse_iterator;
		typedef typename base::const_reverse_iterator		const_reverse_iterator;

		//CONSTRUCTORS
		explicit map(const key_compare & comp = key_compare(),
					const allocator_type & alloc = allocator_type()) :
				tree(),
				comp_allocator(ft::make_pair(comp, alloc)) {}

		template <typename InputIt>
		map (InputIt  first, InputIt  last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if
			< !ft::is_integral<InputIt>::value, InputIt >::type * = ft::nullptr_t) :
				tree(),
				comp_allocator(ft::make_pair(comp, alloc)) {
			for (; first != last; ++first)
				tree.insert(*first);
		}

		map(const map& other) { *this = other; }

		//DESTRUCTOR
		~map() {}

		//OVERLOAD OPERATOR
		map& operator=(const map& other) {
			if (this != &other) {
				comp_allocator = other.comp_allocator;
				clear();
				insert(other.begin(), other.end());
			}
			return *this;
		}

		//GET ALLOCATOR
		allocator_type get_allocator() const { return tree.get_allocator(); }

		//BEGIN
		iterator				begin() { return tree.begin(); }
		const_iterator			begin() const { return tree.begin(); }
		reverse_iterator		rbegin() { return  tree.rbegin(); }
		const_reverse_iterator	rbegin() const { return tree.rbegin(); }

		//END
		iterator				end() { return tree.end(); }
		const_iterator			end() const { return tree.end(); }
		reverse_iterator		rend() { return  tree.rend(); }
		const_reverse_iterator	rend() const { return tree.end(); }

		//EMPTY
		bool empty() const { return tree.empty(); };

		//MAX_SIZE
		size_type max_size() const { return tree.max_size(); };

		//SIZE
		size_type size() const { return tree.size(); };

		//OPERATOR[] OVERLOAD
		mapped_type& operator[](const key_type& k) {
			iterator	hunt = find(k);

			if (hunt != end())
				return hunt->second;
			return (*insert(ft::make_pair(k, mapped_type())).first).second;
		}

		//INSERT
		ft::pair<iterator, bool> insert(const value_type& val) { return tree.insert(val); }
		iterator insert(iterator pos, const value_type& val) {
			static_cast< void >(pos);
			return tree.insert(val).first;
		}

		template <typename _InputIterator >
		void insert (	_InputIterator first,
						_InputIterator last,
						typename ft::enable_if
						< !ft::is_integral<_InputIterator>::value, _InputIterator >::type * = ft::nullptr_t) {
			for(; first != last; ++first)
				tree.insert(*first);
		}

		//FIND
		iterator		find(const key_type & key) { return tree.find(ft::make_pair(key, mapped_type())); }
		const_iterator	find(const key_type& key) const { return tree.find(ft::make_pair(key, mapped_type())); }

		//ERASE
		void erase (iterator pos) { tree.remove(*pos); }
		void erase(iterator first, iterator last) {
			for (; first != last;)
				tree.remove(*(first++));
		}

		size_type erase(const key_type & k) {
			iterator f = find(k);

			if (f != end()) {
				tree.remove(*f);
				return 1;
			}
			return 0;
		}

		//CLEAR
		void clear() { erase(begin(), end()); }

		//COUNT
		size_type count(const key_type & k) const { return (find(k) != end()) ? 1 : 0; }

		//KEY_COMPARE
		key_compare key_comp() const { return comp_allocator.first; };

		//VALUE_COMPARE
		value_compare value_comp() const { return tree.value_comp(); }

		//SWAP
		void swap(map& other) {
			swap(comp_allocator, other.comp_allocator);
			tree.swap(other.tree);
		}

		//LOWER_BOUND
		iterator lower_bound(const Key& k) {
			iterator first = begin();
			iterator last = end();

			for (; first != last; ++first)
				if (!comp_allocator.first((*first).first, k))
					break;
			return first;
		}

		const_iterator lower_bound (const Key& k) const {
			const_iterator first = begin();
			const_iterator last = end();

			for (; first != last; ++first)
				if (!comp_allocator.first((*first).first, k))
					break;
			return const_iterator(first);
		}

		//UPPER BOUND
		iterator upper_bound(const Key& k) {
			iterator first = begin();
			iterator last = end();

			for (; first != last; ++first)
				if (comp_allocator.first(k, (*first).first))
					break;
			return first;
		}

		const_iterator upper_bound (const Key& k) const {
			const_iterator first = begin();
			const_iterator last = end();

			for (; first != last; ++first)
				if (comp_allocator.first(k, (*first).first))
					break;
			return const_iterator(first);
		}

		//EQUAL_RANGE
		ft::pair<iterator, iterator> equal_range(const Key& k) { return ft::make_pair(lower_bound(k), upper_bound(k)); }
		ft::pair<const_iterator, const_iterator> equal_range(const Key& k) const { return ft::make_pair(lower_bound(k), upper_bound(k)); }
	};


	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator==(const ft::map<Key, T, Compare, Alloc > &x, const ft::map<Key, T, Compare, Alloc > &y) {
		return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator!=(const ft::map<Key, T, Compare, Alloc > &x, const ft::map<Key, T, Compare, Alloc > &y){
		return !(x == y);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator<(const ft::map<Key, T, Compare, Alloc > &x, const ft::map<Key, T, Compare, Alloc > &y){
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}
	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator>(const ft::map<Key, T, Compare, Alloc > &x, const ft::map<Key, T, Compare, Alloc > &y) {
		return y < x ;
	}
	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator>=(const ft::map<Key, T, Compare, Alloc > &x, const ft::map<Key, T, Compare, Alloc > &y) {
		return !(x < y) ;
	}
	template< typename Key, typename T, typename Compare, typename Alloc >
	bool operator<=(const ft::map<Key, T, Compare, Alloc > &x, const ft::map<Key, T, Compare, Alloc > &y) {
		return !(y < x) ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void swap(const ft::map<Key, T, Compare, Alloc > &x, const ft::map<Key, T, Compare, Alloc > &y) {
		return x.swap(y);
	}
}
