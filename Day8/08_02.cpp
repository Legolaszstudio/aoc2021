#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include "08_02.h"
const int MAX_CHAR = 26;

/*
	What you are about to see is chaotic, childish and was written by a noob...
	At first glance I felt like comparing differences between displays should be the easiest to make and understand...
	So I went with that idea, I commented the code throughout because even I couldn't remember what different code blocks were doing
*/

// Sort strings characters (stolen from geeksforgeeks)
std::string sortString(std::string& str) {
	int charCount[MAX_CHAR] = { 0 };

	for (int i = 0; i < str.length(); i++)
		charCount[str[i] - 'a']++;

	std::string output = "";
	for (int i = 0; i < MAX_CHAR; i++)
		for (int j = 0; j < charCount[i]; j++)
			output += (char)('a' + i);

	return output;
}

void partTwo() {
	std::string line;
	std::ifstream file("08.txt");
	int counter = 0;
	long long sumOut = 0;

	std::string one = "";
	std::string four = "";
	std::string seven = "";
	std::string eight = "";

	while (std::getline(file, line)) {
		std::stringstream X(line);
		std::string content;
		std::vector<std::string> numbers = {};
		std::vector<std::string> outputs = {};

		int index = 0;
		while (std::getline(X, content, '|')) {
			std::string outString;
			std::stringstream Y(content);
			while (std::getline(Y, outString, ' ')) {
				if (outString != "") {
					if (index == 0) {
						if (outString.size() == 2) {
							one = sortString(outString);
						} else if (outString.size() == 4) {
							four = sortString(outString);
						} else if (outString.size() == 3) {
							seven = sortString(outString);
						} else if (outString.size() == 7) {
							eight = sortString(outString);
						} else {
							numbers.push_back(sortString(outString));
						}
					} else {
						outputs.push_back(sortString(outString));
					}
				}
			}
			index++;
		}


		std::string six = "";
		std::string nine = "";
		std::string zero = "";
		int numSize = numbers.size();
		int dels = 0;
		for (size_t i = 0; i < numSize; i++) {
			if (numbers[i - dels].size() == 6) {
				// Nine, six or zero, lets decide
				if (numbers[i - dels].find(four[0]) == std::string::npos ||
					numbers[i - dels].find(four[1]) == std::string::npos ||
					numbers[i - dels].find(four[2]) == std::string::npos ||
					numbers[i - dels].find(four[3]) == std::string::npos) {
					// This is six or zero
					if (numbers[i - dels].find(seven[0]) == std::string::npos ||
						numbers[i - dels].find(seven[1]) == std::string::npos ||
						numbers[i - dels].find(seven[2]) == std::string::npos) {
						// 6 doesn't contain all digits of 7
						six = numbers[i - dels];
						if ((i - dels) == 0) numbers.erase(numbers.begin());
						else numbers.erase(std::next(numbers.begin(), i - dels));
						dels++;
					} else {
						// 0 contains all digits of 7
						zero = numbers[i - dels];
						if ((i - dels) == 0) numbers.erase(numbers.begin());
						else numbers.erase(std::next(numbers.begin(), i - dels));
						dels++;
					}
				} else {
					// If the number contains all digits of 4 and is 6segments than it must be 9
					nine = numbers[i - dels];
					if ((i - dels) == 0) numbers.erase(numbers.begin());
					else numbers.erase(std::next(numbers.begin(), i - dels));
					dels++;
				}
			}
			if (six != "" && zero != "" && nine != "") break;
		}


		// We have 2, 3 and 5 left
		// Only 3 contains all digits of 7
		std::string three = "";
		for (int i = 0; i < numbers.size(); i++) {
			if (!(numbers[i].find(seven[0]) == std::string::npos ||
				numbers[i].find(seven[1]) == std::string::npos ||
				numbers[i].find(seven[2]) == std::string::npos)) {
				three = numbers[i];
				if (i == 0) numbers.erase(numbers.begin());
				else numbers.erase(std::next(numbers.begin(), i));
				break;
			}
		}

		// 2 and 5 left
		std::string two = "";
		std::string five = "";
		int counter = 0;
		if (numbers[0].find(four[0]) == std::string::npos) {
			counter++;
		}
		if (numbers[0].find(four[1]) == std::string::npos) {
			counter++;
		}
		if (numbers[0].find(four[2]) == std::string::npos) {
			counter++;
		}
		if (numbers[0].find(four[3]) == std::string::npos) {
			counter++;
		}
		// If we compare five with four there should be one missing piece
		if (counter == 1) {
			five = numbers[0];
			two = numbers[1];
		} else {
			// If we compare two with four there should be two missing pieces
			five = numbers[1];
			two = numbers[0];
		}

		std::string displayOut = "";
		for (int i = 0; i < outputs.size(); i++) {
			if (outputs[i] == zero) {
				displayOut += "0";
			} else if (outputs[i] == one) {
				displayOut += "1";
			} else if (outputs[i] == two) {
				displayOut += "2";
			} else if (outputs[i] == three) {
				displayOut += "3";
			} else if (outputs[i] == four) {
				displayOut += "4";
			} else if (outputs[i] == five) {
				displayOut += "5";
			} else if (outputs[i] == six) {
				displayOut += "6";
			} else if (outputs[i] == seven) {
				displayOut += "7";
			} else if (outputs[i] == eight) {
				displayOut += "8";
			} else if (outputs[i] == nine) {
				displayOut += "9";
			}
		}
		if (displayOut.size() != 4) {
			std::cout << "Error!" << std::endl;
		}
		sumOut += std::stoi(displayOut);
	}

	std::cout << "Final answer is: " << sumOut << std::endl;
};