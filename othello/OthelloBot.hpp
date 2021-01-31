/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
* 
* @file OthelloBot.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include <string>
#include <deque>
#include <memory>
#include <ctime>
#include "OthelloGame.hpp"

/**
* Class GameNode representing possible game state
*/
class GameNode : public OthelloGame
{
public:
	/**
	* Create GameNode object with no parameters.
	*/
	GameNode();

	/**
	* Create GameNode object by copying another GameNode object.
	* @param node object to be copied.
	*/
	GameNode(const GameNode& node);

	/**
	* Create GameNode object by copying player's and bot's objects and specifying depth in graph.
	* @param opponent object representing bot.
	* @param player object to be stored.
	* @param depth specifying current node's depth in graph.
	*/
	GameNode(const OthelloGame& opponent, const OthelloGame& player, const int& depth);

	/**
	* Create GameNode object with specific parameters with given current gameState.
	* @param playerDisk char to specify color of bot's disk.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	* @param depth specifying current node's depth in graph.
	* @param gameState to specify current Othello game board.
	* @param score to specify current player's score.
	* @param player object to be stored.
	*/
	GameNode(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime, 
		const std::string& gameState, const int& depth, const unsigned short& score, OthelloGame player);

	/**
	* Create GameNode object with specific parameters without given current gameState.
	* @param playerDisk char to specify color of bot's disk.
	* @param maxDepth integer to specify depth of minmax.
	* @param heuristic integer to specify heuristic function.
	* @param moveTime integer to specify time of player's move.
	* @param depth specifying current node's depth in graph.
	* @param score to specify current player's score.
	* @param player object to be stored.
	*/
	GameNode(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime,
		const int& depth, const unsigned short& score, OthelloGame player);

	/**
	* Destroy GameNode object.
	*/
	~GameNode();

	/**
	* Getter for current node's depth.
	* @return m_depth
	*/
	const int& getDepth();

	/**
	* Getter for current node's version of player.
	* @return m_player
	*/
	OthelloGame& getPlayer();

	/**
	* Setter for current node's version of player.
	* @param player new object to be set as m_player.
	*/
	void setPlayer(OthelloGame& player);

	/**
	* Getter for current node's parent index.
	* @return m_parentIndex.
	*/
	size_t& getParentIndex();

	/**
	* Setter for current node's parent index.
	* @param parentIndex to be set as m_parentIndex.
	*/
	void setParentIndex(const size_t& parentIndex);

	/**
	* Getter for current node's alpha value.
	* @return m_alpha.
	*/
	const int& getAlpha();

	/**
	* Setter for current node's alpha value.
	* @returnalpha to be set as  m_alpha.
	*/
	void setAlpha(const int& alpha);

	/**
	* Getter for current node's beta value.
	* @return m_beta.
	*/
	const int& getBeta();

	/**
	* Getter for current node's beta value.
	* @return beta to be set as m_beta.
	*/
	void setBeta(const int& beta);

	/**
	* Getter for current node's leaf.
	* @return true if node is a leaf.
	*/
	const bool& isLeaf();

	/**
	* Setter for current node's leaf.
	* @param leaf to be set as m_leaf.
	*/
	void setLeaf(const bool& leaf);

	/**
	* Copy given OthelloGame object into another existing GameNode object.
	* @param rhs object OthelloGame to be copied
	* @return this object
	*/
	GameNode& operator=(OthelloGame& rhs);

	/**
	* Copy given GameNode object into another existing GameNode object.
	* @param rhs object GameNode to be copied
	* @return this object
	*/
	GameNode& operator=(GameNode& rhs);

private:
	OthelloGame m_player;
	int m_depth;
	int m_alpha, m_beta;
	size_t m_parentIndex;
	bool m_leaf;

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

	/**
	* Getter for current bot's deque of game node's.
	* @return m_dequeGameNodes.
	*/
	std::deque<GameNode> getDequeGameNodes();

	/**
	* Init m_dequeGameNodes.
	* @return queue of game node's.
	*/
	std::deque<GameNode> createTree();

	/**
	* Make move on a game board based on player's choice.
	* @param player to specify new state of an Othello game board.
	*/
	void makeMove(OthelloGame& player);

	/**
	* Getter for current bot's verion of a player.
	* @return m_player.
	*/
	OthelloGame& getPlayer();

private:
	OthelloGame m_player;
	GameNode m_currentGameNode;
	std::deque<GameNode> m_dequeGameNodes;
	size_t m_currentDequeIndex;
	clock_t m_timer;

	/**
	* Creates a new GameNode for m_dequeGameNodes.
	* @param node is current GameNode.
	* @param validIndexMove is bot's possible move on a game board.
	* @return new object of GameNode.
	*/
	GameNode createGameNode(GameNode& node, const int& validIndexMove);

	/**
	* Updates bot based on player's choice.
	* @param player to specify new state of an Othello game board and also new score.
	*/
	void updateBot(OthelloGame& player);

	/**
	* Updates bot's m_dequeGameNodes.
	*/
	void updateDeque();

	/**
	* Heuristic function - material count.
	*/
	void rateDeque();
};

