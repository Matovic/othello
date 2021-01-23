/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloPlayer.cpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include <vector>
#include "OthelloPlayer.hpp"
#include "OthelloGameLogic.hpp"

// Create OthelloPlayer object with specific parameters.
OthelloPlayer::OthelloPlayer(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime)
	: OthelloGame(color, maxDepth, heuristic, moveTime)
{
}

// Destroy OthelloPlayer object.
OthelloPlayer::~OthelloPlayer()
{
}

// Reads user's commands
void OthelloPlayer::readCommand()
{
	OthelloBot bot{this->m_disk, this->m_maxDepth, this->m_heuristic, this->m_moveTime};

	printScore(*this, bot);

	std::vector<int> vectorValidMove = getValidMoves(this->m_board, this->m_disk, bot.getDisk());

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
		int gameBoardIndex = getIndexFromCommand(command);
		if (!isIntInVector(vectorValidMove, gameBoardIndex))
		{
			std::cout << "Not possible move!\n";
			continue;
		}

		// new game state  with new placed disk
		placeDisk(*this, gameBoardIndex, this->m_disk);
		bot.setGameState(gameBoardIndex, this->m_disk);

		printScore(*this, bot);

		vectorValidMove = getValidMoves(this->m_board, this->m_disk, bot.getDisk());

		// if there are not valid moves, game is over
		if (vectorValidMove.empty())
		{
			std::cout << "\nGame ended! Your score is: " << this->m_score << ".\n";
			break;
		}
	}
}

// Prints game's score
void printScore(OthelloPlayer& player, OthelloBot& bot)
{
	std::cout << "Your score is: " << player.getScore() << ".\n";
	std::cout << "Bot's score is: " << bot.getScore() << ".\n";
	// std::cout << bot << '\n';
}