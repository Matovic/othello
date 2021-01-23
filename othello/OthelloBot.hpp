/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
* 
* @file OthelloBot.hpp
* @author Erik Matovic
* @version 31/01/2021
*/
/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloBot.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include "OthelloGame.hpp"

/**
* Class OthelloBot representing player's opponent
*/
class OthelloBot : public OthelloGame
{
public:
	/**
	* Create OthelloBot object with specific parameters.
	* @param playerDisk char to specify color of bot's disk based on player's disk.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	*/
	OthelloBot(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime);

	/**
	* Destroy OthelloBot object.
	*/
	~OthelloBot();

private:
};

