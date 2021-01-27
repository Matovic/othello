/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
* 
* @file OthelloBot.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include "OthelloGame.hpp"
#include <string>
#include <deque>

class GameNode : public OthelloGame
{
public:

	GameNode(const OthelloGame& node, const OthelloGame& player, const int& depth);

	GameNode(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime, 
		const std::string& gameState, const int& depth, const unsigned short& score, OthelloGame player);

	GameNode(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime,
		const int& depth, const unsigned short& score, OthelloGame player);

	~GameNode();

	const int& getDepth();

	OthelloGame& getPlayer();

	void setPlayer(OthelloGame& player);

	GameNode& operator=(OthelloGame& rhs);

	GameNode& operator=(GameNode& rhs);

private:
	OthelloGame m_player;
	int m_depth;

	friend std::ostream& operator<<(std::ostream& lhs, const GameNode& rhs);
};

/**
* Class OthelloBot representing player's opponent
*/
class OthelloBot : public OthelloGame
{
public:
	/**
	* Create OthelloBot object with specific parameters.
	* @param playerDisk char to specify color of bot's disk based on player's disk.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	*/
	OthelloBot(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime, const OthelloGame& player);

	/**
	* Destroy OthelloBot object.
	*/
	~OthelloBot();

	std::deque<GameNode> getDequeGameNodes();

	std::deque<GameNode> createTree();

	void updateBot(OthelloGame& player);

	OthelloGame& getPlayer();

private:
	OthelloGame m_player;
	GameNode m_currentGameNode;
	std::deque<GameNode> m_dequeGameNodes;

	GameNode createGameNode(GameNode& node, const int& validIndexMove);//, const char& disk);
};

