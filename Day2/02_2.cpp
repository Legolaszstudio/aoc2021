#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include "02_2.h"

int secondPart() {
	std::string line;
	std::ifstream file("02.txt");
	std::vector<int> position = { 0, 0, 0 };
	// X Y AIM

	while (std::getline(file, line)) {
		std::string instruction = line.substr(0, line.find(" "));
		int instrAmplitude = std::stoi(line.substr(line.find(" ")));
		std::cout << instruction << " " << instrAmplitude << std::endl;

		if (instruction == "forward") {
			position[0] += instrAmplitude;
			position[1] += position[2] * instrAmplitude;
		} else if (instruction == "up") {
			position[2] -= instrAmplitude;
		} else if (instruction == "down") {
			position[2] += instrAmplitude;
		}

		std::cout << "Updated vector: (" << position[0] << ";" << position[1] << ";" << position[2] << ")" << std::endl;
	}

	std::cout << std::endl << std::endl << "Final position multiplied: " << position[0] * position[1] << std::endl;

	return 0;
}