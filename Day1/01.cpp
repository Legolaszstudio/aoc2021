// Advent Of Code 2021.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>

int main() {
	std::string line;
	std::ifstream file("01.txt");

	int i = 0;
	int numBefore{};
	int counter = 0;
	int sumCounter = 0;
	std::deque<int> numbers = {};
	while (std::getline(file, line)) {
		if (i == 0) {
			line = line.substr(3);
		}
		int number = std::stoi(line);
		numbers.push_back(number);
		if (numbers.size() > 4) {
			numbers.pop_front();
		}

		std::cout << number << std::endl;
		if (number > numBefore && i != 0) {
			counter++;
		}

		if (i > 2) {
			int currentSum = 0;
			int sumBefore = 0;
			for (size_t index = 0; index < 4; index++) {
				if (index == 3) {
					currentSum += numbers[index];
				} else if (index == 0) {
					sumBefore += numbers[index];
				} else {
					currentSum += numbers[index];
					sumBefore += numbers[index];
				}
			}
			if (currentSum > sumBefore) {
				sumCounter++;
			}
			std::cout << "Sum: " << currentSum << std::endl;
		}

		numBefore = number;
		i++;
	}

	std::cout << std::endl << "Simple counter:  " << counter << std::endl;
	std::cout << "Sum counter:  " << sumCounter << std::endl;
	return 0;
}