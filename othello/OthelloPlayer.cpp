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

// Prints welcoming text for user with info about a game.
void OthelloPlayer::welcomeText()
{
	std::cout << "\n\tWelcome at a game of Othello!";
	std::cout << "\n\n\tTo place a disk simply enter letter of a collumn and number of a row, e.g d3.";
	std::cout << "\n\tTo stop just type stop.";
	std::cout << "\n\tTo see the best possible path of choice just enter print.";
	std::cout << "\n\n\tHave a fun!\n\n";
}

// Reads user's commands
void OthelloPlayer::readCommand()
{
	this->welcomeText();
	OthelloBot bot{this->m_disk, this->m_maxDepth, this->m_heuristic, this->m_moveTime, *this};
	printScore(*this, bot);

	if (this->getDisk() == DiskState::WHITE)
	{
		std::cout << *this << '\n';
		bot.makeMove(*this);
		printScore(*this, bot);
	}
	std::vector<int> vectorValidMove = getValidMoves(this->m_board, this->m_disk, bot.getDisk(), false);

	std::string command;
	while (std::getline(std::cin, command)) {
		toUpper(command);

		if (!command.compare("STOP"))
		{
			std::cout << "\nYou ended the game!\n";
			printScore(*this, bot);
			break;
		}

		if (!command.compare("PRINT"))
		{
			if (this->printBestPath(bot))
				std::cout << "\nFirst make a move.\n";
			printScore(*this, bot);
			std::string possibleGameState = this->m_board;
			showPossibleMoves(possibleGameState, vectorValidMove);
			continue;
		}

		if (command.size() != 2 || COLUMN_CLI.find(command[0]) == std::string::npos || ROW_CLI.find(command[1]) == std::string::npos)
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
		placeDisk(*this, bot, gameBoardIndex);
		printScore(*this, bot);
		std::cout << *this << '\n';

		bot.makeMove(*this);
		printScore(*this, bot);

		vectorValidMove = getValidMoves(this->m_board, this->m_disk, bot.getDisk(), false);

		// if there are not valid moves, game is over
		if (vectorValidMove.empty())
		{
			std::cout << "\nGame over!\n"; 
			printScore(*this, bot);
			break;
		}
	}
}

// Prints best possible path for player.
int OthelloPlayer::printBestPath(OthelloBot& bot)
{
	if (bot.getDequeGameNodes().empty())
		return 1;
	std::cout << "\nThe best path for you is:\n";

	bot.startTimer();
	for (size_t nodeIndex = bot.getDequeGameNodesIndex(), parentIndex = nodeIndex;
		nodeIndex < bot.getDequeGameNodes().size(); ++nodeIndex)
	{
		if (((clock() - bot.getTimer()) / CLOCKS_PER_SEC) > this->m_moveTime)
		{
			std::cout << "No more time to look for another game states.\n\n";
			return 0;
		}

		// find right node
		if (bot.getDequeGameNodes().at(nodeIndex).getParentIndex() != parentIndex)
			continue;

		// find best child 
		size_t dequeIndex = nodeIndex + 1;
		for (; bot.getDequeGameNodes().at(nodeIndex).getParentIndex() == bot.getDequeGameNodes().at(dequeIndex).getParentIndex();
			++dequeIndex)
		{
			if (dequeIndex >= bot.getDequeGameNodes().size())
			{
				std::cout << "No more game states are available\n.";
				return 0;
			}

			if (bot.getDequeGameNodes().at(parentIndex).getDepth() % 2 == 0 && 
				bot.getDequeGameNodes().at(dequeIndex).getAlpha() > bot.getDequeGameNodes().at(nodeIndex).getAlpha() || 
				bot.getDequeGameNodes().at(parentIndex).getDepth() % 2 == 1 &&
				bot.getDequeGameNodes().at(dequeIndex).getBeta() > bot.getDequeGameNodes().at(nodeIndex).getBeta())
			{
				nodeIndex = dequeIndex;
			}
		}
		parentIndex = nodeIndex;
		nodeIndex = dequeIndex;
		std::cout << bot.getDequeGameNodes().at(parentIndex) << '\n';
	}
	return 0;
}