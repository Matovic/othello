/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloGame.cpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include <vector>
#include "OthelloGame.hpp"
#include "OthelloGameLogic.hpp"

// Create Othello bot with given color
OthelloGame::OthelloGame(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime)
	: m_disk{ findDisk(color) }, m_maxDepth{ maxDepth }, m_heuristic{ heuristic }, m_moveTime{ moveTime }, m_score{ 2 }
{
}

// Create OthelloGame object with specific parameters.
OthelloGame::OthelloGame(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime)
	: m_disk{ findDiskFromPlayer(playerDisk) }, m_maxDepth{ maxDepth }, m_heuristic{ heuristic }, m_moveTime{ moveTime }, m_score{ 2 }
{
}

// Destroy Othello bot object.
OthelloGame::~OthelloGame()
{
}

// Get current char of disk specifying color of bot's discs.
const char& OthelloGame::getDisk()
{
	return this->m_disk;
}

// Get current state of a game board.
const std::string& OthelloGame::getGameState()
{
	return this->m_board;
}

// Set state of a game board.
void OthelloGame::setGameState(const int& gameBoardIndex, const char& disk)
{
	this->m_board[gameBoardIndex] = disk;
}

// Set state of a game board with new string.
void OthelloGame::setGameState(const std::string& gameBoard)
{
	this->m_board = gameBoard;
}

// Get current player's score.
const unsigned short& OthelloGame::getScore()
{
	return this->m_score;
}

// Increment player's score.
void OthelloGame::incrementScore()
{
	++this->m_score;
}

// Decrement player's score.
void OthelloGame::decrementScore()
{
	--this->m_score;
}

// Writes current game state to stream.
std::ostream& operator<<(std::ostream& lhs, const OthelloGame& rhs)
{
	lhs << "  a b c d e f g h";
	for (size_t i = 0, row = 0; i < rhs.m_boardSize; ++i)
	{
		if (i % rhs.m_boardWidth == 0)	lhs << '\n' << ++row << ' ';
		lhs << rhs.m_board[i] << ' ';
	}
	lhs << '\n';
	return lhs;
}

// Makes all characters uppercase in given string.
void toUpper(std::string& str)
{
	for (char& c : str) c = static_cast<char>(std::toupper(c));
}

// Checks if string is an integer number.
bool isStringInt(const std::string& str)
{
	for (auto it = str.begin(); it != str.end(); ++it)
		if (std::isdigit(*it) == 0) return false;

	return !str.empty();
}

// Checks if given command line argument is correct number for an Othello game.
int checkNumberOnConsoleSwitch(const std::string consoleSwitch)
{
	if (!isStringInt(consoleSwitch))
		return -2;
	return std::stoi(consoleSwitch);
}

// Get parameters from command line arguments.
std::tuple<int, int, int, int> getParameters(const int& argc, char* argv[])
{
	// color = -1, maxDepth = -1, heuristic = -1, moveTime = -1 are all not valid
	int color = -1, maxDepth = -1, heuristic = -1, moveTime = -1;
	std::tie(color, maxDepth, heuristic, moveTime) = processArguments(argc, argv);

	if (maxDepth == -1) maxDepth = 15;
	if (heuristic == -1) heuristic = 2;
	if (moveTime == -1) moveTime = 15;

	if (checkParameters(color, maxDepth, heuristic, moveTime))
		std::exit(EXIT_FAILURE);

	return std::make_tuple(color, maxDepth, heuristic, moveTime);
}

// Processes command line arguments into a tuple of color, max depth, heuristic function and time.
std::tuple<int, int, int, int> processArguments(const int& argc, char* argv[])
{
	int color = -1, maxDepth = -1, heuristic = -1, moveTime = -1;
	std::vector<std::string> args(argv + 1, argc + argv);

	for (std::string consoleSwitch : args)
	{
		toUpper(consoleSwitch);

		// check given numbers
		if (maxDepth == 0)
			maxDepth = checkNumberOnConsoleSwitch(consoleSwitch);

		else if (heuristic == 0)
			heuristic = checkNumberOnConsoleSwitch(consoleSwitch);

		else if (moveTime == 0)
			moveTime = checkNumberOnConsoleSwitch(consoleSwitch);

		// check given commands
		else if (consoleSwitch.compare("--WHITE") == 0 && color == -1)
			color = 1;

		else if (consoleSwitch.compare("--BLACK") == 0 && color == -1)
			color = 0;

		else if (consoleSwitch.compare("--TIME") == 0 && moveTime == -1)
			moveTime = 0;

		else if (consoleSwitch.compare("--FUNC") == 0 && heuristic == -1)
			heuristic = 0;

		else if (consoleSwitch.compare("--DEPTH") == 0 && maxDepth == -1)
			maxDepth = 0;

		else
		{
			std::cerr << "ERROR 00: Wrong parameters!\n";
			std::exit(EXIT_FAILURE);
		}
	}
	return std::make_tuple(color, maxDepth, heuristic, moveTime);
}

// Checks if given command line arguments are fit to be parameters for an Othello game.
int checkParameters(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime)
{
	if (color < 0)
	{
		std::cerr << "ERROR 01: Color not found!\n";
		return 1;
	}

	if (maxDepth < 5 || maxDepth > 15)
	{
		std::cerr << "ERROR 02: Incorrect depth! Depth can be from 5 to 15.\n";
		return 1;
	}

	if (heuristic < 1 || heuristic > 2)
	{
		std::cerr << "ERROR 03: Heuristic function is not known!\n";
		return 1;
	}

	if (moveTime < 5 || moveTime > 30)
	{
		std::cerr << "ERROR 04: Incorrect time! Time can be from 5 to 30.\n";
		return 1;
	}
	return 0;
}

// Gets index from valid user's command.
int getIndexFromCommand(const std::string& command)
{
	int columnIndex = command[0] - 'A', rowIndex = command[1] - '1';
	return rowIndex * 8 + columnIndex;
}

// Gets disk on an Othello game board from given color.
char findDisk(const int& color)
{
	char disk = 'X';
	if (color) disk = 'O';
	return disk;
}

// Gets disk on an Othello game board from given player's disk.
char findDiskFromPlayer(const char& playerDisk)
{
	char disk = 'X';
	if (playerDisk == 'X') disk = 'O';
	return disk;
}