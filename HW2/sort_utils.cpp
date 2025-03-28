#include <iostream>

#include "sort_utils.hpp"


void Sorting::BubbleSort(int *arr, const int &n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}


void OutArr::print_arr(int *arr, const int &n) {
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}