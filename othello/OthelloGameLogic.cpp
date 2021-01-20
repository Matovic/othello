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
int checkUp(const std::string& gameBoard, const size_t& diskIndex, const int& color)
{
	if (diskIndex > 55)
		return -1;
	char opponentDisk = 'X';
	if (!color) opponentDisk = 'O';

	if (gameBoard[diskIndex] != opponentDisk && gameBoard[diskIndex] == '-')
		return -1;

	if (gameBoard[diskIndex] == opponentDisk)
		return checkUp(gameBoard, diskIndex + 8, color);

	return static_cast<int>(diskIndex);
}

/*
std::vector<int> checkVertical(const std::string& gameBoard, const size_t& diskIndex, const int& color)
{
	std::vector<int> vectorDiskIndex;
	if (gameBoard[diskIndex] > 7) checkDown(gameBoard, diskIndex, color);
	if (gameBoard[diskIndex] < 56) checkUp(gameBoard, diskIndex, color);

	return vectorDiskIndex;
}*/

// Gets all possible moves on Othello board.
void getValidMoves(OthelloBot& othelloBot)
{
	std::string possibleGameState = othelloBot.getGameState();
	auto movePosition = possibleGameState.find('O');
	possibleGameState[movePosition - 1] = '*';
	std::cout << "FIND:" << movePosition << '\n';
	std::cout << possibleGameState << '\n';
}

// Moves disk on Othello board based on given command.
void moveDisk(OthelloBot& othelloBot, const std::string& command)
{
	std::cout << command << '\n';
	std::cout << '\n' << othelloBot << '\n';
}