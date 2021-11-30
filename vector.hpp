/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:55:52 by marvin            #+#    #+#             */
/*   Updated: 2021/11/28 17:55:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "iterators/iterators.hpp"

namespace ft {

	template<
		class T,
		class Allocator = std::allocator<T>
	> class vector {
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = Allocator::reference;
		using pointer = Allocator::pointer;
		using const_pointer = Allocator::const_pointer;
		using iterator = std::iterator;
		using reverse_iterator = ft::reverse_iterator<iterator>;

		vector() {}
		explicit vector(const Allocator& alloc);
		explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) {

		}
	};

	template<class Allocator>
	class vector<bool, Allocator> {

	};
}
