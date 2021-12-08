#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include <iostream>
#include<cmath>

void partTwo(std::vector<int> crabs, int maxPos);

int sumX(int until) {
	return (std::pow(until, 2) + until) / 2;
}

int main() {
	std::string line;
	std::ifstream file("07.txt");
	std::vector<int> crabs = {};
	int maxPos = 0;

	while (std::getline(file, line, ',')) {
		int crabPos = std::stoi(line);
		crabs.push_back(crabPos);
		if (crabPos > maxPos) {
			maxPos = crabPos;
		}
	}

	int smallestFuelConsumption = 0;
	int smallestFuelConsumptionIndex = 0;
	for (int testPos = 0; testPos <= maxPos; testPos++) {
		int currentFuelConsumption = 0;
		for (int i = 0; i < crabs.size(); i++) {
			currentFuelConsumption += abs(testPos - crabs[i]);
		}
		std::cout << "Fuel consumption at position " << testPos << " is " << currentFuelConsumption << std::endl;
		if (testPos == 0 || currentFuelConsumption < smallestFuelConsumption) {
			smallestFuelConsumption = currentFuelConsumption;
			smallestFuelConsumptionIndex = testPos;
		}
	}

	std::cout << std::endl << "Smallest fuel consumption was at " << smallestFuelConsumptionIndex << " with " << smallestFuelConsumption << " used fuel." << std::endl;
	
	std::cout << "To run second part press enter:" << std::endl << std::endl;
	getchar();
	partTwo(crabs, maxPos);
	return 0;
}

void partTwo(std::vector<int> crabs, int maxPos) {
	int smallestFuelConsumption = 0;
	int smallestFuelConsumptionIndex = 0;
	for (int testPos = 0; testPos <= maxPos; testPos++) {
		int currentFuelConsumption = 0;
		for (int i = 0; i < crabs.size(); i++) {
			currentFuelConsumption += sumX(abs(testPos - crabs[i]));
		}
		std::cout << "Fuel consumption at position " << testPos << " is " << currentFuelConsumption << std::endl;
		if (testPos == 0 || currentFuelConsumption < smallestFuelConsumption) {
			smallestFuelConsumption = currentFuelConsumption;
			smallestFuelConsumptionIndex = testPos;
		}
	}
	std::cout << std::endl << "Smallest fuel consumption was at " << smallestFuelConsumptionIndex << " with " << smallestFuelConsumption << " used fuel." << std::endl;
}