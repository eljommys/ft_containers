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

#ifndef SHOW
# define SHOW 1
#endif

void	compare(){
	std::string res = exec("diff results/stan.txt results/mine.txt");
	if (res.length()){
		std::cout << "< reference" << std::endl;
		std::cout << "> mine" << std::endl;
		std::cout << "\u274C" << std::endl;
		std::cout << res << std::endl;
	}
	else
		std::cout << "\u2705" << std::endl;
}

int main() {

	std::cout << "╔════════════════════╗" << std::endl;
	std::cout << "║ ft_containers test ║" << std::endl;
	std::cout << "╚════════════════════╝" << std::endl;

	std::vector<int> his_vct;
	ft::vector<int> my_vct;

	std::cout << "push back " << 20 << std::endl;
	for (int i = 0; i < 20; i++){
		his_vct.push_back(i); my_vct.push_back(i);
	}

	vector_output(my_vct); vector_output(his_vct);
	compare();

	std::cout << std::endl;

	for (int i = 0; i < 2; i++){
		his_vct.pop_back(); my_vct.pop_back();
		std::cout << "pop back" << std::endl;
	}
	vector_output(my_vct); vector_output(his_vct);
	compare();

	std::cout << std::endl;

	std::cout << "erase 3" << std::endl;
	his_vct.erase(his_vct.begin() + 3); my_vct.erase(my_vct.begin() + 3);
	vector_output(his_vct); vector_output(my_vct);
	compare();

	std::cout << "insert in 3, 14" << std::endl;
	his_vct.insert(his_vct.begin() + 2, 14); my_vct.insert(my_vct.begin() + 2, 14);
	vector_output(his_vct); vector_output(my_vct);
	compare();

	return 0;
}
