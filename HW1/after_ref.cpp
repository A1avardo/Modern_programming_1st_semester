#include <iostream>

int main() {

	std::setlocale(LC_ALL, "rus");
	const int arr_size = 10;
	int arr[arr_size];
	std::cout << "������� ������ �� 10 ���������"<<std::endl;
	for (int i = 0; i < arr_size; i++) {
		std::cout << "������� " << i + 1 << " ������� �������: ";
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
		std::cout << "������������������ ����������";
	}
	else {
		std::cout << "������������������ �� ����������";
	}

}