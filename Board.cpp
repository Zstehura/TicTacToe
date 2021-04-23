#include "stdafx.h"
#include "Board.h"


Board::Board(int iSize) {
	size = iSize;
	cWinner = ' ';
	for (int i = 0; i < (size*size); i++) {
		pos.push_back(' ');
	}
	srand(time(0));
}

Board::~Board() {}

void Board::cpuMove() {
	int iMove = 0;
	do {
		iMove = rand() % (size * size);
	} while (pos[iMove] != ' ');

	pos[iMove] = 'O';
	checkWinner();
}

void Board::getPlayerMove() {
	const std::string PROMPT = "Please enter the coordinates for your next move (0 to quit): ";
	bool valid = false;
	int iMove = 0;
	std::string sMove = "";

	while (!valid) {
		std::cout << PROMPT;
		std::cin >> sMove;

		if (sMove == "0") break;

		if (sMove.length() == 2) {
			if ((sMove[0] <= ('a' + size - 1) && sMove[0] >= 'a') || (sMove[0] <= ('A' + size - 1) && sMove[0] >= 'A')) {
				// grab number based on column
				if (sMove[0] <= ('a' + size - 1) && sMove[0] >= 'a') {
					//lowercase
					iMove = sMove[0] - 'a';
				}
				else {
					//Capitalized
					iMove = sMove[0] - 'A';
				}

				if (sMove[1] >= '1' && sMove[1] <= ('0' + size)) {
					iMove += ((sMove[1] - '1') * size);
					if (pos[iMove] == ' ') valid = true;
				}
			}
		}

		if (!valid) {
			std::cout << "ERROR: Invalid input. Moves should be entered with a letter" <<
				"\n  and a number such as 'A1'" << std::endl;
		}
	}

	if (valid) {
		pos[iMove] = 'X';
		checkWinner();
	}
	else {
		// user chose to quit
		// set the winner character to reflect this
		cWinner = 'q';
	}
}

std::string Board::strDash() {
	// returns a string of dashes with a number corresponding to the size of the Board
	std::string s = "   ";
	for (int i = 0; i < size; i++) {
		if(i<size-1) s += "----";
		else s += "---";
	}
	return s;
}

void Board::checkWinner(){
	// Check the places to see if there is a winner or a tie

	// Check Columns
	for (int col = 0; col < size; col++) {
		bool win = true;
		for (int row = 1; row < size; row++) {
			if (pos[col] != pos[col + (row * size)]) {
				win = false;
			}
		}

		if (win) cWinner = pos[col];
	}

	// Check Rows
	for (int row = 0; row < size; row++) {
		bool win = true;
		for (int col = 1; col < size; col++) {
			if (pos[(row*size)] != pos[(row*size + col)]) {
				win = false;
			}
		}

		if (win) cWinner = pos[row * size];
	}

	// Check diagonals
	bool win = true;
	for (int i = 1; i < size; i++) {
		if (pos[0] != pos[i * (size + 1)]) win = false;
	}
	if (win) cWinner = pos[0];

	win = true;
	for (int i = 1; i < size; i++) {
		if (pos[size - 1] != pos[(size-1)*(i+1)]) win = false;
	}
	if (win) cWinner = pos[size - 1];

	bool catsGame = true;
	if (cWinner != ' ') {
		for (int i = 0; i < (size*size); i++) {
			if (pos[i] == ' ') catsGame = false;
		}
		if (catsGame) cWinner = 'C';
	}
}

std::string Board::strLine(int line) {
	// Make sure its a valid line #
	if (line >= size) return "Error";

	std::string s = " ";
	int iAdd = line * size;

	//construct string of the line number provided
	for (int i = 0; i < size; i++) {
		s += pos[i + iAdd];
		if (i < size - 1) {
			s += " | ";
		}
	}

	return s;
}

void Board::printBoard() {
	std::cout << "   ";
	for (int i = 0; i < size; i++) {
		std::cout << " " << (char)('A' + i) << "  ";
	}
	std::cout << std::endl;

	for (int iLine = 0; iLine < size; iLine++) {
		std::cout << " " << (iLine + 1) << " " << strLine(iLine);
		if (iLine < size - 1) std::cout << std::endl << strDash();
		std::cout << std::endl;
	}

}

char Board::getWinner() {
	return cWinner;
}
