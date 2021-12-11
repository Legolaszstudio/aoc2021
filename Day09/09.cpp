#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>
#include "09_2.h"

int main() {
	std::string line;
	std::ifstream file("09.txt");
	std::vector<std::vector<int>> inputMatrix = {};

	while (std::getline(file, line)) {
		inputMatrix.push_back({});
		int lastIndex = inputMatrix.size() - 1;
		for (int i = 0; i < line.size(); i++) {
			inputMatrix[lastIndex].push_back(std::stoi(std::string(1,line[i])));
		}
	}

	int riskLevel = 0;
	for (int i = 0; i < inputMatrix.size(); i++) {
		for (int j = 0; j < inputMatrix[i].size(); j++) {
			int currentNum = inputMatrix[i][j];
			if (i != 0) {
				// we can check upwards
				if (currentNum >= inputMatrix[i - 1][j]) {
					continue;
				}
			}
			if (i != inputMatrix.size() - 1) {
				// we can check downwards
				if (currentNum >= inputMatrix[i + 1][j]) {
					continue;
				}
			}
			if (j != 0) {
				// we can check left
				if (currentNum >= inputMatrix[i][j - 1]) {
					continue;
				}
			}
			if (j != inputMatrix[i].size() - 1) {
				// we can check right
				if (currentNum >= inputMatrix[i][j + 1]) {
					continue;
				}
			}
			std::cout << currentNum << " ";
			riskLevel += currentNum + 1;
		}
	}
	std::cout << std::endl << "Final risk level: " << riskLevel << std::endl;
	std::cout << "To run second part press enter:" << std::endl << std::endl;
	getchar();
	partTwo(inputMatrix);
	return 0;
}