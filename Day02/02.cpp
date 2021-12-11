#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include "02_2.h"

int main() {
	std::string line;
	std::ifstream file("02.txt");
	std::vector<int> position = { 0, 0 };

	while (std::getline(file, line)) {
		std::string instruction = line.substr(0, line.find(" "));
		int instrAmplitude = std::stoi(line.substr(line.find(" ")));
		std::cout << instruction << " " << instrAmplitude << std::endl;

		if (instruction == "forward") {
			position[0] += instrAmplitude;
		} else if (instruction == "up") {
			position[1] -= instrAmplitude;
		} else if (instruction == "down") {
			position[1] += instrAmplitude;
		}

		std::cout << "Updated position: (" << position[0] << ";" << position[1] << ")" << std::endl;
	}

	std::cout << std::endl << std::endl << "Final position multiplied: " << position[0] * position[1] << std::endl;
	std::cout << "To run second part press enter:" << std::endl;
	getchar();

	secondPart();

	return 0;
}