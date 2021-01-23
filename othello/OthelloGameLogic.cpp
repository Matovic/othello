/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloGameLogic.cpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "OthelloGameLogic.hpp"

// Checks possible move on Othello board by going left.
int checkLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	size_t currentColumn = diskIndex % 8;		// get current collumn in Othello board
	if (currentColumn == 0)
		return -1;								// if currentColumn is first column, return -1

	if (gameBoard[diskIndex] == opponentDisk)
		return checkLeft(gameBoard, diskIndex - 1, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going right.
int checkRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	size_t currentColumn = diskIndex % 8;		// get current collumn in Othello board
	if (currentColumn / 7)
		return -1;								// if currentColumn is last column, return -1

	if (gameBoard[diskIndex] == opponentDisk)
		return checkRight(gameBoard, diskIndex + 1, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going up.
int checkUp(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex < 8)
		return -1;

	if (gameBoard[diskIndex] == opponentDisk)
		return checkUp(gameBoard, diskIndex - 8, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going down.
int checkDown(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex > 55)
		return -1;

	if (gameBoard[diskIndex] == opponentDisk)
		return checkDown(gameBoard, diskIndex + 8, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going diagonal up and left.
int checkDiagonalUpLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex < 8 || diskIndex % 8 == 0)
		return -1;

	if (gameBoard[diskIndex] == opponentDisk)
		return checkDiagonalUpLeft(gameBoard, diskIndex - 9, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going diagonal up and right.
int checkDiagonalUpRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex < 8 || diskIndex % 8 == 7)
		return -1;

	if (gameBoard[diskIndex] == opponentDisk)
		return checkDiagonalUpRight(gameBoard, diskIndex - 7, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going diagonal down and left.
int checkDiagonalDownLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex > 55 || diskIndex % 8 == 0)
		return -1;

	if (gameBoard[diskIndex] == opponentDisk)
		return checkDiagonalDownLeft(gameBoard, diskIndex + 7, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going diagonal down and right.
int checkDiagonalDownRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex > 55 || diskIndex % 8 == 7)
		return -1;

	if (gameBoard[diskIndex] == opponentDisk)
		return checkDiagonalDownRight(gameBoard, diskIndex + 9, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks all directions for possible moves on Othello board.
std::vector<int> checkDirections(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	std::vector<int> vectorValidMoves;
	int tmp = -1;

	// check up
	if (diskIndex > 7 && gameBoard[diskIndex - 8] == opponentDisk)
	{
		tmp = checkUp(gameBoard, diskIndex - 8, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check down
	if (diskIndex < 56 && gameBoard[diskIndex + 8] == opponentDisk)
	{
		tmp = checkDown(gameBoard, diskIndex + 8, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check left
	if (diskIndex % 8 != 0 && gameBoard[diskIndex - 1] == opponentDisk)
	{
		tmp = checkLeft(gameBoard, diskIndex - 1, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check right
	if (diskIndex % 8 != 7 && gameBoard[diskIndex + 1] == opponentDisk)
	{
		tmp = checkRight(gameBoard, diskIndex + 1, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check diagonal up-left
	if (diskIndex > 7 && diskIndex % 8 != 0 && gameBoard[diskIndex - 9] == opponentDisk)
	{
		tmp = checkDiagonalUpLeft(gameBoard, diskIndex - 9, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check diagonal up-right
	if (diskIndex > 7 && diskIndex % 8 != 7 && gameBoard[diskIndex - 7] == opponentDisk)
	{
		tmp = checkDiagonalUpRight(gameBoard, diskIndex - 7, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check diagonal down-left
	if (diskIndex < 56 && diskIndex % 8 != 0 && gameBoard[diskIndex + 7] == opponentDisk)
	{
		tmp = checkDiagonalDownLeft(gameBoard, diskIndex + 7, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check diagonal down-right
	if (diskIndex < 56 && diskIndex % 8 != 7 && gameBoard[diskIndex + 9] == opponentDisk)
	{
		tmp = checkDiagonalDownRight(gameBoard, diskIndex + 9, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	return vectorValidMoves;
}

// Gets all possible moves on Othello board.
std::vector<int> getValidMoves(const std::string& board, const char& disk, const char& opponentDisk)
{
	std::string possibleGameState = board;
	std::vector<int> vectorValidMoves;										// possible indexes of game state

	size_t pos = 0;
	while (1)
	{
		size_t movePosition = possibleGameState.find(disk, pos);			// position of my disk

		if (movePosition == std::string::npos) 
			break;

		std::vector<int> tmp = checkDirections(possibleGameState, movePosition, opponentDisk);
		vectorValidMoves.insert(vectorValidMoves.end(), tmp.begin(), tmp.end());
		
		pos = movePosition + 1;
	}
	showPossibleMoves(possibleGameState, vectorValidMoves);
	return vectorValidMoves;
}

// Shows possible moves to the player on game board.
void showPossibleMoves(std::string& possibleGameState, const std::vector<int>& vectorValidMoves)
{
	for (int x : vectorValidMoves)
		possibleGameState[x] = '*';
	std::cout << '\n';
	printGameState(possibleGameState);
}

// Places disk on Othello board based on given command.
void placeDisk(OthelloGame& othelloGame, const int& gameBoardIndex, const char& disk)
{
	othelloGame.setGameState(gameBoardIndex, disk);
	othelloGame.incrementScore();
}


// Writes current game state to output stream on a console.
void printGameState(const std::string& gameState)
{
	std::cout << "  a b c d e f g h";
	for (size_t i = 0, row = 0; i < 64; ++i)
	{
		if (i % 8 == 0)	std::cout << '\n' << ++row << ' ';
		std::cout << gameState[i] << ' ';
	}
	std::cout << '\n';
}

// Checks if given vector has already element with value of given integer.
int isIntInVector(const std::vector<int>& v, const int& iValue)
{
	return std::find(v.begin(), v.end(), iValue) != v.end();
}