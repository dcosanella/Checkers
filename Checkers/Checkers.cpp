// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class CheckerBoard {
	public:
		void initBoard(void);
		void displayBoard(void);


	private:
		string board[8][8];
};

//---------------------------------------------------------------------------------
// Initialize CheckerBoard
void CheckerBoard::initBoard(void) {
	for(int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if ((row + col) % 2 != 0 && row >= 5) {
				board[row][col] = "W";
				if (row == 3 || row == 4) {
					board[row][col] = " ";
				}
			}
			else if((row + col) % 2 != 0 && row <= 2) {
				board[row][col] = "B";
				if(row >= 3) {
					board[row][col] = " ";
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------
// Display CheckerBoard
void CheckerBoard::displayBoard(void) {

	cout << "\n\n";
	
	for(int row = 0; row < 8; row++) {
		cout << "\t\t+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

		cout << "\t\t|";
		for (int col = 0; col < 8; col++) {
			if (board[row][col].empty()) {
				cout << "  " << "   |";
			}
			else {
				cout << "  " << board[row][col] << "  |";
			}
			
		}
		cout << endl;
	}
	cout << "\t\t+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
}

int main()
{
	CheckerBoard checkerBoard;
	checkerBoard.initBoard();
	checkerBoard.displayBoard();
    return 0;
}

