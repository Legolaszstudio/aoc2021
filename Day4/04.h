#include <deque>
#include "classes.h"

#pragma once
std::deque<std::deque<std::deque<BingoItem>>> drawNumber(std::deque<std::deque<std::deque<BingoItem>>> input, int number);
int hasWinner(std::deque<std::deque<std::deque<BingoItem>>> input);
int sumUnmarkedBoard(std::deque<std::deque<BingoItem>> board);