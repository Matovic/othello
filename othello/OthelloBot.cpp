/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloBot.cpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include "OthelloBot.hpp"

// Create OthelloBot object with specific parameters.
OthelloBot::OthelloBot(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime) 
	: OthelloGame(playerDisk, maxDepth, heuristic, moveTime)
{
}

// Destroy OthelloBot object.
OthelloBot::~OthelloBot()
{
}