#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <sstream>

struct BingoItem {
	int num;
	bool drawn;
};

/// <summary>
/// Changes drawn to true
/// </summary>
/// <param name="input">Bingo tables</param>
/// <param name="number">Number to be drawn</param>
/// <returns>Bingo table with drawn values changed to true</returns>
std::deque<std::deque<std::deque<BingoItem>>> drawNumber(std::deque<std::deque<std::deque<BingoItem>>> input, int number) {
	std::deque<std::deque<std::deque<BingoItem>>> output = input;
	for (int boardNum = 0; boardNum < output.size(); boardNum++) {
		for (int row = 0; row < output[boardNum].size(); row++) {
			for (int column = 0; column < output[boardNum][row].size(); column++) {
				if (output[boardNum][row][column].num == number) {
					output[boardNum][row][column].drawn = true;
				}
			}
		}
	}

	return output;
}

/// <summary>
/// Checks winner
/// </summary>
/// <param name="input">Bingo tables</param>
/// <returns>-1 if no winner found, otherwise table number</returns>
int hasWinner(std::deque<std::deque<std::deque<BingoItem>>> input) {
	for (int boardNum = 0; boardNum < input.size(); boardNum++) {
		// Check rows
		for (int row = 0; row < input[boardNum].size(); row++) {
			bool isWinning = true;
			for (int column = 0; column < input[boardNum][row].size(); column++) {
				isWinning = isWinning && input[boardNum][row][column].drawn;
				if (isWinning == false) break;
			}
			if (isWinning) {
				return boardNum;
			}
		}

		//Check columns
		for (int column = 0; column < input[boardNum][0].size(); column++) {
			bool isWinning = true;
			for (int row = 0; row < input[boardNum].size(); row++) {
				isWinning = isWinning && input[boardNum][row][column].drawn;
				if (isWinning == false) break;
			}
			if (isWinning) {
				return boardNum;
			}
		}
	}
	return -1;
}

/// <summary>
/// Sums undrawn numbers on the board
/// </summary>
/// <param name="board">The bingo board</param>
/// <returns>Sum of undrawn numbers</returns>
int sumUnmarkedBoard(std::deque<std::deque<BingoItem>> board) {
	int sum = 0;
	for (int row = 0; row < board.size(); row++) {
		for (int column = 0; column < board[row].size(); column++) {
			if (board[row][column].drawn == false) {
				sum += board[row][column].num;
			}
		}
	}
	return sum;
}

int main() {
	std::string line;
	std::ifstream file("04.txt");

	std::deque<int> drawnNumbers = {};
	std::deque<std::deque<std::deque<BingoItem>>> boardMatrix = {};
	// boardMatrix[boardnum][row][column]

	int index = 0;
	int boardLine = 0;
	while (std::getline(file, line)) {
		if (index == 0) {
			//Parse numbers drawn
			std::stringstream X(line);
			std::string lineNum;
			while (std::getline(X, lineNum, ',')) {
				drawnNumbers.push_back(std::stoi(lineNum));
				std::cout << lineNum << ", ";
			}
			std::cout << std::endl;
		}

		if (line == "") {
			boardMatrix.push_back({});
			boardLine = 0;
			std::cout << std::endl << std::endl;
		} else if (index != 0) {
			boardMatrix[boardMatrix.size() - 1].push_back({});
			std::string lineNum;
			std::stringstream X(line);
			while (std::getline(X, lineNum, ' ')) {
				if (lineNum != "") {
					BingoItem item;
					item.drawn = false;
					item.num = std::stoi(lineNum);
					boardMatrix[boardMatrix.size() - 1][boardLine].push_back(item);
				}
				std::cout << lineNum << " ";
			}
			std::cout << std::endl;
			boardLine++;
		}
		index++;
	}

	// Start drawing numbers
	int winningBoard = -1;
	int drawIndex = -1;
	while (drawIndex < (int)(drawnNumbers.size()) && winningBoard == -1) {
		drawIndex++;
		boardMatrix = drawNumber(boardMatrix, drawnNumbers[drawIndex]);
		winningBoard = hasWinner(boardMatrix);
	}

	std::cout << std::endl << std::endl;
	if (winningBoard == -1) {
		std::cout << "Error in calc, no winner" << std::endl;
		return 1;
	} else {
		std::cout << winningBoard + 1 << " board has won" << std::endl;
		int unmarkedSum = sumUnmarkedBoard(boardMatrix[winningBoard]);
		std::cout << unmarkedSum << " is the sum of the nondrawn numbers" << std::endl;
		int winningDrawn = drawnNumbers[drawIndex];
		std::cout << winningDrawn << " was the winning draw" << std::endl << std::endl;
		std::cout << "Final answer is: " << winningDrawn * unmarkedSum << std::endl;
	}

	return 0;
}