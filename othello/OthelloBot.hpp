/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
* 
* @file OthelloBot.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include <string>

/**
* Class OthelloBot representing player's opponent
*/
class OthelloBot
{
public:
	/**
	* Create Othello bot with specific color.
	* @param color integer to specify color of bot's discs.
	* 1 - white color.
	* 0 - black color.
	* -1 - not valid command, exit program.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	*/
	OthelloBot(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime);

	/**
	* Destroy Othello bot object.
	*/
	~OthelloBot();

	/**
	* Get current integer of color specifying color of bot's discs.
	* @return m_color const reference of an integer.
	*/
	const int& getColor();

	/**
	* Get current state of a game board.
	* @return m_game const reference of a string.
	*/
	const std::string& getGameState();

	/**
	* Set state of a game board.
	* @param gameBoardIndex index to be changed.
	* @param disk to written on game board.
	*/
	void setGameState(const int& gameBoardIndex, const char& disk);

private:
	int m_color, m_maxDepth, m_heuristic, m_moveTime;			
	std::string m_game = "---------------------------OX------XO--------------------------------";

	friend std::ostream& operator<<(std::ostream&, const OthelloBot&);
};

/**
* Writes current game state to stream.
* @param lhs stream write
* @param rhs object OthelloBot to be written to stream
* @return lhs
*/
std::ostream& operator<<(std::ostream& lhs, const OthelloBot& rhs);