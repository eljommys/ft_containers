#pragma once

#include "ft.hpp"

namespace ft {

template<typename Node, typename T>
class tree_iterator {

	public:
	typedef T													value_type;
	typedef typename std::bidirectional_iterator_tag			iterator_category;
	typedef typename ft::iterator_traits<Node>::value_type		node;
	typedef typename ft::iterator_traits<Node>::difference_type	difference_type;
	typedef typename ft::iterator_traits<Node>::pointer			node_pointer;
	typedef typename ft::iterator_traits<Node>::reference		node_reference;
	typedef value_type*											pointer;
	typedef value_type&											reference;

	protected:
	node_pointer ptr;
	node_pointer ptr_end;

	private:
	bool _is_left_child(node_pointer _node) {
		return _node == _node->parent->left;
	}

	node_pointer _get_min_child(node_pointer _node) const {
		while (_node->left != ptr_end)
			_node = _node->left;
		return _node;
	}

	node_pointer _get_max_child(node_pointer _node) const {
		while (_node->right != ptr_end)
			_node = _node->right;
		return _node;
	}

	public:
	~tree_iterator(){}

	tree_iterator() : ptr(), ptr_end() {}

	explicit tree_iterator(node_pointer ptr , node_pointer ptr_end) : ptr(ptr), ptr_end (ptr_end) {}

	template<typename NodePtr, typename S>
	tree_iterator (const tree_iterator<NodePtr, S> & other) :
		ptr(other.base()),
		ptr_end(other.end_base()) {}

	node_pointer base() const { return ptr; }

	node_pointer end_base() const { return ptr_end; }

	tree_iterator& operator=(const tree_iterator & other) {
		if (this != &other) {
			ptr = other.base();
			ptr_end = other.end_base();
		}
		return *this;
	}

	const node_pointer getNode() const {
		return ptr;
	}

	const node_pointer getEndNode() const {
		return ptr_end;
	}

	reference operator*() const { return ptr->content; }

	pointer operator->() const { return &ptr->content; }

	tree_iterator& operator++() {
		if (ptr->right != ptr_end)
			ptr = _get_min_child(ptr->right);
		else {
			while( !_is_left_child(ptr))
				ptr = ptr->parent;
			ptr = ptr->parent;
		}
		return *this;
	}

	tree_iterator operator++(int) {
		tree_iterator tmp(*this);
		operator++();
		return tmp;
	}

	tree_iterator& operator--() {
		if (ptr->left != ptr_end)
			ptr =  _get_max_child(ptr->left);
		else {
			while (_is_left_child(ptr))
				ptr = ptr->parent;
			ptr = ptr->parent;
		}
		return *this;
	}

	tree_iterator operator--(int) {
		tree_iterator tmp(*this);
		operator--();
		return tmp;
	}
};

	template <typename N1, typename T1, typename N2, typename T2>
	bool operator== (const ft::tree_iterator<N1, T1> lhs, const ft::tree_iterator<N2, T2> rhs) {
		return lhs.getNode() == rhs.getNode();
	}

	template <typename N1, typename T1, typename N2, typename T2>
	bool operator!= (const ft::tree_iterator<N1, T1> lhs, const ft::tree_iterator<N2, T2> rhs) {
		return !(lhs == rhs);
	}

	template <typename N1, typename T1,  typename N2, typename T2>
	bool operator<(const ft::tree_iterator<N1, T1> lhs, const ft::tree_iterator<N2, T2> rhs) {
		return lhs.getNode() <rhs.getNode();
	}

	template <typename N1, typename T1,  typename N2, typename T2>
	bool operator>= (const ft::tree_iterator<N1, T1> lhs, const ft::tree_iterator<N2, T2> rhs) {
		return !(lhs <rhs);
	}

	template <typename N1, typename T1,  typename N2, typename T2>
	bool operator> (const ft::tree_iterator<N1, T1> lhs, const ft::tree_iterator<N2, T2> rhs) {
		return rhs <lhs;
	}

	template <typename N1, typename T1,  typename N2, typename T2>
	bool operator<= (const ft::tree_iterator<N1, T1> lhs, const ft::tree_iterator<N2, T2> rhs) {
		return !(rhs <lhs);
	}

	template <typename N1, typename T1,  typename N2, typename T2>
	ptrdiff_t operator- (const ft::tree_iterator<N1, T1> lhs, const ft::tree_iterator<N2, T2> rhs) {
		return lhs.getNode() - rhs.getNode();
	}

	template <typename N, typename T>
	ptrdiff_t operator+ (typename ft::tree_iterator<N, T>::difference_type n, const ft::tree_iterator<N, T> lhs) {
		return (ft::tree_iterator<N,T>)(lhs.getNode() + n);
	}

}
