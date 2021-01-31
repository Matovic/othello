/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloPlayer.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include "OthelloGame.hpp"
#include "OthelloBot.hpp"

/**
* Class OthelloPlayer representing player
*/
class OthelloPlayer : public OthelloGame
{
public:
	/**
	* Create OthelloPlayer object with specific parameters.
	* @param color integer to specify color of player's disk.
	* 1 - white color.
	* 0 - black color.
	* -1 - not valid command, exit program.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	*/
	OthelloPlayer(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime);

	/**
	* Destroy OthelloPlayer object.
	*/
	~OthelloPlayer();

	/**
	* Reads user's commands
	*/
	void readCommand();

private:
	/**
	* Prints welcoming text for user with info about a game.
	*/
	void welcomeText();

	/**
	* Prints best possible path for player.
	* @param bot class for accessing tree structure of possible game states.
	* @return 0 if possible, otherwise 1.
	*/
	int printBestPath(OthelloBot& bot);
};