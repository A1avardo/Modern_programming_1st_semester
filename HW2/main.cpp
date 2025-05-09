#include <iostream>
#include "sorting.hpp"
#include "output.hpp"

int main() {

	int arr[] = {5, 3, 8, 1, 2};
	const int n = sizeof(arr) / sizeof(arr[0]);

	Sorting::BubbleSort(arr, n);
	OutArr::print_arr(arr, n);

	return 0;
}
