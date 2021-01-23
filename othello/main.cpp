/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file main.cpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include "OthelloGame.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 8)
	{
		std::cerr << "ERROR 00: Wrong parameters!\n";
		return 1;
	}
	readCommand(argc, argv);
	return 0;
}