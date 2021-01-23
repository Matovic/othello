/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file main.cpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include "OthelloPlayer.hpp"

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
	OthelloPlayer player{ color, maxDepth, heuristic, moveTime };
	player.readCommand();

	return 0;
}