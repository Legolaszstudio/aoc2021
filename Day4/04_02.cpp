#include "04_02.h"
#include "04.h"
#include <iostream>

void partTwo(std::deque<std::deque<std::deque<BingoItem>>> boardMatrix, std::deque<int> drawnNumbers) {
	// Start drawing numbers
	int drawIndex = -1;
	std::deque<std::deque<BingoItem>> winner = {};
	int winningNum = -1;
	while (drawIndex < (int)(drawnNumbers.size() - 1)) {
		drawIndex++;
		int drawnNumber = drawnNumbers[drawIndex];
		boardMatrix = drawNumber(boardMatrix, drawnNumbers[drawIndex]);
		int winnerBoard = 0;
		while (winnerBoard != -1) {
			winnerBoard = hasWinner(boardMatrix);
			if (winnerBoard != -1) {
				winner = boardMatrix[winnerBoard];
				winningNum = drawnNumbers[drawIndex];
				boardMatrix.erase(boardMatrix.begin() + winnerBoard);
			}
		}
	}

	std::cout << "We have the last winner, it\'s board no" << winner[0][0].board+1 << std::endl;
	int unmarkedSum = sumUnmarkedBoard(winner);
	std::cout << unmarkedSum << " is the sum of the nondrawn numbers" << std::endl;
	std::cout << "Won when the number " << winningNum << " was drawn" << std::endl;
	std::cout << std::endl << "Final answer is: " << unmarkedSum * winningNum << std::endl;
}