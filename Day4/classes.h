#include <string>

class BingoItem {
	BingoItem(bool drawn, int num);
	public:
		bool drawn = false;
		int num = 0;
};