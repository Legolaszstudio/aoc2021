#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <deque>
#include <unordered_map>
void partTwo(std::string polymer, std::unordered_map<std::string, std::string> bindings);

int calculateSolutionPartOne(std::string& inp) {
	std::unordered_map<char, long long> charCount = {};
	for (int i = 0; i < inp.size(); i++) {
		charCount[inp[i]] += 1;
	}
	long long smallest = 0xfffffffffffffff;
	long long biggest = 0;
	for (const auto& item : charCount) {
		if (item.second < smallest) {
			smallest = item.second;
		}
		if (item.second > biggest) {
			biggest = item.second;
		}
	}
	return biggest - smallest;
}

int main() {
	std::string line;
	std::ifstream file("14.txt");
	std::string polymer = "";
	bool isMappingLoading = false;
	std::unordered_map<std::string, std::string> bindings = {};
	while (std::getline(file, line)) {
		if (isMappingLoading) {
			int arrowIndex = line.find('-');
			std::string from = line.substr(0, arrowIndex - 1);
			std::string to = line.substr(arrowIndex + 3, line.size() - 1);
			bindings[from] = to;
		} else {
			if (line == "") {
				isMappingLoading = true;
			} else {
				polymer = line;
			}
		}
	}
	std::string originalInput = polymer;

	// Part1 bruteforce iterating everything
	for (int step = 0; step < 10; step++) {
		int polymerSize = polymer.size();
		int inserts = 0;
		for (int i = 0; i < polymerSize - 1; i++) {
			std::string checking = std::string(1, polymer[i + inserts]) + std::string(1, polymer[i + inserts + 1]);
			if (bindings.count(checking) > 0) {
				polymer.insert(i + inserts + 1, bindings[checking]);
				inserts++;
			}
		}
		//std::cout << "After step " << step + 1 << " : " << polymer << std::endl;
	}

	long long solution = calculateSolutionPartOne(polymer);
	std::cout << "Solution after 10 steps: " << solution << std::endl;
	partTwo(originalInput, bindings);
	return 0;
}

/*----------------------------------------------------------------------------------------------------*/
// Part2 is a little more conscious

long long calculateSolutionPartTwo(std::unordered_map<std::string, long long> inp) {
	std::unordered_map<char, long long> charCount = {};
	for (const auto& pair : inp) {
		charCount[pair.first[0]] += pair.second;
	}
	long long smallest = 0xfffffffffffffff;
	long long biggest = 0;
	for (const auto& item : charCount) {
		if (item.second < smallest) {
			smallest = item.second;
		}
		if (item.second > biggest) {
			biggest = item.second;
		}
	}
	return (biggest - smallest) + 1;
}

void partTwo(std::string polymer, std::unordered_map<std::string, std::string> bindings) {
	std::unordered_map<std::string, long long> current, next;

	// Add initial items to current
	for (int i = 0; i < polymer.size() - 1; i++) {
		std::string pair = std::string(1, polymer[i]) + std::string(1, polymer[i + 1]);
		current[pair]++;
	}

	for (int i = 0; i < 40; i++) {
		for (const auto& pair : current) {
			std::string replacement = bindings[pair.first];

			next[pair.first[0] + replacement] += pair.second;
			next[replacement + pair.first[1]] += pair.second;
		}
		current = next;
		next.clear();
	}

	long long solution = calculateSolutionPartTwo(current);
	std::cout << "Solution after 40 steps: " << solution << std::endl;
}