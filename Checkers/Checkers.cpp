// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string g_blank = "";

class CheckerBoard {
	public:
		void displayTitle(void);
		void initBoard(void);
		void displayBoard(void);
		string getSquare(int row, int col);
		void updateBoard(int row, int col, string);
		void clearSquare(int row, int col);

	private:
		string m_board[8][8];
};

class Game : public CheckerBoard {
	public:
		void displayGame(void);
		void gameLoop(CheckerBoard checkerBoard);
		string getPlayer(void);
		string switchPlayer(string player);
		bool checkForJump(int row, int col, int rowMove, int colMove, CheckerBoard checkerBoard);
		void jump(int row, int col, int rowMove, int colMove, CheckerBoard checkerBoard);
		int getJumpMove(void);

	private:
		string m_player;
		int m_row;
		int m_col;
		int m_rowMove;
		int m_colMove;
		bool m_winner;
		bool m_jump;
		int m_jumpOption;
};

//---------------------------------------------------------------------------------
// Display title
void CheckerBoard::displayTitle(void) {
	cout << endl <<  "\t\t\t\t      Checkers" << endl;
}

//---------------------------------------------------------------------------------
// Initialize checkerboard
void CheckerBoard::initBoard(void) {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if ((row + col) % 2 != 0 && row >= 5) {
				m_board[row][col] = "r";
				if (row == 3 || row == 4) {
					m_board[row][col] = g_blank;
				}
			}
			else if ((row + col) % 2 != 0 && row <= 2) {
				m_board[row][col] = "b";
				if (row >= 3) {
					m_board[row][col] = g_blank;
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------
// Display checkerboard
void CheckerBoard::displayBoard(void) {
	system("cls");
	displayTitle();
	cout << "\n\n";

	cout << "\t\t     0     1     2     3     4     5     6     7" << endl;
	
	for (int row = 0; row < 8; row++) {
		cout << "\t\t  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
		cout << "\t\t" << row << " |";
		for (int col = 0; col < 8; col++) {
			if (m_board[row][col] == g_blank) {
				cout << "  " << "   |";
			}
			else {
				cout << "  " << m_board[row][col] << "  |";
			}
			
		}
		cout << endl;
	}
	cout << "\t\t  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
}

//---------------------------------------------------------------------------------
// Return string inside of specfied square
string CheckerBoard::getSquare(int row, int col) {
	return m_board[row][col];
}

//---------------------------------------------------------------------------------
// Update the game board
void CheckerBoard::updateBoard(int row, int col, string square) {
	m_board[row][col] = square;
}

//---------------------------------------------------------------------------------
// Clear a game square
void CheckerBoard::clearSquare(int row, int col) {
	m_board[row][col] = g_blank;
}

//---------------------------------------------------------------------------------
// Display the game
void Game::displayGame(void) {
	CheckerBoard checkerBoard;
	checkerBoard.initBoard();
	checkerBoard.displayBoard();
	m_player = "r";
	gameLoop(checkerBoard);
}

//---------------------------------------------------------------------------------
// Main game loop
void Game::gameLoop(CheckerBoard checkerBoard) {
	m_winner = false;
	while (!m_winner) {
		cout << "\n\tTurn: " << m_player << "\n\n";
		cout << "\t" << m_player << ", please choose the row of the game piece you would like to move: ";
		cin >> m_row;
		cout << "\n\tNow, choose the column of that game piece: ";
		cin >> m_col;

		string square = checkerBoard.getSquare(m_row, m_col);
		if (square == m_player) {
			cout << "\n\tWhich row would you like to move this piece to: ";
			cin >> m_rowMove;
			cout << "\n\tWhich column would you like to move this piece to: ";
			cin >> m_colMove;
			if ((m_col - m_colMove == 1 || m_col - m_colMove == -1) && (m_row - m_rowMove == 1 || m_row - m_rowMove == -1)) {
				string squareMove;
				squareMove = checkerBoard.getSquare(m_rowMove, m_colMove);
				if (squareMove.empty()) {
					checkerBoard.clearSquare(m_row, m_col);
					checkerBoard.updateBoard(m_rowMove, m_colMove, m_player);
					string player = getPlayer();
					m_player = switchPlayer(player);
					checkerBoard.displayBoard();
				}
				else {
					if (squareMove == m_player) {
						cout << "\tInvalid move. Square selected is not empty. Choose another square." << endl;
						gameLoop(checkerBoard);
					}
				}	
			}
			//TODO: add invalid move exception (or function). Or look for other valid moves (jump over opposing pieces, etc.)
			// Check for jumps
			else if ((m_col - m_colMove == 2 || m_col - m_colMove == -2) && (m_row - m_rowMove == 2 || m_row - m_rowMove == -2)) {
				bool jumpMove = checkForJump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
				if (jumpMove) {
					cout << "in jumpMove\n\n";
					jump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
					string player = getPlayer();
					m_player = switchPlayer(player);
				}
			}
		}
		else {
			cout << "\tNo game piece found. Please choose another location.\n\n";
			gameLoop(checkerBoard);
		}
	}	
}

//---------------------------------------------------------------------------------
// Return current player
string Game::getPlayer(void) {
	return m_player;
}

//---------------------------------------------------------------------------------
// Switch player
string Game::switchPlayer(string player) {
	if (player == "r") {
		player = "b";
	}
	else {
		player = "r";
	}
	return player;
}

//---------------------------------------------------------------------------------
// Check for a legel jump move
bool Game::checkForJump(int row, int col, int rowMove, int colMove, CheckerBoard checkerBoard) {
	m_jump = false;
	if (rowMove - row == 2 && colMove - col == 2) {
		string square = checkerBoard.getSquare((rowMove - 1), (colMove - 1));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to 
		if (square != m_player  && jumpSquare == g_blank) {
			m_jump = true;
			m_jumpOption = 1;
		}
	}
	else if (row - rowMove == 2 && col - colMove == 2) {
		string square = checkerBoard.getSquare((rowMove - 1), (colMove - 1));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to 
		if (square != m_player  && jumpSquare == g_blank) {
			m_jump = true;
			m_jumpOption = 2;
		}
	}
	else if (row - rowMove == 2 && colMove - col == 2) {
		string square = checkerBoard.getSquare((rowMove - 1), (colMove - 1));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to 
		if (square != m_player  && jumpSquare == g_blank) {
			m_jump = true;
			m_jumpOption = 3;
		}
	}
	else if (rowMove - row == 2 && col - colMove == 2) {
		string square = checkerBoard.getSquare((rowMove - 1), (colMove - 1));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to 
		if (square != m_player  && jumpSquare == g_blank) {
			m_jump = true;
			m_jumpOption = 4;
		}
	}
	return m_jump;
}

//---------------------------------------------------------------------------------
// Make jump move
void Game::jump(int row, int col, int rowMove, int colMove, CheckerBoard checkerBoard) {
	int jumpOption = getJumpMove();
	switch (jumpOption) {
		case 1:
			checkerBoard.clearSquare(row, col);
			checkerBoard.clearSquare((rowMove - 1), (colMove - 1));
			checkerBoard.updateBoard(rowMove, colMove, m_player);
			checkerBoard.displayBoard();
			break;
		case 2:
			checkerBoard.clearSquare(row, col);
			checkerBoard.clearSquare((rowMove + 1), (colMove + 1));
			checkerBoard.updateBoard(rowMove, colMove, m_player);
			checkerBoard.displayBoard();
			break;
		case 3:
			checkerBoard.clearSquare(row, col);
			checkerBoard.clearSquare((rowMove + 1), (colMove - 1));
			checkerBoard.updateBoard(rowMove, colMove, m_player);
			checkerBoard.displayBoard();
			break;
		case 4: //TODO: find out why this case is not working properly. Should jump piece down from right to left
			checkerBoard.clearSquare(row, col);
			checkerBoard.clearSquare((rowMove - 1), (colMove + 1));
			checkerBoard.updateBoard(rowMove, colMove, m_player);
			checkerBoard.displayBoard();
			break;
		default:
			break;
	}
	string player = getPlayer();
	m_player = switchPlayer(player);
	gameLoop(checkerBoard);
}

//---------------------------------------------------------------------------------
// Return jump option
int Game::getJumpMove(void) {
	return m_jumpOption;
}

int main()
{
	Game checkers;
	checkers.displayGame();
	return 0;
} 