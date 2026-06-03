#include <iostream>
#include <string>
#include <cmath>

#include <Windows.h>

int calculateLevel(int index) {
	return floor(log2(index + 1));
}

std::string calculateType(int index) {
	if (index == 0) return "root";
	if (index % 2 == 0) {
		return "right";
	}
	else {
		return "left";
	}
}

int calculateParentValue(int index, int* arr) {
	int parentIndex = (index - 1) / 2;
	return arr[parentIndex];
}

void updateCurrentElementInfo(int index, int* arr, int& level, std::string& type, int& parentValue) {
	level = calculateLevel(index);
	type = calculateType(index);
	parentValue = calculateParentValue(index, arr);
}

void printPyramidElementInfo(int level, std::string type, int parentValue, int currentValue) {
	std::cout << level << " " << type << "(" << parentValue << ") " << currentValue << "\n";
}

void printPyramid(int* arr, int size) {
	
	//print base array
	std::cout << "Исходный массив: ";
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i];
		if (i != size - 1)
			std::cout << " ";
	}
	std::cout << "\n";


	//print pyramid
	int level{}, parentValue{};
	std::string type{"root"};
	
	std::cout << "Пирамида:\n";
	for (int i = 0; i < size; ++i) {
		updateCurrentElementInfo(i, arr, level, type, parentValue);
		if (i == 0) {
			std::cout << level << " " << type << " " << arr[0] << "\n"; // root
			continue;
		}
		else {
			printPyramidElementInfo(level, type, parentValue, arr[i]);
		}
	}
}


//1 left(1) 3
//1 - уровень, left/right - сторона, (1) - это родитель, 3 - значение элемента

bool goToLeftChild(int size, int& currIndex) {
	int childIndex = 2 * currIndex + 1;
	if (childIndex < size) {
		currIndex = childIndex;
		return true;
	}
	else {
		return false;
	}
}

bool goToRightChild(int size, int& currIndex) {
	int childIndex = 2 * currIndex + 2;
	if (childIndex < size) {
		currIndex = childIndex;
		return true;
	}
	else {
		return false;
	}
}

bool goToParent(int* arr, int size, int& currIndex) {
	if (currIndex == 0) return false;
	else {
		currIndex = (currIndex - 1) / 2;
		return true;
	}	
}



void journeyInPyramid(int* arr, int size) {
	int currentIndex{}, currentLevel{}, currentParentValue{};
	std::string currentType{ "root" }, command{};
	do {
		std::cout << "Вы находитесь здесь: ";
		if (currentIndex == 0) {
			std::cout << currentLevel << " " << currentType << " " << arr[0] << "\n"; // root
		}
		else {
			printPyramidElementInfo(currentLevel, currentType, currentParentValue, arr[currentIndex]);
		}
		std::cout << "Введите команду: ";
		std::cin >> command;
		if (command == "right") {
			if (goToRightChild(size, currentIndex)) {
				std::cout << "Ок\n";
				updateCurrentElementInfo(currentIndex, arr, currentLevel, currentType, currentParentValue);
			}
			else {
				std::cout << "Ошибка! Отсутствует правый потомок\n";
			}
		}
		else if (command == "left") {
			if (goToLeftChild(size, currentIndex)) {
				std::cout << "Ок\n";
				updateCurrentElementInfo(currentIndex, arr, currentLevel, currentType, currentParentValue);
			}
			else {
				std::cout << "Ошибка! Отсутствует левый потомок\n";
			}
		}
		else if (command == "up") {
			if (goToParent(arr, size, currentIndex)) {
				std::cout << "Ок\n";
				updateCurrentElementInfo(currentIndex, arr, currentLevel, currentType, currentParentValue);
			}
			else {
				std::cout << "Ошибка! Отсутствует родитель\n";
			}
		}
		else {
			if (command != "exit") {
				std::cout << "Неизвестная команда. Введите, пожалуйста, верную: right, left, up или exit\n";
			}
		}
	} while (command != "exit");
}



int main() {
	SetConsoleOutputCP(1251);
	
	int array[6]{ 1, 3, 6, 5, 9, 8 };
	int array2[8]{ 94, 67, 18, 44, 55, 12, 6, 42 };
	int array3[10]{ 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
	printPyramid(array,6);
	/*std::cout << "\n\n";
	printPyramid(array2, 8);
	std::cout << "\n\n";
	printPyramid(array3, 10);*/
	journeyInPyramid(array, 6);

	return 0;
}
