#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include <iostream>


//Part 1 only works with smaller numbers
int main() {
	std::string line;
	std::ifstream file("06.txt");
	std::vector<int> fishes = {};

	while (std::getline(file, line, ',')) {
		fishes.push_back(std::stoi(line));
	}

	for (int i = 1; i <= 80; i++) {
		int fishSize = fishes.size();
		for (int fishIndex = 0; fishIndex < fishSize; fishIndex++) {
			if (fishes[fishIndex] == 0) {
				fishes[fishIndex] = 6;
				fishes.push_back(8);
			} else {
				fishes[fishIndex] -= 1;
			}
		}
		std::cout << "After " << i << " days there will be " << fishes.size() << " fishes" << std::endl;
	}
	return 0;
}