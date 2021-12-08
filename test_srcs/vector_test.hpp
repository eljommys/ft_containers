#pragma once

#include "test.hpp"

template<typename T>
void	vector_output(ft::vector<T> vct) {
	typedef typename ft::vector<T>::iterator	iterator;
	std::ofstream file("results/mine.txt", std::ios_base::trunc);

	file << "┌──────────VECTOR────────────┐" << std::endl;
	file << "├─" << "size = " << vct.size() << std::endl;
	file << "├─" << "capacity = " << vct.capacity() << std::endl;
	file << "├─" << "empty = " << vct.empty() << std::endl;
	//file << "├─" << "begin = " << &(*vct.begin()) << std::endl;
	//file << "├─" << "end = " << &(*vct.end()) << std::endl;
	file << "├─" << "[";
	for (iterator i = vct.begin(); i < vct.end(); i++) {
		file << *i;
		if (i + 1 < vct.end())
			file << ",";
	}
	file << "]" << std::endl;
	file << "└────────────────────────────┘" << std::endl;
	file.close();
}

template<typename T>
void	vector_output(std::vector<T> vct) {
	typedef typename std::vector<T>::iterator	iterator;
	std::ofstream file("results/stan.txt", std::ios_base::trunc);

	file << "┌──────────VECTOR────────────┐" << std::endl;
	file << "├─" << "size = " << vct.size() << std::endl;
	file << "├─" << "capacity = " << vct.capacity() << std::endl;
	file << "├─" << "empty = " << vct.empty() << std::endl;
	//file << "├─" << "begin = " << &(*vct.begin()) << std::endl;
	//file << "├─" << "end = " << &(*vct.end()) << std::endl;
	file << "├─" << "[";
	for (iterator i = vct.begin(); i < vct.end(); i++) {
		file << *i;
		if (i + 1 < vct.end())
			file << ",";
	}
	file << "]" << std::endl;
	file << "└────────────────────────────┘" << std::endl;
	file.close();
}
