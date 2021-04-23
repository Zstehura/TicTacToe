

#include "stdafx.h"
#include "Board.h"

using namespace std;

int main(){
	// Declarations
	Board b;
	string sInput = "";
	bool valid = false;
	bool bWin = false;
	int coinToss = 0;

	// Introduction to the game
	cout << "Welcome to Tic Tac Toe!" << endl;
	cout << "The rules are very simple:" << endl;
	cout << " Be the first to fill an entire row, column, or diagonal line" << endl;

	// Prompt for board size
	cout << "\nHow large would you like to make the board? " << endl;
	while (!valid) {
		try {
			cout << "Enter a number 2-9: ";
			cin >> sInput;
			int size = stoi(sInput);
			if (size < 2 || size > 9) throw 1;
			b = Board(size);
			valid = true;
		}
		catch (...) {
			cout << "ERROR: Invalid input" << endl;
		}
	}

	// Determine first move
	cout << "\nLet's toss a coin to see who goes first!" << endl;
	valid = false;
	while (!valid) {
		cout << "Call either Heads or Tails: ";
		cin >> sInput;
		if (sInput[0] == 'h' || sInput[0] == 'H' || sInput[0] == 't' || sInput[0] == 'T') {
			valid = true;
		}
		else {
			cout << "ERROR: Invalid input" << endl;
		}
	}
	coinToss = rand() % 2;
	if (coinToss == 1) {
		// We'll say this is heads
		cout << "The toss came up Heads!" << endl;
		if (sInput[0] == 'h' || sInput[0] == 'H') bWin = true;
		else bWin = false;
	}
	else {
		// Tails
		cout << "The toss came up Tails!" << endl;
		if (sInput[0] == 't' || sInput[0] == 'T') bWin = true;
		else bWin = false;
	}

	// Check if the player won the toss
	if (bWin) {
		// Give player first move
		cout << "You won! You get the first move.\n" << endl;
		b.printBoard();
		cout << endl;
		b.getPlayerMove();
	}
	else {
		cout << "You lost, the computer goes first" << endl;
	}

	// Start the game
	// Loop gives computer the first move since the player would already have had 
	//   the first move if they won
	bWin = false;
	do {
		// Computer moves
		b.cpuMove();
		// Check for the game end
		if (b.getWinner() != ' ') break;

		// Give player their move
		cout << endl;
		b.printBoard();
		cout << endl;
		b.getPlayerMove();
		//Check for the game end
		if (b.getWinner() != ' ') break;

	} while (true);

	cout << "\nFinal Result:\n\n";
	b.printBoard();
	cout << endl << endl;
	if (b.getWinner() == 'X') {
		cout << "You win!!\n\n";
	}
	else if (b.getWinner() == 'O') {
		cout << "Oh no! You Lost!\n\n";
	}
	else if (b.getWinner() == 'C') {
		cout << "Cat's Game! Its a tie!\n\n";
	}

	char c;
	std::cin >> c;
	return 0;
}