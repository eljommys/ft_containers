#pragma once

#include "includes/ft.hpp"

namespace ft {

	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map {
		public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<key_type, mapped_type>				value_type;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef typename Allocator::reference				reference;
		typedef typename Allocator::const_reference			const_referece;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef ft::bidirectional_iterator<pointer>			iterator;
		typedef const ft::bidirectional_iterator<pointer>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef const ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		class value_compare {
			public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			friend class map<key_type, mapped_type, key_compare, allocator_type>;

			bool operator()( const value_type& lhs, const value_type& rhs ) const {
				return _comp(lhs.first, rhs.first);
			}

			protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {}
		};

		//CONSTRUCTORS
		map() :
				_allocator(Allocator()),
				_comp(Compare()),
				_tree(NULL),
				_it(NULL) {}

		explicit map(	const Compare& comp,
						const Allocator& alloc = Allocator() ) :
				_allocator(alloc),
				_comp(comp),
				_tree(NULL),
				_it(NULL) {}

		template< class InputIt >
		map(InputIt first, InputIt last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator() ) :
				_comp(comp),
				_allocator(alloc){
			size_type dist = std::distance(first, last);
			for (; first != last; first++)
				insert(*first);
		}

		map( const map& other ) : _comp(other._comp), _allocator(other._allocator){}

		~map() {}

		/*map& operator=( const map& other ) {}

		//GET_ALLOCATOR
		allocator_type get_allocator() const {}

		//OPERATOR[]
		T& operator[]( const Key& key ) {}

		//BEGIN
		iterator begin() {}
		const_iterator begin() const {}

		//END
		iterator end() {}
		const_iterator end() const {}

		//RBEGIN
		reverse_iterator rbegin() {}
		const_reverse_iterator rbegin() const {}

		//REND
		reverse_iterator rend() {}
		const_reverse_iterator rend() const {}

		//EMPTY
		bool empty() const {}

		//SIZE
		size_type size() const {}

		//MAX_DISTANCE
		size_type max_size() const {}

		//CLEAR
		void clear() {}*/

		//INSERT
		ft::pair<iterator,bool> insert( const value_type& value ) {
			if (!_tree) {
				_tree = new ft::Tree<pointer>;
				_tree->prev = NULL;
				_tree->val = new value_type;
				*(_tree->val) = value;
				_tree->right = NULL;
				_tree->left = NULL;
			}

			ft::Tree<pointer>	*node = _tree;
			while (true) {
				if (_comp(value.first, node->val.first)) {
					if (!node->left) {
						node->left = new ft::Tree<pointer>;
						node->left->prev = node;
						node->left->val = _allocator.allocate(1);
						*(node->left->val) = value;
						node->left->left = NULL;
						node->left->right = NULL;
						return make_pair<iterator, bool>(iterator(node->left, true));
					}
					else
						node = node->left;
				} else if (_comp(node->val.first, value.first)) {
					if (!node->right) {
						node->right = new ft::Tree<pointer>;
						node->right->prev = node;
						node->right->val = _allocator.allocate(1);
						*(node->right->val) = value;
						node->right->left = NULL;
						node->right->right = NULL;
						return make_pair<iterator, bool>(iterator(node->right, true));
					}
					else
						node = node->left;
				} else
					return make_pair<iterator, bool>(iterator(node), false);
			}
		}

		/*iterator insert( iterator hint, const value_type& value ) {}
		template< class InputIt >
		void insert( InputIt first, InputIt last );

		//ERASE
		void erase( iterator pos ) {}
		void erase( iterator first, iterator last ) {}
		size_type erase( const key_type& key ) {}

		//SWAP
		void swap( map& other ) {}

		//COUNT
		size_type count( const Key& key ) const {}

		//FIND
		iterator find( const Key& key ) {}
		const_iterator find( const Key& key ) const {}

		//EQUAL_RANGE
		ft::pair<iterator,iterator> equal_range( const Key& key ) {}
		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {}

		//LOWER_BOUND
		iterator lower_bound( const Key& key ) {}
		const_iterator lower_bound( const Key& key ) const {}

		//UPPER_BOUND
		iterator upper_bound( const Key& key ) {}
		const_iterator upper_bound( const Key& key ) const {}

		//KEY_COMP
		key_compare key_comp() const {}
		ft::map::value_compare value_comp() const {}*/

		private:
		allocator_type		_allocator;
		key_compare			_comp;
		ft::Tree<pointer>	*_tree;
		iterator			_it;
	};
};
