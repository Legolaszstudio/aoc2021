#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
	std::string line;
	std::ifstream file("11.txt");
	std::vector<std::vector<int>> originalInput = {};
	while (std::getline(file, line)) {
		originalInput.push_back({});
		for (int i = 0; i < line.size(); i++) {
			int num = std::stoi(std::string(1,line[i]));
			originalInput[originalInput.size() - 1].push_back(num);
		}
	}

	for (int step = 0; step < 100; step++) {
		
	}
	return 0;
}