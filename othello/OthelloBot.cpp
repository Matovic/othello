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
OthelloBot::OthelloBot(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime) 
	: m_color{ color }, m_maxDepth{ maxDepth }, m_heuristic{ heuristic }, m_moveTime{ moveTime }
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

// Writes current game state to stream.
std::ostream& operator<<(std::ostream& lhs, const OthelloBot& rhs)
{
	lhs << "  a b c d e f g h";
	for (size_t i = 0, row = 0; i < 64; ++i)
	{
		if (i % 8 == 0)	lhs << '\n' << ++row << ' ';
		lhs << rhs.m_game[i] << ' ';
	}
	lhs << '\n';
	return lhs;
}