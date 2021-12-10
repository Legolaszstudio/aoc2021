#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>

int main() {
	std::string line;
	std::ifstream file("10.txt");

	int points = 0;
	while (std::getline(file, line)) {
		std::deque<char> requiredClosingTags = {};
		for(int i = 0; i < line.size(); i++) {
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
					break;
				} else {
					requiredClosingTags.erase(requiredClosingTags.begin());
				}
			}
		}
	}

	std::cout << "Final syntax error points: " << points;
	return 0;
}