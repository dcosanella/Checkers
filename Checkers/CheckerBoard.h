#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <string>

using namespace std;

class CheckerBoard {
public:
	void displayTitle(void);
	void displayScore(void);
	void updateScore(string& player, int jumpOption);
	void initBoard(void);
	void displayBoard(void);
	string& getSquare(int row, int col);
	void updateBoard(int row, int col, string& square);
	void clearSquare(int row, int col);
	void checkForKing(void);
	bool checkWinner(void);
	const int getRPieces(void);
	const int getBPieces(void);

private:
	string m_board[8][8];
	int m_rPieces;
	int m_bPieces;
};


#endif