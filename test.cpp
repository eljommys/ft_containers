#include "map.hpp"
#include <map>

int main() {
	ft::map<int, int> a = ft::map<int, int>();

	ft::map<int, int>::iterator it = a.insert(ft::pair<int, int>(1, 1)).first;

	std::cout << (*it).first << std::endl;

	return 0;
}
