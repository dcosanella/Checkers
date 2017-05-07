// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "CheckerBoard.h"
#include "Game.h"

using namespace std;

//---------------------------------------------------------------------------------
// Display title
void CheckerBoard::displayTitle(void) {
	cout << endl <<  "\t\t\t\t      Checkers" << endl;
}

//---------------------------------------------------------------------------------
// Initialize checkerboard
void CheckerBoard::initBoard(void) {
	m_rPieces = 0;
	m_bPieces = 0;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if ((row + col) % 2 != 0 && row >= 5) {
				m_board[row][col] = "r";
				m_rPieces++;
				if (row == 3 || row == 4) {
					m_board[row][col] = "";
				}
			}
			else if ((row + col) % 2 != 0 && row <= 2) {
				m_board[row][col] = "b";
				m_bPieces++;
				if (row >= 3) {
					m_board[row][col] = "";
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
	cout << "\n";
	displayScore();
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
// Display score (number of game pieces remaining)
void CheckerBoard::displayScore() {
	cout << "\n";
	cout << "\t\t\tPlayer r: " << m_rPieces;
	cout << "\t\tPlayer b: " << m_bPieces;
}

//---------------------------------------------------------------------------------
// Update the score
void CheckerBoard::updateScore(string& player, int& jumpOption) {
	if (jumpOption <= 4) {
		if (player == "r" || player == "R") {
			m_bPieces--;
		}
		else if (player == "b" || player == "B") {
			m_rPieces--;
		}
	}
	else if (jumpOption > 4 && jumpOption <= 8) {
		if (player == "r" || player == "R") {
			m_bPieces -= 2;
		}
		else if (player == "b" || player == "B") {
			m_rPieces -= 2;
		}
	}
}

//---------------------------------------------------------------------------------
// Return string inside of specfied square
const string& CheckerBoard::getSquare(int row, int col) {
	return m_board[row][col];
}

//---------------------------------------------------------------------------------
// Update the game board (make move)
void CheckerBoard::updateBoard(int row, int col, string square) {
	m_board[row][col] = square;
	// TODO: implement function to check for king after board is updated
	checkForKing();
}

//---------------------------------------------------------------------------------
// Clear a game square
void CheckerBoard::clearSquare(int row, int col) {
	m_board[row][col] = "";
}

//---------------------------------------------------------------------------------
// Check for any kings after board has been updated
void CheckerBoard::checkForKing(void) {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (row == 0) {
				if (m_board[row][col] == "r") {
					m_board[row][col] = "R";
				}
			}
			else if (row == 7) {
				if (m_board[row][col] == "b") {
					m_board[row][col] = "B";
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------
// Display the game
void Game::displayGame(void) {
	m_checkerBoard.initBoard();
	m_checkerBoard.displayBoard();
	m_player = "r";
	gameLoop(m_checkerBoard);
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
			if (m_player == "b") {
				if ((m_col - m_colMove == 1 || m_col - m_colMove == -1) && m_row - m_rowMove == -1) {
					string squareMove;
					squareMove = checkerBoard.getSquare(m_rowMove, m_colMove);
					if (squareMove.empty()) {
						checkerBoard.clearSquare(m_row, m_col);
						checkerBoard.updateBoard(m_rowMove, m_colMove, m_player);
						switchPlayer();
						checkerBoard.displayBoard();
					}
					else {
						if (squareMove == m_player) {
							cout << "\tInvalid move. Square selected is not empty. Choose another square." << endl;
							gameLoop(checkerBoard);
						}
					}
				}
				// single jump move
				else if ((m_col - m_colMove == 2 || m_col - m_colMove == -2) && m_row - m_rowMove == -2) {
					bool jumpMove = checkForJump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
					if (jumpMove) {
						jump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
						switchPlayer();
					}
				}
				// double jump move
				else if ((m_col - m_colMove == 4 || m_col - m_colMove == -4) && m_row - m_rowMove == -4) {
					bool jumpMove = checkForJump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
					if (jumpMove) {
						jump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
						switchPlayer();
					}
				}
				else {
					cout << "\tInvalid move. Cannot move piece to specified location. Please try again." << endl;
				}
			}
			else if (m_player == "r") {
				if ((m_col - m_colMove == 1 || m_col - m_colMove == -1) && m_row - m_rowMove == 1) {
					string squareMove;
					squareMove = checkerBoard.getSquare(m_rowMove, m_colMove);
					if (squareMove.empty()) {
						checkerBoard.clearSquare(m_row, m_col);
						checkerBoard.updateBoard(m_rowMove, m_colMove, m_player);
						switchPlayer();
						checkerBoard.displayBoard();
					}
					else {
						if (squareMove == m_player) {
							cout << "\tInvalid move. Square selected is not empty. Choose another square." << endl;
							gameLoop(checkerBoard);
						}
					}
				}
				// single jump move
				else if ((m_col - m_colMove == 2 || m_col - m_colMove == -2) && m_row - m_rowMove == 2) {
					bool jumpMove = checkForJump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
					if (jumpMove) {
						jump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
						switchPlayer();
					}
				}
				// double jump move
				else if ((m_col - m_colMove == 4 || m_col - m_colMove == -4) && m_row - m_rowMove == 4) {
					bool jumpMove = checkForJump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
					if (jumpMove) {
						jump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
						switchPlayer();
					}
				}
				else {
					cout << "\tInvalid move. Cannot move piece to specified location. Please try again." << endl;
				}
			}
		}
		// check for kinged game pieces
		else if ((m_player == "r" && square == "R") || (m_player == "b" && square == "B")) {
			cout << "\n\tWhich row would you like to move this piece to: ";
			cin >> m_rowMove;
			cout << "\n\tWhich column would you like to move this piece to: ";
			cin >> m_colMove;
			if ((m_col - m_colMove == 1 || m_col - m_colMove == -1) && (m_row - m_rowMove == 1 || m_row - m_rowMove == -1)) {
				string squareMove;
				squareMove = checkerBoard.getSquare(m_rowMove, m_colMove);
				if (squareMove.empty()) {
					checkerBoard.clearSquare(m_row, m_col);
					checkerBoard.updateBoard(m_rowMove, m_colMove, square);
					switchPlayer();
					checkerBoard.displayBoard();
				}
				else {
					if (squareMove == m_player) {
						cout << "\tInvalid move. Square selected is not empty. Choose another square." << endl;
						gameLoop(checkerBoard);
					}
				}
			}
			// Check for jumps
			else if ((m_col - m_colMove == 2 || m_col - m_colMove == -2) && (m_row - m_rowMove == 2 || m_row - m_rowMove == -2)) {
				bool jumpMove = checkForJump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
				if (jumpMove) {
					jump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
					switchPlayer();
				}
			}
			// Check for double jumps
			else if ((m_col - m_colMove == 4 || m_col - m_colMove == -4) && (m_row - m_rowMove == 4 || m_row - m_rowMove == -4)) {
				bool jumpMove = checkForJump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
				if (jumpMove) {
					jump(m_row, m_col, m_rowMove, m_colMove, checkerBoard);
					switchPlayer();
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
// Switch player
void Game::switchPlayer(void) {
	if (m_player == "r") {
		m_player = "b";
	}
	else {
		m_player = "r";
	}
}

//---------------------------------------------------------------------------------
// Check for a legel jump move
bool Game::checkForJump(int row, int col, int rowMove, int colMove, CheckerBoard checkerBoard) {
	m_jump = false;
	// jump down left to right
	if (rowMove - row == 2 && colMove - col == 2) {
		string square = checkerBoard.getSquare((rowMove - 1), (colMove - 1));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to
		if (!(square.empty())) {
			if (square != m_player  && jumpSquare.empty()) {
				m_jump = true;
				m_jumpOption = 1;
			}
		}
	}
	// jump up right to left
	else if (row - rowMove == 2 && col - colMove == 2) {
		string square = checkerBoard.getSquare((rowMove + 1), (colMove + 1));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to
		if (!(square.empty())) {
			if (square != m_player  && jumpSquare.empty()) {
				m_jump = true;
				m_jumpOption = 2;
			}
		}
	}
	// jump up left to right
	else if (row - rowMove == 2 && colMove - col == 2) {
		string square = checkerBoard.getSquare((rowMove + 1), (colMove - 1));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to
		if (!(square.empty())) {
			if (square != m_player  && jumpSquare.empty()) {
				m_jump = true;
				m_jumpOption = 3;
			}
		}
	}
	// jump down right to left
	else if (rowMove - row == 2 && col - colMove == 2) {
		string square = checkerBoard.getSquare((rowMove - 1), (colMove + 1));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to
		if (!(square.empty())) {
			if (square != m_player  && jumpSquare.empty()) {
				m_jump = true;
				m_jumpOption = 4;
			}
		}
	}
	// check for double jumps
	// double jump down left to right
	else if (rowMove - row == 4 && colMove - col == 4) {
		string square = checkerBoard.getSquare((rowMove - 3), (colMove - 3));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare((rowMove - 2), (colMove - 2));	// Check square to jump to 
		if (!(square.empty())) {
			if (square != m_player  && jumpSquare.empty()) {
				square = checkerBoard.getSquare((rowMove - 1), (colMove - 1));		// Check square to jump over
				jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to 
				if (!(square.empty())) {
					if (square != m_player  && jumpSquare.empty()) {
						m_jump = true;
						m_jumpOption = 5;
					}
				}
			}
		}
	}
	// double jump up right to left
	else if (row - rowMove == 4 && col - colMove == 4) {
		string square = checkerBoard.getSquare((rowMove + 3), (colMove + 3));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare((rowMove + 2), (colMove + 2));	// Check square to jump to
		if (!(square.empty())) {
			if (square != m_player  && jumpSquare.empty()) {
				square = checkerBoard.getSquare((rowMove + 1), (colMove + 1));		// Check square to jump over
				jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to 
				if (!(square.empty())) {
					if (square != m_player  && jumpSquare.empty()) {
						m_jump = true;
						m_jumpOption = 6;
					}
				}
			}
		}
	}
	// double jump up left to right
	else if (row - rowMove == 4 && colMove - col == 4) {
		string square = checkerBoard.getSquare((rowMove + 3), (colMove - 3));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare((rowMove + 2), (colMove - 2));	// Check square to jump to
		if (!(square.empty())) {
			if (square != m_player  && jumpSquare.empty()) {
				square = checkerBoard.getSquare((rowMove + 1), (colMove - 1));		// Check square to jump over
				jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to 
				if (!(square.empty())) {
					if (square != m_player  && jumpSquare.empty()) {
						m_jump = true;
						m_jumpOption = 7;
					}
				}
			}
		}
	}
	// double jump down right to left
	else if (rowMove - row == 4 && col - colMove == 4) {
		string square = checkerBoard.getSquare((rowMove - 3), (colMove + 3));		// Check square to jump over
		string jumpSquare = checkerBoard.getSquare((rowMove - 2), (colMove + 2));	// Check square to jump to
		if (!(square.empty())) {
			if (square != m_player  && jumpSquare.empty()) {
				square = checkerBoard.getSquare((rowMove - 1), (colMove + 1));		// Check square to jump over
				jumpSquare = checkerBoard.getSquare(rowMove, colMove);				// Check square to jump to 
				if (!(square.empty())) {
					if (square != m_player  && jumpSquare.empty()) {
						m_jump = true;
						m_jumpOption = 8;
					}
				}
			}
		}
	}

	return m_jump;
}

//---------------------------------------------------------------------------------
// Make jump move
void Game::jump(int row, int col, int rowMove, int colMove, CheckerBoard checkerBoard) {
	int jumpOption = getJumpMove();
	string square = checkerBoard.getSquare(row, col);
	if (square == "R" && m_player == "r") {
		m_player == "R";
	}
	else if (square == "B" && m_player == "b") {
		m_player == "B";
	}

	switch (jumpOption) {
	case 1:
		checkerBoard.updateBoard(rowMove, colMove, checkerBoard.getSquare(row, col));
		checkerBoard.clearSquare(row, col);
		checkerBoard.clearSquare((rowMove - 1), (colMove - 1));
		checkerBoard.updateScore(m_player, jumpOption);
		checkerBoard.displayBoard();
		break;
	case 2:
		checkerBoard.updateBoard(rowMove, colMove, checkerBoard.getSquare(row, col));
		checkerBoard.clearSquare(row, col);
		checkerBoard.clearSquare((rowMove + 1), (colMove + 1));
		checkerBoard.updateScore(m_player, jumpOption);
		checkerBoard.displayBoard();
		break;
	case 3:
		checkerBoard.updateBoard(rowMove, colMove, checkerBoard.getSquare(row, col));
		checkerBoard.clearSquare(row, col);
		checkerBoard.clearSquare((rowMove + 1), (colMove - 1));
		checkerBoard.updateScore(m_player, jumpOption);
		checkerBoard.displayBoard();
		break;
	case 4:
		checkerBoard.updateBoard(rowMove, colMove, checkerBoard.getSquare(row, col));
		checkerBoard.clearSquare(row, col);
		checkerBoard.clearSquare((rowMove - 1), (colMove + 1));
		checkerBoard.updateScore(m_player, jumpOption);
		checkerBoard.displayBoard();
		break;
	case 5:
		checkerBoard.updateBoard(rowMove, colMove, checkerBoard.getSquare(row, col));
		checkerBoard.clearSquare(row, col);
		checkerBoard.clearSquare((rowMove - 3), (colMove - 3));
		checkerBoard.clearSquare((rowMove - 1), (colMove - 1));
		checkerBoard.updateScore(m_player, jumpOption);
		checkerBoard.displayBoard();
		break;
	case 6:
		checkerBoard.updateBoard(rowMove, colMove, checkerBoard.getSquare(row, col));
		checkerBoard.clearSquare(row, col);
		checkerBoard.clearSquare((rowMove + 3), (colMove + 3));
		checkerBoard.clearSquare((rowMove + 1), (colMove + 1));
		checkerBoard.updateScore(m_player, jumpOption);
		checkerBoard.displayBoard();
		break;
	case 7:
		checkerBoard.updateBoard(rowMove, colMove, checkerBoard.getSquare(row, col));
		checkerBoard.clearSquare(row, col);
		checkerBoard.clearSquare((rowMove + 3), (colMove - 3));
		checkerBoard.clearSquare((rowMove + 1), (colMove - 1));
		checkerBoard.updateScore(m_player, jumpOption);
		checkerBoard.displayBoard();
		break;
	case 8:
		checkerBoard.updateBoard(rowMove, colMove, checkerBoard.getSquare(row, col));
		checkerBoard.clearSquare(row, col);
		checkerBoard.clearSquare((rowMove - 3), (colMove + 3));
		checkerBoard.clearSquare((rowMove - 1), (colMove + 1));
		checkerBoard.updateScore(m_player, jumpOption);
		checkerBoard.displayBoard();
		break;
	default:
		break;
	}

	switchPlayer();
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