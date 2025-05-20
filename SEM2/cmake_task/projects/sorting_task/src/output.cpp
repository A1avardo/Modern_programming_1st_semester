#include <iostream>
#include "output.hpp"
 
void OutArr::print_arr(int* arr, const int& n) {
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}