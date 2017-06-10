#ifndef GAME_H
#define GAME_H

#include <string>
#include "CheckerBoard.h"

using namespace std;

class Game {
public:
	void displayGame(void);
	void gameLoop(CheckerBoard& checkerBoard);
	void switchPlayer(void);
	bool checkForJump(int row, int col, int rowMove, int colMove, CheckerBoard& checkerBoard);
	void jump(int row, int col, int rowMove, int colMove, CheckerBoard& checkerBoard);
	int getJumpMove(void);

private:
	CheckerBoard m_checkerBoard;
	string m_player;
	int m_row;
	int m_col;
	int m_rowMove;
	int m_colMove;
	bool m_winner;
	bool m_jump;
	int m_jumpOption;
};

#endif