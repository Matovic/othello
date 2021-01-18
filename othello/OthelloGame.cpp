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
#include "OthelloBot.hpp"
#include "OthelloGameLogic.hpp"

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
	// color = -1, maxDepth = -1, heuristic = -1, moveTime = -1 are all not valid
	int color = -1, maxDepth = -1, heuristic = -1, moveTime = -1;
	std::vector<std::string> args(argv + 1, argc + argv);

	for (std::string str : args)
	{
		toUpper(str);

		if (str.compare("--WHITE") == 0)
			color = 1;

		else if (str.compare("--BLACK") == 0)
			color = 0;

		else if (str.compare("--TIME") == 0)
			moveTime = 0;

		else if (str.compare("--FUNC") == 0)
			heuristic = 0;

		else if (str.compare("--DEPTH") == 0)
			maxDepth = 0;

		else if (maxDepth == 0 && isStringInt(str))
			maxDepth = std::stoi(str);

		else if (heuristic == 0 && isStringInt(str))
			heuristic = std::stoi(str);

		else if (moveTime == 0 && isStringInt(str))
			moveTime = std::stoi(str);

		else
		{
			std::cerr << "ERROR 00: Wrong parameters!\n";
			std::exit(EXIT_FAILURE);
		}
	}
	return std::make_tuple(color, maxDepth, heuristic, moveTime);
}

// Checks if given command line arguments are fit to be parameters for Othello game.
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

	if (heuristic < 1 || heuristic > 3)
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

// Reads user's commands
void readCommand(int argc, char* argv[])
{
	// color = -1, maxDepth = -1, heuristic = -1, moveTime = -1 are all not valid
	int color = -1, maxDepth = -1, heuristic = -1, moveTime = -1;

	std::tie(color, maxDepth, heuristic, moveTime) = getParameters(argc, argv);
	OthelloBot othelloBot{ color, maxDepth, heuristic, moveTime };
	//std::cout << othelloBot << '\n';

	getValidMoves(othelloBot);

	std::string command;
	while (std::getline(std::cin, command)) {
		toUpper(command);

		if (!command.compare("STOP"))
		{
			std::cout << "\nGame stopped, you lost!\n";
			break;
		}

		if (command.size() != 2 || COLUMN.find(command[0]) == std::string::npos || ROW.find(command[1]) == std::string::npos)
		{
			std::cout << "Not valid command!\n";
			continue;
		}
		moveDisk(othelloBot, command);

		getValidMoves(othelloBot);
	}
}