#pragma once

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include <random>

class Board
{
public:
	Board(int);
	Board() : Board(3) {};
	~Board();

	void cpuMove();
	void getPlayerMove();
	void printBoard();

	char getWinner();
	
private:
	int size;
	char cWinner;

	std::vector<char> pos;

	void checkWinner();
	std::string strLine(int);
	std::string strDash();
};

