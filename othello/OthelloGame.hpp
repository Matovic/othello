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
* Class OthelloGame representing Othello game
*/
class OthelloGame
{
public:
	/**
	* Create OthelloGame object with specific parameters.
	* @param color integer to specify color of player's disk.
	* 1 - white color.
	* 0 - black color.
	* -1 - not valid command, exit program.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	*/
	OthelloGame(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime);

	/**
	* Create OthelloGame object with specific parameters.
	* @param playerDisk char to specify color of bot's disk.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	*/
	OthelloGame(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime);

	OthelloGame(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime,
		const std::string& gameState, const unsigned short& score);

	OthelloGame(const OthelloGame& node);

	OthelloGame() = default;

	/**
	* Destroy OthelloGame object.
	*/
	~OthelloGame();

	/**
	* Get current char of disk specifying color of bot's discs.
	* @return m_color const reference of an integer.
	*/
	const char& getDisk();

	/**
	* Get current state of a game board.
	* @return m_board const reference of a string.
	*/
	const std::string& getGameState();

	/**
	* Set state of a game board with one character.
	* @param gameBoardIndex index to be changed.
	* @param disk to written on game board.
	*/
	void setGameState(const int& gameBoardIndex, const char& disk);

	/**
	* Set state of a game board with new string.
	* @param gameBoard new game board state string.
	*/
	void setGameState(const std::string& gameBoard);

	/**
	* Get current player's score.
	* @return m_score const reference of an integer.
	*/
	const unsigned short& getScore();

	/**
	* Increment player's score.
	*/
	void incrementScore();

	/**
	* Decrement player's score.
	*/
	void decrementScore();

	OthelloGame& operator=(OthelloGame& rhs);

protected:
	char m_disk;
	int m_maxDepth, m_heuristic, m_moveTime;

	const size_t m_boardWidth = 8, m_boardSize = 64;
	std::string m_board = "---------------------------OX------XO--------------------------------";
	unsigned short m_score;

	friend std::ostream& operator<<(std::ostream&, const OthelloGame&); 
	friend void printScore(const OthelloGame& player, const OthelloGame& bot);
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
* Checks if given command line arguments are fit to be parameters for an Othello game.
* @param color 
* @param maxDepth
* @param heuristic function
* @param moveTime
* @return 0 if arguments are fine or 1 if arguments are not fit for Othello game
*/
int checkParameters(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime);

/**
* Checks if given command line argument is correct number for an Othello game.
* @param consoleSwitch
* @return std::stoi(consoleSwitch) if consoleSwitch is fine or -2 if consoleSwitch is not fit for Othello game
*/
int checkNumberOnConsoleSwitch(const std::string consoleSwitch);

/**
* Gets index from valid user's command.
* @param command is valid user's command 
* @return index to be used on Othello game board
*/
int getIndexFromCommand(const std::string& command);

/**
* Gets disk on an Othello game board from given color.
* @param color to specify disk on an Othello game board
* @return char representing disk color
*/
char findDisk(const int& color);

/**
* Gets disk on an Othello game board from given player'ð disk.
* @param playerDisk to specify disk for bot on an Othello game board
* @return char representing disk color
*/
char findDiskFromPlayer(const char& playerDisk);

/**
* Prints game's score
* @param player for printing player's score
* @param bot for printing bot's score
*/
void printScore(const OthelloGame& player, const OthelloGame& bot);