#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include <iostream>

void partTwo(std::vector<int>);

//Part 1 only works with smaller numbers
int main() {
	std::string line;
	std::ifstream file("06.txt");
	std::vector<int> originalFishes = {};

	while (std::getline(file, line, ',')) {
		originalFishes.push_back(std::stoi(line));
	}
	std::vector<int> fishes = originalFishes;
	

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
	}
	std::cout << "After " << 80 << " days there will be " << fishes.size() << " fishes" << std::endl;

	std::cout << "To run second part press enter:" << std::endl << std::endl;
	getchar();
	partTwo(originalFishes);
	return 0;
}

void partTwo(std::vector<int> inp) {
	std::cout << inp.size();
	std::vector<long long> fishes = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	// Load initial values
	for (int i = 0; i < inp.size(); i++) {
		fishes[inp[i]]++;
	}
	// Iterate over days
	for (int i = 1; i <= 256; i++) {
		long long addFishCount = fishes[0];

		fishes[0] = fishes[1];
		fishes[1] = fishes[2];
		fishes[2] = fishes[3];
		fishes[3] = fishes[4];
		fishes[4] = fishes[5];
		fishes[5] = fishes[6];
		fishes[6] = fishes[7];
		fishes[7] = fishes[8];

		fishes[6] += addFishCount;
		fishes[8] = addFishCount;
	}

	std::cout << "After " << 256 << " days there will be ";
	long long sum = 0;
	for (int i = 0; i < fishes.size(); i++) {
		sum += fishes[i];
	}
	std::cout << sum << " fishes" << std::endl;
};