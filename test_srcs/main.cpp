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
		std::cout << "\u2705";
}

int main() {

	std::cout << "╔════════════════════╗" << std::endl;
	std::cout << "║ ft_containers test ║" << std::endl;
	std::cout << "╚════════════════════╝" << std::endl;

	std::vector<int> his_vct;
	ft::vector<int> my_vct;

	ft::vector<int> tmp_my_vct;
	std::vector<int> tmp_his_vct;

	std::cout << "push back " << 20 << std::endl;
	for (int i = 0; i < 20; i++){
		his_vct.push_back(i); my_vct.push_back(i);
	}

	vector_output(my_vct); vector_output(his_vct);
	compare();

	std::cout << std::endl;

	std::cout << "pop back" << std::endl;
	for (int i = 0; i < 2; i++){
		his_vct.pop_back(); my_vct.pop_back();
		vector_output(my_vct); vector_output(his_vct);
		compare();
	}
	std::cout << std::endl;

	std::cout << "erase 3" << std::endl;
	his_vct.erase(his_vct.begin() + 3); my_vct.erase(my_vct.begin() + 3);
	vector_output(his_vct); vector_output(my_vct);
	compare();
	std::cout << std::endl;

	std::cout << "insert in 14 in 3" << std::endl;
	his_vct.insert(his_vct.begin() + 16, 14); my_vct.insert(my_vct.begin() + 16, 14);
	vector_output(his_vct); vector_output(my_vct);
	compare();
	his_vct.insert(his_vct.begin() + 16, 14); my_vct.insert(my_vct.begin() + 16, 14);
	vector_output(his_vct); vector_output(my_vct);
	compare();
	std::cout << std::endl;

	std::cout << "swap" << std::endl;
	for (int i = 20; 0 > i; i--){
		tmp_my_vct.push_back(i); tmp_his_vct.push_back(i);
	}
	tmp_my_vct.swap(my_vct); tmp_his_vct.swap(his_vct);
	vector_output(tmp_his_vct); vector_output(tmp_my_vct);
	compare();
	vector_output(his_vct); vector_output(my_vct);
	compare();
	std::cout << std::endl;

	std::cout << "operator=" << std::endl;
	tmp_his_vct = his_vct; tmp_my_vct = my_vct;
	vector_output(tmp_my_vct); vector_output(tmp_his_vct);
	compare();
	vector_output(my_vct); vector_output(his_vct);
	compare();
	std::cout << std::endl;

	return 0;
}
