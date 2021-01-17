/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloGameLogic.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include <vector>
#include "OthelloGameLogic.hpp"

/*
std::vector<int> checkVertical(const std::string& gameBoard, const size_t& diskIndex, const int& color)
{
	std::vector<int> vectorDiskIndex;
	if (gameBoard[diskIndex] > 7) checkDown(gameBoard, diskIndex, color);
	if (gameBoard[diskIndex] < 56) checkUp(gameBoard, diskIndex, color);

	return vectorDiskIndex;
}*/

// 
void movePossibilities(OthelloBot& othelloBot)
{
	std::string possibleGameState = othelloBot.getGameState();
	auto movePosition = possibleGameState.find('O');
	possibleGameState[movePosition - 1] = '*';
	std::cout << "FIND:" << movePosition << '\n';
	std::cout << possibleGameState << '\n';
}

// 
void moveDisk(OthelloBot& othelloBot, const std::string& command)
{
	std::cout << command << '\n';
	std::cout << '\n' << othelloBot << '\n';
}