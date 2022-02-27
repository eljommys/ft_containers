#pragma once

#include "ft.hpp"

namespace ft {

	template<typename T>
	struct Node {
		private:
			bool				_aux; //boolean to subtract from max size in allocator

		public :
			typedef T			value_type;
			value_type			content;
			Node*				parent;
			Node*				right;
			Node*				left;

		Node(T const & _v , Node *_node) :
			content(_v),
			parent(_node),
			right(_node),
			left(_node){}

		Node(Node const &other) :
			content(other.content),
			parent(other.parent),
			right(other.right),
			left(other.left){}

		~Node(){}
	};

	template<typename T, typename Compare, typename Allocator>
	class tree {

		public:
		typedef T  															value_type;
		typedef Compare														value_compare;
		typedef Allocator  													allocator_type;
		typedef ft::Node<T>   												node_type;

		typedef typename Allocator::template rebind<node_type>::other		node_allocator;
		typedef typename node_allocator::pointer							pointer;
		typedef typename node_allocator::const_pointer						const_pointer;
		typedef typename node_allocator::reference							reference;
		typedef typename node_allocator::const_reference					const_reference;

		typedef typename ft::tree_iterator<pointer, value_type>				iterator;
		typedef typename ft::tree_iterator<const_pointer, const value_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>  					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		typedef typename allocator_type::size_type							size_type;
		typedef typename allocator_type::difference_type					differences_type;

		private:
		pointer									_origin;
		pointer									_none;
		pointer									_end;
		size_type								_size;
		value_compare							_comp;
		node_allocator							_allocator;

		tree(const tree& other);

		tree& operator= (const tree& other);

		size_type& __size() { return _size; }
		const size_type& __size() const { return _size; }

		void _none_reset() const {
			_none->parent = _none;
			_none->right = _origin;
			_none->left = _origin;
			_origin->parent = _none;
		}

		pointer _predecesor (pointer _ptr) {
			if (_ptr->left != _none) {
				_ptr = _ptr->left;
				while (_ptr->right != _none)
					_ptr = _ptr->right;
				return _ptr;
			}
			while (_ptr == _ptr->parent->left)
				_ptr = _ptr->parent;
			return _ptr->parent;
		}

		pointer _find (value_type const & _v) {
			pointer aux = _origin;

			while (aux != _none) {
				if (_comp(aux->content, _v))
					aux = aux->right;
				else if (_comp(_v, aux->content))
					aux = aux->left;
				else
					return aux;
			}
			return aux;
		}

		const_pointer _find (value_type const & _v) const {
			pointer aux = _origin;

			while (aux != _none) {
				if (_comp(aux->content, _v))
					aux = aux->right;
				else if (_comp(_v, aux->content))
					aux = aux->left;
				else
					return aux;
			}
			return _none ;
		}

		template <typename S>
		void _swap(S &a, S  &b) {
			S	c;

			c = a;
			a = b;
			b = c;
		}

		ft::pair<pointer, bool>	__treeLeaf (value_type const & _v, pointer _ptr) {
			while (true) {
				if (_comp(_ptr->content, _v)) {
					if (_ptr->right == _none)
						break;
					_ptr = _ptr->right;
				} else if (_comp(_v, _ptr->content)) {
					if (_ptr->left == _none)
						break ;
					_ptr = _ptr->left;
				} else
					return ft::make_pair(_ptr, false);
			}
			return ft::make_pair(_ptr, true);
		}

		pointer _create_node(const value_type & _v) {
			pointer tmpNode = node_allocator().allocate(1);

			node_allocator().construct(tmpNode, node_type(_v , _none));
			__size()++;
			return tmpNode;
		}

		pointer _create_node(const value_type & _v, pointer _ptr) {
			pointer tmpNode = node_allocator().allocate(1);

			node_allocator().construct(tmpNode, node_type(_v , _none));
			tmpNode->parent = _ptr;
			__size()++;
			return tmpNode;
		}

		void _destroy_node(pointer _ptr) {
			node_allocator().destroy(_ptr);
			node_allocator().deallocate(_ptr, 1);
		}

		void _destroy_tree(pointer _ptr) {
			if (_ptr != _none) {
				_destroy_tree(_ptr->left);
				_destroy_tree(_ptr->right);
				_destroy_node(_ptr);
			}
		}

		public:
		explicit tree (const value_compare & _comp = value_compare(),
						const allocator_type & _alloc = allocator_type()) :
						_end(ft::nullptr_t),
						_comp(_comp),
						_allocator(_alloc) {
			_size = 0;
			_none = node_allocator().allocate(1);
			node_allocator().construct(_none, node_type(value_type(), _none));
			_none->parent = _none;
			_none->right = _none;
			_none->left = _none;
			_end = _none;
			_origin = _none;
		}

		~tree() {
			_destroy_tree(_origin);
			_destroy_node(_none);
		}


		iterator		begin() {
			pointer aux = _origin;

			while (aux->left != _none)
				aux = aux->left;
			return iterator(aux, _none);
		}
		const_iterator	begin() const {
			pointer aux = _origin;

			while (aux->left != _none)
				aux = aux->left;
			return const_iterator(aux, _none);
		}

		iterator				end() {  return iterator(_none, _none); }
		const_iterator			end() const { return const_iterator(_none , _none); }

		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }

		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

		ft::pair<iterator, bool> insert (value_type const & _v) {
			if (_origin == _none) {
				_origin = _create_node(_v);
				_none_reset();
				return ft::make_pair(iterator(_origin, _none), true);
			} else {
				ft::pair<pointer, bool> __checkLeaf = __treeLeaf(_v, _origin);

				if (__checkLeaf.second) {
					if (_comp(__checkLeaf.first->content, _v)) {
						__checkLeaf.first->right = _create_node(_v, __checkLeaf.first);
						__checkLeaf.first = __checkLeaf.first->right;
					} else if (_comp(_v,__checkLeaf.first->content)) {
						__checkLeaf.first->left= _create_node(_v, __checkLeaf.first);
						__checkLeaf.first = __checkLeaf.first->left;
					}
					_none_reset();
					return ft::make_pair(iterator(__checkLeaf.first, _none), true);
				}
				_none_reset();
				return ft::make_pair(iterator(__checkLeaf.first, _none), false);
			}
		}

		void remove (const value_type & _v) {
			pointer ptr = _find(_v);
			pointer father = (ptr->left == _none || ptr->right == _none) ?
								ptr : _predecesor (ptr);
			pointer child  = father->left != _none ? father->left : father->right;
			pointer uncle = _none;

			if (child != _none)
				child->parent = father->parent;

			if (father == father->parent->left) {
				father->parent->left = child;
				if (father != _origin)
					uncle = father->parent->right;
				else
					_origin = child;
			} else {
				father->parent->right = child;
				uncle = father->parent->left;
			}

			if (father != ptr) {
				father->parent = ptr->parent;
				if (ptr == ptr->parent->left)
					father->parent->left = father;
				else
					father->parent->right = father;
				father->left = ptr->left;
				father->left->parent = father;
				father->right = ptr->right;
				if (father->right != _none)
					father->right->parent = father;
				if (_origin == ptr)
					_origin = father;
			}
			_destroy_node(ptr);
			_none_reset();
			__size()--;
		}

		size_type size() const { return _size ; }

		iterator find (value_type const & _v) { return iterator (_find(_v), _none); }

		const_iterator find (value_type const & _v) const { return const_iterator (_find(_v), _none); }

		value_compare value_comp() const  { return _comp; }

		size_type max_size() const {
			return node_allocator().max_size();
		}

		bool empty() const { return (__size()) ? false : true; }

		allocator_type get_allocator() const { return node_allocator(); }

		void clear() {
			_destroy_tree(_origin);
			__size() = 0;
			_origin = _none;
		}

		void	swap(tree& _other) {
			_swap(_origin, _other._origin);
			_swap(_size, _other._size);
			_swap(_none, _other._none);
			_swap(_end, _other._end);
			_swap(_allocator, _other._allocator);
			_swap(_comp, _other._comp);
		}
	};
}
