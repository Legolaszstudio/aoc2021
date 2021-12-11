#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include "09_2.h"
int releaseTheAnts(std::vector<std::vector<int>>& inputMatrix, int startI, int startJ);


void partTwo(std::vector<std::vector<int>> inputMatrix) {
	std::vector<long long> basins = {};
	for (int i = 0; i < inputMatrix.size(); i++) {
		for (int j = 0; j < inputMatrix[i].size(); j++) {
			if (inputMatrix[i][j] < 9) {
				long long result = releaseTheAnts(inputMatrix, i, j);
				basins.push_back(result);
			}
		}
	}
	std::cout << "There were over " << basins.size() << " basins." << std::endl;
	std::sort(basins.begin(), basins.end());
	long long one = basins[basins.size() - 1];
	long long two = basins[basins.size() - 2];
	long long three = basins[basins.size() - 3];
	std::cout << "There three biggest basins multiplied: " << one << " * " << two << " * " << three << " = " << one * two * three << std::endl;
}

int releaseTheAnts(std::vector<std::vector<int>>& inputMatrix, int startI, int startJ) {
	std::vector<int> currentLocation = { startI, startJ };
	std::deque<std::vector<int>> decisionMatrix = {};
	long long basinSize = 0;
	while (true) {
		inputMatrix[currentLocation[0]][currentLocation[1]] = 10;
		int top = 10;
		int bottom = 10;
		int left = 10;
		int right = 10;
		if (currentLocation[0] != (inputMatrix.size() - 1)) {
			bottom = inputMatrix[currentLocation[0] + 1][currentLocation[1]];
		}
		if (currentLocation[0] != 0) {
			top = inputMatrix[currentLocation[0] - 1][currentLocation[1]];
		}
		if (currentLocation[1] != (inputMatrix[currentLocation[0]].size() - 1)) {
			right = inputMatrix[currentLocation[0]][currentLocation[1] + 1];
		}
		if (currentLocation[1] != 0) {
			left = inputMatrix[currentLocation[0]][currentLocation[1] - 1];
		}

		if ((top < 9 && right < 9) ||
			(bottom < 9 && right < 9) ||
			(left < 9 && bottom < 9) ||
			(top < 9 && left < 9) ||
			(top < 9 && bottom < 9) ||
			(left < 9 && right < 9)) {
			//We have multiple options, lets come back later
			decisionMatrix.push_front({ currentLocation[0], currentLocation[1] });
		}

		if (bottom < 9) {
			//Let's go downward
			currentLocation[0] += 1;
			basinSize++;
			//std::cout << "I go down" << std::endl;
		} else if (right < 9) {
			//Let's go right
			currentLocation[1] += 1;
			basinSize++;
			//std::cout << "I go right" << std::endl;
		} else if (top < 9) {
			//Let's go up
			currentLocation[0] -= 1;
			basinSize++;
			//std::cout << "I go up" << std::endl;
		} else if (left < 9) {
			//Let's go left
			currentLocation[1] -= 1;
			basinSize++;
			//std::cout << "I go left" << std::endl;
		} else {
			//Stuck
			//std::cout << "I am stuck" << std::endl;
			if (decisionMatrix.size() == 0) {
				basinSize++;
				break;
			}
			currentLocation = decisionMatrix[0];
			decisionMatrix.erase(decisionMatrix.begin());
		}

	}
	std::cout << "Everything filled (" << basinSize << ")" << std::endl << std::endl;
	return basinSize;
}