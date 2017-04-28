// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class CheckerBoard {
	public:
		void displayTitle(void);
		void initBoard(void);
		void displayBoard(void);
		string getSquare(int row, int col);
		void updateBoard(int row, int col, string);

	private:
		string m_board[8][8];
};

class Game : public CheckerBoard {
	public:
		void displayGame(void);
		void gameLoop(CheckerBoard checkerboard);
		string getPlayer(void);
		string switchPlayer(string player);

	private:
		string m_player;
		int m_row;
		int m_col;
		int m_rowMove;
		int m_colMove;
		bool m_winner;
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
					m_board[row][col] = " ";
				}
			}
			else if ((row + col) % 2 != 0 && row <= 2) {
				m_board[row][col] = "b";
				if (row >= 3) {
					m_board[row][col] = " ";
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
			if (m_board[row][col].empty()) {
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
	cout << "\n\nrow: " << row << endl;
	cout << "\n\ncol: " << col << endl;
	cout << "\n\nstring: " << square << endl;
	m_board[row][col] = square;
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
		cout << "\tTurn: " << m_player << "\n\n";
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
				checkerBoard.updateBoard(m_row, m_col, " ");
				checkerBoard.updateBoard(m_rowMove, m_colMove, m_player);
				string player = getPlayer();
				m_player = switchPlayer(player);
				checkerBoard.displayBoard();
			}
			//TODO: add invalid move exception (or function)
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

int main()
{
	Game checkers;
	checkers.displayGame();
	return 0;
} 