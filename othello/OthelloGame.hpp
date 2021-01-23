/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloGame.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include <string>

/**
* Class OthelloGame representing player's opponent
*/
class OthelloGame
{
public:
	/**
	* Create OthelloGame object with specific parameters.
	* @param color integer to specify color of bot's discs.
	* 1 - white color.
	* 0 - black color.
	* -1 - not valid command, exit program.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	*/
	OthelloGame(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime);

	/**
	* Destroy OthelloGame object.
	*/
	~OthelloGame();

	/**
	* Get current integer of color specifying color of bot's discs.
	* @return m_color const reference of an integer.
	*/
	const int& getColor();

	/**
	* Get current state of a game board.
	* @return m_board const reference of a string.
	*/
	const std::string& getGameState();

	/**
	* Set state of a game board.
	* @param gameBoardIndex index to be changed.
	* @param disk to written on game board.
	*/
	void setGameState(const int& gameBoardIndex, const char& disk);

	/**
	* Get current player's score.
	* @return m_score const reference of an integer.
	*/
	const unsigned short& getScore();

	/**
	* Increment player's score.
	*/
	void incrementScore();

private:
	int m_color, m_maxDepth, m_heuristic, m_moveTime;
	const size_t m_boardWidth = 8, m_boardSize = 64;
	std::string m_board = "---------------------------OX------XO--------------------------------";
	unsigned short m_playerScore;

	friend std::ostream& operator<<(std::ostream&, const OthelloGame&);
};

/**
* Writes current game state to stream.
* @param lhs stream write
* @param rhs object OthelloGame to be written to stream
* @return lhs
*/
std::ostream& operator<<(std::ostream& lhs, const OthelloGame& rhs);

/**
* Makes all characters uppercase in given string.
* @param str string to make all characters uppercase.
*/
void toUpper(std::string& str);

/**
* Checks if string is an integer number.
* @param str string to check.
* @return true if str is int or false if str is not int
*/
bool isStringInt(const std::string& str);

/**
* Get parameters from command line arguments.
* @param argument count
* @param argument vector
* @return tuple of color, max depth, heuristic function, time
*/
std::tuple<int, int, int, int> getParameters(const int& argc, char* argv[]);

/**
* Processes command line arguments into a tuple of color, max depth, heuristic function and time.
* @param argument count
* @param argument vector
* @return tuple of color, max depth, heuristic function, time
*/
std::tuple<int, int, int, int> processArguments(const int& argc, char* argv[]);

/**
* Checks if given command line arguments are fit to be parameters for Othello game.
* @param color 
* @param maxDepth
* @param heuristic function
* @param moveTime
* @return 0 if arguments are fine or 1 if arguments are not fit for Othello game
*/
int checkParameters(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime);

/**
* Reads user's commands
* @param argument count
* @param argument vector
* @return 0 if arguments are fine or 1 if arguments are not fit for Othello game
*/
void readCommand(int argc, char* argv[]);

/**
* Gets index from valid user's command
* @param command is valid user's command 
* @return index to be used on Othello game board
*/
int getIndexFromCommand(const std::string& command);