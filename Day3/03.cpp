#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include "03_2.h"

int main() {
	std::string line;
	std::ifstream file("03.txt");
	std::deque<std::string> inputs = {};
	bool isFirst = true;
	while (std::getline(file, line)) {
		inputs.push_back(line);
	}

	// Get gamma rate
	std::string gamRateString = "";
	for (size_t i = 0; i < inputs[0].length(); i++) {
		std::vector<int> zerosAndOnes = { 0, 0 };
		for (size_t j = 0; j < inputs.size(); j++) {
			if (inputs[j].at(i) == '0') {
				zerosAndOnes[0] += 1;
			} else {
				zerosAndOnes[1] += 1;
			}
		}
		std::cout << "0 and 1 count at " << i << ": " << zerosAndOnes[0] << " " << zerosAndOnes[1] << std::endl;
		if (zerosAndOnes[0] > zerosAndOnes[1]) {
			gamRateString += "0";
		} else {
			gamRateString += "1";
		}
	}
	int gammaRate = std::stoi(gamRateString, nullptr, 2);
	std::cout << "Gamma rate string: " << gamRateString << " (" << gammaRate << ")" << std::endl;

	// Epsilon rate is the opposite of gamma rate
	std::string epsilonRateString = "";
	for (size_t i = 0; i < gamRateString.length(); i++) {
		if (gamRateString[i] == '0') {
			epsilonRateString += "1";
		} else {
			epsilonRateString += "0";
		}
	}
	int epsilonRate = std::stoi(epsilonRateString, nullptr, 2);
	std::cout << "Epsilon rate string: " << epsilonRateString << " (" << epsilonRate << ")" << std::endl;
	std::cout << std::endl << "Final answer: " << epsilonRate * gammaRate << std::endl;

	std::cout << "To run second part press enter:" << std::endl << std::endl;
	getchar();

	secondPart(inputs);
	return 0;
}