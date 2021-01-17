/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloGameLogic.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include "OthelloGameLogic.hpp"

// 
void moveDisk(OthelloBot& othelloBot, const std::string& command)
{
	std::cout << command << '\n';
	std::cout << '\n' << othelloBot << '\n';
}