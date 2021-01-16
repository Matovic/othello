/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloBot.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include <string>
//#include <algorithm>
#include "OthelloBot.hpp"
#include "OthelloGame.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 8)
	{
		std::cerr << "ERROR 00: Wrong parameters!\n";
		return 1;
	}

	// color = -1, maxDepth = -1, heuristic = -1, moveTime = -1 are all not valid
	int color = -1, maxDepth = -1, heuristic = -1, moveTime = -1;

	std::tie(color, maxDepth, heuristic, moveTime) = getParameters(argc, argv);
	OthelloBot othelloBot{ color };
	othelloBot.printGame();

	std::string command; 
	std::string column = "ABCDEFGH", row = "12345678";
	while (std::getline(std::cin, command)) {
		toUpper(command);

		if (!command.compare("STOP"))
		{
			std::cout << "\nGame stopped, you lost!\n";
			break;
		}

		if (command.size() != 2 || column.find(command[0]) == std::string::npos || row.find(command[1]) == std::string::npos)
		{
			std::cout << "Not valid command!\n";
			continue;
		}

		//TODO: process command

		//std::cout << command[0] << ' ' << command[1];
	}
	return 0;
}