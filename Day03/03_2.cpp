#include <deque>
#include <string>
#include "03_2.h"
#include <vector>
#include <iostream>

int secondPart(std::deque<std::string> inputs) {
	//Oxygen generator rating
	std::deque<std::string> oxDeque = inputs;
	while (oxDeque.size() > 1) {
		for (size_t i = 0; i < oxDeque[0].length(); i++) {
			std::vector<int> zerosAndOnes = { 0, 0 };
			for (size_t j = 0; j < oxDeque.size(); j++) {
				if (oxDeque[j].at(i) == '0') {
					zerosAndOnes[0] += 1;
				} else {
					zerosAndOnes[1] += 1;
				}
			}
			char toDelete = '0';
			if (zerosAndOnes[0] > zerosAndOnes[1]) {
				toDelete = '1';
			}
			int inpLen = oxDeque.size();
			std::deque<std::string> inputCopy = oxDeque;
			int deletes = 0;
			for (size_t inputIter = 0; inputIter < inpLen; inputIter++) {
				if (oxDeque[inputIter].at(i) == toDelete && inputCopy.size() > 1) {
					inputCopy.erase(inputCopy.begin() + (inputIter - deletes));
					deletes++;
				}
			}
			oxDeque = inputCopy;
		}
	}
	int oxGenRating = std::stoi(oxDeque[0], nullptr, 2);
	std::cout << "Oxygen generator rating: " << oxDeque[0] << " (" << oxGenRating << ")" << std::endl;

	//CO2 Scrubber rating
	std::deque<std::string> scrubDeque = inputs;
	while (scrubDeque.size() > 1) {
		for (size_t i = 0; i < scrubDeque[0].length(); i++) {
			std::vector<int> zerosAndOnes = { 0, 0 };
			for (size_t j = 0; j < scrubDeque.size(); j++) {
				if (scrubDeque[j].at(i) == '0') {
					zerosAndOnes[0] += 1;
				} else {
					zerosAndOnes[1] += 1;
				}
			}
			char toDelete = '1';
			if (zerosAndOnes[0] > zerosAndOnes[1]) {
				toDelete = '0';
			}
			int inpLen = scrubDeque.size();
			std::deque<std::string> inputCopy = scrubDeque;
			int deletes = 0;
			for (size_t inputIter = 0; inputIter < inpLen; inputIter++) {
				if (scrubDeque[inputIter].at(i) == toDelete && inputCopy.size() > 1) {
					inputCopy.erase(inputCopy.begin() + (inputIter - deletes));
					deletes++;
				}
			}
			scrubDeque = inputCopy;
		}
	}
	int scrubRating = std::stoi(scrubDeque[0], nullptr, 2);
	std::cout << "CO2 scrubber rating: " << scrubDeque[0] << " (" << scrubRating << ")" << std::endl;
	std::cout << std::endl << "Final answer: " << scrubRating * oxGenRating << std::endl;

	return 0;
}