/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloBot.cpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include <vector>

#include "OthelloBot.hpp"
#include "OthelloGameLogic.hpp"

GameNode::GameNode(const std::string& gameState, const int& depth) 
	: m_gameState{ gameState }, m_depth{ depth }
{
}

GameNode::~GameNode()
{
}

const std::string& GameNode::getGameState()
{
	return this->m_gameState;
}

const int& GameNode::getDepth()
{
	return this->m_depth;
}

// Create OthelloBot object with specific parameters.
OthelloBot::OthelloBot(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime) 
	: OthelloGame(playerDisk, maxDepth, heuristic, moveTime), m_currentGameNode{ GameNode(this->getGameState(), 0) }, m_d{ this->createTree() }
{
}

// Destroy OthelloBot object.
OthelloBot::~OthelloBot()
{
}

std::deque<GameNode> OthelloBot::createTree()
{
	// std::cout << this->m_currentGameNode << "\n";
	std::deque<GameNode> d = { this->m_currentGameNode };
	char opponentDisk = findDiskFromPlayer(this->getDisk());

	size_t i = 0;
	for (int depth = 0; depth < this->m_maxDepth && !d.empty(); depth = d[i].getDepth(), ++i)
	{
		std::vector<int> vectorValidMove = getValidMoves(d[i].getGameState(), this->m_disk, opponentDisk, true);

		// if there are not valid moves, game is over
		if (vectorValidMove.empty())
		{
			break;
		}

		for (int validIndexMove : vectorValidMove)
		{
			d.push_back(createGameNode(d[i], validIndexMove, this->m_disk));
		}
	}

	for (auto x : d)
	{
		std::cout << x << '\n';
	}
	return d;
}

GameNode OthelloBot::createGameNode(GameNode& node, const int& validIndexMove, const char& disk)
{
	std::string newGameState = node.getGameState();
	newGameState[validIndexMove] = disk;
	return GameNode(newGameState, node.getDepth() + 1);
}

std::ostream& operator<<(std::ostream& lhs, const GameNode& rhs)
{
	lhs << "  a b c d e f g h";
	for (size_t i = 0, row = 0; i < 64; ++i)
	{
		if (i % 8 == 0)	lhs << '\n' << ++row << ' ';
		lhs << rhs.m_gameState[i] << ' ';
	}
	lhs << rhs.m_depth << '\n';
	return lhs;
}