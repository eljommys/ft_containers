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

#include "test.hpp"

void	compare(){
	std::string res = exec("diff results/stan.txt results/mine.txt");
	if (res.length()){
		std::cout << "\u274C" << std::endl;
		std::cout << res.c_str() << std::endl;
	}
	else
		std::cout << "\u2705" << std::endl;
}

int main() {

	std::cout << "╔════════════════════╗" << std::endl;
	std::cout << "║ ft_containers test ║" << std::endl;
	std::cout << "╚════════════════════╝" << std::endl;

	std::vector<int> vct;

	for (int i = 0; i < 10; i++){
		vct.push_back(i); std::cout << "push back " << i << std::endl;
	}

	vector_output(vct);
	compare();

	std::cout << std::endl;

	for (int i = 0; i < 2; i++){
		vct.pop_back(); std::cout << "pop back" << std::endl;
	}
	vector_output(vct);

	std::cout << std::endl;

	vct.erase(vct.begin() + 3); std::cout << "erase 3" << std::endl;
	vector_output(vct);

	vct.insert(vct.begin() + 3, 14); std::cout << "insert in 3, 14" << std::endl;
	vector_output(vct);

	std::vector<int> tmp_vct = vct; std::cout << "tmp_vct = vct" << std::endl;
	vector_output(tmp_vct);


/*
	ft::vector<int> vct;

	for (int i = 0; i < 10; i++){
		vct.push_back(i); std::cout << "push back " << i << std::endl;
	}
	vector_output(vct);

	std::cout << std::endl;

	for (int i = 0; i < 2; i++){
		vct.pop_back(); std::cout << "pop back" << std::endl;
	}
	vector_output(vct);

	std::cout << std::endl;

	vct.erase(vct.begin() + 3); std::cout << "erase 3" << std::endl;
	vector_output(vct);

	vct.insert(vct.begin(), 14); std::cout << "insert in 3, 14" << std::endl;
	vector_output(vct);

	ft::vector<int> tmp_vct = vct; std::cout << "tmp_vct = vct" << std::endl;
	vector_output(tmp_vct); */

	return 0;
}
