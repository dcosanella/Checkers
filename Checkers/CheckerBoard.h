#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <string>

using namespace std;

class CheckerBoard {
public:
	void displayTitle(void);
	void initBoard(void);
	void displayBoard(void);
	string& getSquare(int row, int col);
	void updateBoard(int row, int col, string);
	void clearSquare(int row, int col);
	void checkForKing(void);

private:
	string m_board[8][8];
};


#endif