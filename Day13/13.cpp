#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <deque>

int printMatrix(std::deque<std::deque<int>> inp, bool print) {
	int counter = 0;
	for (int i = 0; i < inp.size(); i++) {
		for (int j = 0; j < inp[0].size(); j++) {
			if (inp[i][j] == 0) {
				if (print) std::cout << ".";
			} else {
				if (print) std::cout << "#";
				counter++;
			}
		}
		if (print) std::cout << std::endl;
	}
	return counter;
}

int main() {
	std::string line;
	std::ifstream file("13.txt");
	bool isFoldInstruction = false;
	std::vector<std::vector<int>> points = {};
	std::vector<std::vector<int>> folds = {};
	std::vector<int> maxSize = { 0, 0 };
	while (std::getline(file, line)) {
		if (line == "") {
			isFoldInstruction = true;
		} else if (isFoldInstruction) {
			folds.push_back({});
			int equal = line.find('=');
			if (line[equal - 1] == 'x') {
				folds[folds.size() - 1].push_back(0);
			} else {
				folds[folds.size() - 1].push_back(1);
			}
			std::string foldSizeS = line.substr(equal+1);
			folds[folds.size() - 1].push_back(std::stoi(foldSizeS));
		} else {
			std::stringstream X(line);
			std::string numS;
			points.push_back({});
			while (std::getline(X, numS, ',')) {
				int instructionNum = points[points.size() - 1].size();
				int num = std::stoi(numS);
				points[points.size() - 1].push_back(num);
				if (maxSize[instructionNum] <= num) maxSize[instructionNum] = (num + 1);
			}
		}
	}
	std::deque<std::deque<int>> originalInput;
	std::deque<std::deque<int>> solveMatrix(maxSize[1], std::deque<int>(maxSize[0]));
	for (const auto& item : points) {
		solveMatrix[item[1]][item[0]] = 1;
	}
	originalInput = solveMatrix;

	// Start solving
	for (int foldI = 0; foldI < folds.size(); foldI++) {
		std::vector<int> currentFold = folds[foldI];
		int foldUntil = currentFold[1];
		if (currentFold[0] == 1) {
			// Fold along y axis
			std::deque<std::deque<int>> temp;
			int i = 0;
			while (i < foldUntil) {
				temp.push_back(solveMatrix[i]);
				i++;
			}
			i += 1;
			std::deque<std::deque<int>> tempTwo;
			while (i < solveMatrix.size()) {
				tempTwo.push_back(solveMatrix[i]);
				i++;
			}

			// You always have to fold up
			for (int i = 0; i < tempTwo.size(); i++) {
				for (int j = 0; j < tempTwo[0].size(); j++) {
					int tempIndex = temp.size() - i - 1;
					if (tempIndex >= 0) {
						if (tempTwo[i][j] == 1) {
							temp[tempIndex][j] = 1;
						}
					} else {
						temp.push_front(tempTwo[i]);
					}
				}
			}
			solveMatrix = temp;
		} else {
			// Fold along x axis
			std::deque<std::deque<int>> temp(solveMatrix.size(), std::deque<int>());
			int j = 0;
			while (j < foldUntil) {
				for (int i = 0; i < temp.size(); i++) {
					temp[i].push_back(solveMatrix[i][j]);
				}
				j++;
			}
			j += 1;
			std::deque<std::vector<int>> tempTwo(solveMatrix.size(), std::vector<int>());
			while (j < solveMatrix[0].size()) {
				for (int i = 0; i < tempTwo.size(); i++) {
					tempTwo[i].push_back(solveMatrix[i][j]);
				}
				j++;
			}
			std::cout << std::endl;
			// You always have to fold left
			for (int j = 0; j < tempTwo[0].size(); j++) {
				int tempIndex = temp[0].size() - j - 1;
				for (int i = 0; i < tempTwo.size(); i++) {
					if (tempIndex >= 0) {
						if (tempTwo[i][j] == 1) {
							temp[i][tempIndex] = 1;
						}
					} else {
						if (tempTwo[i][j] == 1) {
							temp[i].push_front(1);
						} else {
							temp[i].push_front(0);
						}
					}
				}
			}
			solveMatrix = temp;
		}

		if (foldI == 0) {
			int solution = printMatrix(solveMatrix, false);
			std::cout << "There were " << solution << " dots, after the first fold" << std::endl << std::endl;
		}
	}
	std::ofstream outputFile;
	outputFile.open("output.txt");
	for (int i = 0; i < solveMatrix.size(); i++) {
		for (int j = 0; j < solveMatrix[0].size(); j++) {
			if (solveMatrix[i][j] == 0) {
				outputFile << ".";
			} else {
				outputFile << "#";
			}
		}
		outputFile << "\n";
	}
	outputFile.close();
	std::cout << "Dumped part2 solution to output.txt" << std::endl;
	return 0;
}