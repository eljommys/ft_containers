/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:39:19 by marvin            #+#    #+#             */
/*   Updated: 2021/11/28 16:39:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
//#include <map.hpp>
//#include <stack.hpp>

#include "ft.hpp"
#include "containers/vector.hpp"

template<typename T>
void	show_vector(ft::vector<T> vct){
	typedef typename ft::vector<T>::iterator	iterator;

	std::cout << "==========VECTOR============" << std::endl;
	std::cout << "size = " << vct.size() << std::endl;
	std::cout << "capacity = " << vct.capacity() << std::endl;
	std::cout << "[";
	for (iterator i = vct.begin(); i < vct.end(); i++)
		std::cout << *i << ",";
	std::cout << "]" << std::endl;
	std::cout << "============================" << std::endl;
}

int main() {

	ft::vector<int> vct;

	vct.push_back(1); std::cout << "push back 1" << std::endl;
	show_vector(vct);
	vct.push_back(2); std::cout << "push back 1" << std::endl;
	show_vector(vct);
}
