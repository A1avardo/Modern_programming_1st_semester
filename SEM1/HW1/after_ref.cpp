include <iostream>

int main() {

	std::setlocale(LC_ALL, "rus");
	const int arr_size = 10;
	int arr[arr_size];
	std::cout << "Введите массив из 10 элементов"<<std::endl;
	for (int i = 0; i < arr_size; i++) {
		std::cout << "Введите" << i + 1 << " -ый элмент последовательности: ";
		std::cin >> arr[i];
	}

	bool increasing = true;
	int i = 0;
	while (i < arr_size - 1) {
		if (arr[i] > arr[i + 1]) {
			increasing = false;
			break;
		}
		i++;
	}

	if (increasing) {
		std::cout << "Последовательности возрастает";
	}
	else {
		std::cout << "Последовательность не возрастает";
	}

}