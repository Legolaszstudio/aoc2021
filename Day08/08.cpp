#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>
#include "08_02.h"

/*
	Digit Counts
	0 - 6
	1 - 2!
	2 - 5
	3 - 5
	4 - 4!
	5 - 5
	6 - 6
	7 - 3!
	8 - 7!
	9 - 6
*/

int main() {
	std::string line;
	std::ifstream file("08.txt");
	int counter = 0;

	while (std::getline(file, line)) {
		std::stringstream X(line);
		std::string content;
		int mainIndex = 0;
		while (std::getline(X, content, '|')) {
			if (mainIndex == 1) {
				std::string outString;
				std::stringstream Y(content);
				while (std::getline(Y, outString, ' ')) {
					if (outString != "") { 
						int strSize = outString.size();
						if (strSize == 2 || strSize == 4 || strSize == 3 || strSize == 7) counter++;
					}
				}
			}
			mainIndex++;
		}
	}

	std::cout << "Digits 1, 4, 7, or 8 appeared " << counter << " times." << std::endl;
	std::cout << "To run second part press enter:" << std::endl << std::endl;
	getchar();
	partTwo();
	return 0;
}