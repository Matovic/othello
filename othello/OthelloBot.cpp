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

// 
GameNode::GameNode(const OthelloGame& node, const OthelloGame& player, const int& depth)
	: OthelloGame(node), m_depth{ depth }, m_player {player}
{
}

// 
GameNode::GameNode(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime,
	const std::string& gameState, const int& depth, const unsigned short& score, OthelloGame player)
	: OthelloGame(playerDisk, maxDepth, heuristic, moveTime, gameState, score), m_depth{ depth }, m_player{ player }
{
}

// 
GameNode::GameNode(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime,
	const int& depth, const unsigned short& score, OthelloGame player)
	: OthelloGame(playerDisk, maxDepth, heuristic, moveTime), m_depth{ depth }, m_player{ player }
{
	this->m_score = score;
}

// 
GameNode::~GameNode()
{
}

// 
const int& GameNode::getDepth()
{
	return this->m_depth;
}

//
OthelloGame& GameNode::getPlayer()
{
	return this->m_player;
}

// 
void GameNode::setPlayer(OthelloGame& player)
{
	this->m_player = player;
}

// 
GameNode& GameNode::operator=(OthelloGame& rhs)
{
	this->m_board = rhs.getGameState();
	this->m_score = rhs.getScore();
	return *this;
}

// 
GameNode& GameNode::operator=(GameNode& rhs)
{
	this->m_board = rhs.getGameState();
	this->m_score = rhs.getScore();
	this->m_player = rhs.getPlayer();
	return *this;
}

// Create OthelloBot object with specific parameters.
OthelloBot::OthelloBot(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime, const OthelloGame& player)
	: OthelloGame(playerDisk, maxDepth, heuristic, moveTime), m_currentGameNode{ GameNode(playerDisk, maxDepth, heuristic, moveTime, 
		0, 2, player) }, m_dequeGameNodes{ this->createTree() }, m_player { player }
{
}

// Destroy OthelloBot object.
OthelloBot::~OthelloBot()
{
}

// 
OthelloGame& OthelloBot::getPlayer()
{
	return this->m_player;
}

// 
std::deque<GameNode> OthelloBot::getDequeGameNodes()
{
	return this->m_dequeGameNodes;
}

// 
void OthelloBot::updateBot(OthelloGame& player)
{
	this->setGameState(player.getGameState());
	this->m_player = player;
	// this->m_currentGameNode = *this;
}

// 
std::deque<GameNode> OthelloBot::createTree()
{
	if (this->m_disk == 'O' && this->m_score == 2) 
		return std::deque<GameNode>();

	this->m_currentGameNode = *this;
	this->m_currentGameNode.setPlayer(this->getPlayer());
	std::deque<GameNode> dequeGameNodes = { this->m_currentGameNode };
	const char& opponentDisk = this->getPlayer().getDisk();

	for (int depth = 0, dequeIndex = 0; depth < this->m_maxDepth && !dequeGameNodes.empty(); ++dequeIndex, depth = dequeGameNodes[dequeIndex].getDepth())
	{
		std::cout << "\nDEEEEEEEEEEEPTH: " << depth << '\n';
		if (depth % 2 == 1)
		{
			std::vector<int> vectorValidMove = getValidMoves(dequeGameNodes[dequeIndex].getGameState(), opponentDisk, this->m_disk, true);

			// if there are not valid moves, game is over
			if (vectorValidMove.empty())
			{
				std::cout << "Empty vector!\n";
				break;
			}
			std::cout << "dequeGameNodes[" << dequeIndex << "]:\n";
			std::cout << dequeGameNodes[dequeIndex] << '\n';

			for (int validIndexMove : vectorValidMove)
			{
				GameNode oldGameState = dequeGameNodes[dequeIndex];
				dequeGameNodes.push_back(createGameNode(dequeGameNodes[dequeIndex], validIndexMove));
				dequeGameNodes[dequeIndex] = oldGameState;

				std::cout << "DEQUE[" << dequeGameNodes.size() - 1 << "]:\n";
				std::cout << dequeGameNodes[dequeGameNodes.size() - 1] << '\n';
			}
			continue;
		}
		std::vector<int> vectorValidMove = getValidMoves(dequeGameNodes[dequeIndex].getGameState(), this->m_disk, opponentDisk, true);

		// if there are not valid moves, game is over
		if (vectorValidMove.empty())
		{
			std::cout << "Empty vector!\n";
			break;
		}
		std::cout << "dequeGameNodes[" << dequeIndex << "]:\n";
		std::cout << dequeGameNodes[dequeIndex] << '\n';

		for (int validIndexMove : vectorValidMove)
		{
			GameNode oldGameState = dequeGameNodes[dequeIndex];
			dequeGameNodes.push_back(createGameNode(dequeGameNodes[dequeIndex], validIndexMove));
			dequeGameNodes[dequeIndex] = oldGameState;

			std::cout << "DEQUE[" << dequeGameNodes.size() - 1 << "]:\n";
			std::cout << dequeGameNodes[dequeGameNodes.size() - 1] << '\n';
		}
	}

	/*for (auto x : dequeGameNodes)
	{
		std::cout << x << '\n';
	}*/
	return dequeGameNodes;
}

// 
GameNode OthelloBot::createGameNode(GameNode& node, const int& validIndexMove)//, const char& disk)
{
	if (node.getDepth() % 2 == 1)
	{
		placeDisk(node.getPlayer(), node, validIndexMove);
	}
	else
	{
		placeDisk(node, node.getPlayer(), validIndexMove);
	}

	return GameNode(node, node.getPlayer(), node.getDepth() + 1);
}

// 
std::ostream& operator<<(std::ostream& lhs, const GameNode& rhs)
{
	lhs << "  a b c d e f g h";
	for (size_t i = 0, row = 0; i < 64; ++i)
	{
		if (i % 8 == 0)	lhs << '\n' << ++row << ' ';
		lhs << rhs.m_board[i] << ' ';
	}
	lhs << "\nDepth: " << rhs.m_depth << '\n';
	printScore(rhs.m_player, rhs);
	return lhs;
}