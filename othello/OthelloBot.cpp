/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloBot.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include "OthelloBot.hpp"

// Create Othello bot with given color
OthelloBot::OthelloBot(const int& color) : m_color{ color }
{
}

// Destroy Othello bot object.
OthelloBot::~OthelloBot()
{
}

// Get current integer of color specifying color of bot's discs.
const int& OthelloBot::getColor()
{
	return m_color;
}

// Get current state of a game board.
const std::string& OthelloBot::getGameState()
{
	return m_game;
}

// Print current game state on console
void OthelloBot::printGame()
{
	std::cout << "  a b c d e f g h\n";
	int row = 1;
	std::cout << row++ << ' ';
	for (size_t i = 0; i < 64; ++i)
	{
		if (i != 0 && (i % 8 == 0))
		{
			std::cout << '\n' << row << ' ';
			++row;
		}
		std::cout << m_game[i] << ' ';
	}
	std::cout << '\n';
}
