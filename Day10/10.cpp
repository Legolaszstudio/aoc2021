#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
	std::string line;
	std::ifstream file("10.txt");

	int points = 0;
	std::vector<long long> syntaxErrorPoints = {};
	while (std::getline(file, line)) {
		std::deque<char> requiredClosingTags = {};
		for (int i = 0; i < line.size(); i++) {
			char currentTag = line[i];
			if (currentTag == '(') {
				requiredClosingTags.push_front(')');
			} else if (currentTag == '[') {
				requiredClosingTags.push_front(']');
			} else if (currentTag == '{') {
				requiredClosingTags.push_front('}');
			} else if (currentTag == '<') {
				requiredClosingTags.push_front('>');
			} else {
				if (requiredClosingTags[0] != currentTag) {
					if (currentTag == ')') {
						points += 3;
					} else if (currentTag == ']') {
						points += 57;
					} else if (currentTag == '}') {
						points += 1197;
					} else if (currentTag == '>') {
						points += 25137;
					}
					requiredClosingTags = {};
					break;
				} else {
					requiredClosingTags.erase(requiredClosingTags.begin());
				}
			}
		}
		long long closingTagPoints = 0;
		for (int i = 0; i < requiredClosingTags.size(); i++) {
			char closingTag = requiredClosingTags[i];
			if (closingTag == ')') {
				closingTagPoints = (closingTagPoints * 5) + 1;
			} else if (closingTag == ']') {
				closingTagPoints = (closingTagPoints * 5) + 2;
			} else if (closingTag == '}') {
				closingTagPoints = (closingTagPoints * 5) + 3;
			} else if (closingTag == '>') {
				closingTagPoints = (closingTagPoints * 5) + 4;
			}
		}
		if (closingTagPoints != 0) syntaxErrorPoints.push_back(closingTagPoints);
	}

	std::cout << "Final corrupted line points: " << points << std::endl;
	std::sort(syntaxErrorPoints.begin(), syntaxErrorPoints.end());
	std::cout << "Final incomplete lines points: " << syntaxErrorPoints[syntaxErrorPoints.size() / 2] << std::endl;
	return 0;
}