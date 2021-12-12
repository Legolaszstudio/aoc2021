#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
struct Octopus {
	bool flashed = false;
	int num;
};
void flashOctopus(std::vector<std::vector<Octopus>>& input, int inputI, int inputJ);

void printMatrix(std::vector<std::vector<Octopus>>& input) {
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].size(); j++) {
			std::cout << input[i][j].num;
		}
		std::cout << std::endl;
	}
}
long long flashCount = 0;

int main() {
	std::string line;
	std::ifstream file("11.txt");
	std::vector<std::vector<Octopus>> originalInput = {};
	while (std::getline(file, line)) {
		originalInput.push_back({});
		for (int i = 0; i < line.size(); i++) {
			Octopus octo;
			octo.num = std::stoi(std::string(1, line[i]));
			octo.flashed = false;
			originalInput[originalInput.size() - 1].push_back(octo);
		}
	}
	std::vector<std::vector<Octopus>> workingMatrix = originalInput;

	for (int step = 0; step < 100; step++) {
		for (int i = 0; i < workingMatrix.size(); i++) {
			for (int j = 0; j < workingMatrix[i].size(); j++) {
				if(!workingMatrix[i][j].flashed) workingMatrix[i][j].num += 1;
				if (workingMatrix[i][j].num == 10) {
					workingMatrix[i][j].num = 0;
					workingMatrix[i][j].flashed = true;
					flashOctopus(workingMatrix, i, j);
				}
			}
		}
		//std::cout << "After step " << step + 1 << ":" << std::endl;
		//printMatrix(workingMatrix);
		for (int i = 0; i < workingMatrix.size(); i++) {
			for (int j = 0; j < workingMatrix[i].size(); j++) {
				workingMatrix[i][j].flashed = false;
			}
		}
		//std::cout << "There were a total of " << flashCount << " flashes so far" << std::endl;
		//std::cout << std::endl;
	}
	std::cout << "There were a total of " << flashCount << " flashes." << std::endl;
	return 0;
}

void flashOctopus(std::vector<std::vector<Octopus>>& input, int inputI, int inputJ) {
	++flashCount;
	if (inputI != 0) {
		//Top
		if (!input[inputI - 1][inputJ].flashed) input[inputI - 1][inputJ].num += 1;
		if (input[inputI - 1][inputJ].num == 10) {
			input[inputI - 1][inputJ].num = 0;
			input[inputI - 1][inputJ].flashed = true;
			flashOctopus(input, inputI - 1, inputJ);
		}
	}
	if (inputI != (input.size() - 1)) {
		//Bottom
		if (!input[inputI + 1][inputJ].flashed) input[inputI + 1][inputJ].num += 1;
		if (input[inputI + 1][inputJ].num == 10) {
			input[inputI + 1][inputJ].num = 0;
			input[inputI + 1][inputJ].flashed = true;
			flashOctopus(input, inputI + 1, inputJ);
		}
	}
	if (inputJ != 0) {
		//Left
		if (!input[inputI][inputJ - 1].flashed) input[inputI][inputJ - 1].num += 1;
		if (input[inputI][inputJ - 1].num == 10) {
			input[inputI][inputJ - 1].num = 0;
			input[inputI][inputJ - 1].flashed = true;
			flashOctopus(input, inputI, inputJ - 1);
		}
	}
	if (inputJ != (input[inputI].size() - 1)) {
		//Right
		if (!input[inputI][inputJ + 1].flashed) input[inputI][inputJ + 1].num += 1;
		if (input[inputI][inputJ + 1].num == 10) {
			input[inputI][inputJ + 1].num = 0;
			input[inputI][inputJ + 1].flashed = true;
			flashOctopus(input, inputI, inputJ + 1);
		}
	}

	if (inputI != 0 && inputJ != 0) {
		//Top left
		if (!input[inputI - 1][inputJ - 1].flashed) input[inputI - 1][inputJ - 1].num += 1;
		if (input[inputI - 1][inputJ - 1].num == 10) {
			input[inputI - 1][inputJ - 1].num = 0;
			input[inputI - 1][inputJ - 1].flashed = true;
			flashOctopus(input, inputI - 1, inputJ - 1);
		}
	}
	if (inputI != 0 && inputJ != (input[inputI].size() - 1)) {
		//Top right
		if (!input[inputI - 1][inputJ + 1].flashed) input[inputI - 1][inputJ + 1].num += 1;
		if (input[inputI - 1][inputJ + 1].num == 10) {
			input[inputI - 1][inputJ + 1].num = 0;
			input[inputI - 1][inputJ + 1].flashed = true;
			flashOctopus(input, inputI - 1, inputJ + 1);
		}
	}
	if (inputI != (input.size() - 1) && inputJ != 0) {
		//Bottom left
		if (!input[inputI + 1][inputJ - 1].flashed) input[inputI + 1][inputJ - 1].num += 1;
		if (input[inputI + 1][inputJ - 1].num == 10) {
			input[inputI + 1][inputJ - 1].num = 0;
			input[inputI + 1][inputJ - 1].flashed = true;
			flashOctopus(input, inputI + 1, inputJ - 1);
		}
	}
	if (inputI != (input.size() - 1) && inputJ != (input[inputI].size() - 1)) {
		//Bottom right
		if (!input[inputI + 1][inputJ + 1].flashed) input[inputI + 1][inputJ + 1].num += 1;
		if (input[inputI + 1][inputJ + 1].num == 10) {
			input[inputI + 1][inputJ + 1].num = 0;
			input[inputI + 1][inputJ + 1].flashed = true;
			flashOctopus(input, inputI + 1, inputJ + 1);
		}
	}
}