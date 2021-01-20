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
#include "OthelloGameLogic.hpp"

// Checks possible move on Othello board by going up.
int checkUp(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex > 55)
		return -1;

	if (gameBoard[diskIndex] != opponentDisk && gameBoard[diskIndex] != '-')
		return -1;

	if (gameBoard[diskIndex] == opponentDisk)
		return checkUp(gameBoard, diskIndex - 8, opponentDisk);

	return static_cast<int>(diskIndex);
}

/*
std::vector<int> checkVertical(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	std::vector<int> vectorDiskIndex;
	if (gameBoard[diskIndex] > 7) checkDown(gameBoard, diskIndex, opponentDisk);
	if (gameBoard[diskIndex] < 56) checkUp(gameBoard, diskIndex, opponentDisk);

	return vectorDiskIndex;
}*/

// Checks all directions for possible moves on Othello board.
std::vector<int> checkDirections(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	std::vector<int> vectorValidMoves;// { static_cast<int>(diskIndex) };
	gameBoard, diskIndex, opponentDisk;
	int tmp = -1;
	// go up
	tmp = checkUp(gameBoard, diskIndex - 8, opponentDisk);
	if (tmp != -1) vectorValidMoves.insert(vectorValidMoves.end(), tmp);


	return vectorValidMoves;
}

// Gets all possible moves on Othello board.
std::vector<int> getValidMoves(OthelloBot& othelloBot)
{
	std::string possibleGameState = othelloBot.getGameState();
	size_t pos = 0;
	std::vector<int> vectorValidMoves;								// possible indexes of game state
	char opponentDisk = 'X';
	if (!othelloBot.getColor()) opponentDisk = 'O';
	while (1)
	{
		size_t movePosition = possibleGameState.find(opponentDisk, pos);
		if (movePosition == std::string::npos) break;

		std::vector<int> tmp = checkDirections(possibleGameState, movePosition, 0);
		vectorValidMoves.insert(vectorValidMoves.end(), tmp.begin(), tmp.end());
		

		pos = movePosition + 1;
	}

	for (int x : vectorValidMoves)
	{
		possibleGameState[x] = '*';
		//std::cout << x << ' ' << opponentDisk;
	}
	std::cout << '\n';

	//std::cout << "FIND:" << pos << '\n';
	printGameState(possibleGameState);

	return vectorValidMoves;
}

// Moves disk on Othello board based on given command.
void moveDisk(OthelloBot& othelloBot, const std::string& command)
{
	std::cout << command << '\n';
	std::cout << '\n' << othelloBot << '\n';
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