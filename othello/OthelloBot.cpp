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
#include <limits>
#include "OthelloBot.hpp"
#include "OthelloGameLogic.hpp"

// Create GameNode object with no parameters.
GameNode::GameNode() 
	: OthelloGame(0), m_depth{ -1 }, m_alpha{ std::numeric_limits<int>::min() }, m_beta{ std::numeric_limits<int>::max() }, 
	m_parentIndex { 0 }, m_leaf {false}
{
}

// Create GameNode object by copying another GameNode object.
GameNode::GameNode(const GameNode& node) 
	: OthelloGame(node), m_depth{ node.m_depth }, m_player{ node.m_player },m_alpha{ std::numeric_limits<int>::min() }, 
	m_beta{ std::numeric_limits<int>::max() }, m_parentIndex{ node.m_parentIndex }, m_leaf{ false }
{
}

// Create GameNode object by copying player's and bot's objects and specifying depth in graph.
GameNode::GameNode(const OthelloGame& opponent, const OthelloGame& player, const int& depth)
	: OthelloGame(opponent), m_depth{ depth }, m_player {player}, m_alpha{ std::numeric_limits<int>::min() }, 
	m_beta{ std::numeric_limits<int>::max() }, m_parentIndex{ 0 }, m_leaf{ false }
{
}

// Create GameNode object with specific parameters with given current gameState.
GameNode::GameNode(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime,
	const std::string& gameState, const int& depth, const unsigned short& score, OthelloGame player)
	: OthelloGame(playerDisk, maxDepth, heuristic, moveTime, gameState, score), m_depth{ depth }, m_player{ player },
	m_alpha{ std::numeric_limits<int>::min() }, m_beta{ std::numeric_limits<int>::max() }, m_parentIndex{ 0 }, m_leaf{ false }
{
}

// Create GameNode object with specific parameters without given current gameState.
GameNode::GameNode(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime,
	const int& depth, const unsigned short& score, OthelloGame player)
	: OthelloGame(playerDisk, maxDepth, heuristic, moveTime, score), m_depth{ depth }, m_player{ player }, 
	m_alpha{ std::numeric_limits<int>::min() }, m_beta{ std::numeric_limits<int>::max() }, m_parentIndex{ 0 }, m_leaf{ false }
{
}

// Destroy GameNode object.
GameNode::~GameNode()
{
}

// Getter for current node's depth.
const int& GameNode::getDepth()
{
	return this->m_depth;
}

// Getter for current node's version of player.
OthelloGame& GameNode::getPlayer()
{
	return this->m_player;
}

// Setter for current node's version of player.
void GameNode::setPlayer(OthelloGame& player)
{
	this->m_player = player;
}

// Getter for current node's parent index.
size_t& GameNode::getParentIndex()
{
	return this->m_parentIndex;
}

// Setter for current node's parent index.
void GameNode::setParentIndex(const size_t& parentIndex)
{
	this->m_parentIndex = parentIndex;
}

// Getter for current node's alpha value.
const int& GameNode::getAlpha()
{
	return this->m_alpha;
}

// Setter for current node's alpha value.
void GameNode::setAlpha(const int& alpha)
{
	this->m_alpha = alpha;
}

// Getter for current node's beta value.
const int& GameNode::getBeta()
{
	return this->m_beta;
}

// Getter for current node's beta value.
void GameNode::setBeta(const int& beta)
{
	this->m_beta = beta;
}

// Getter for current node's leaf.
const bool& GameNode::isLeaf()
{
	return this->m_leaf;
}

// Setter for current node's leaf.
void GameNode::setLeaf(const bool& leaf)
{
	this->m_leaf = leaf;
}

// Copy given OthelloGame object into another existing GameNode object.
GameNode& GameNode::operator=(OthelloGame& rhs)
{
	this->m_board = rhs.getGameState();
	this->m_score = rhs.getScore();
	return *this;
}

// Copy given GameNode object into another existing GameNode object.
GameNode& GameNode::operator=(GameNode& rhs)
{
	this->m_board = rhs.getGameState();
	this->m_score = rhs.getScore();
	this->m_player = rhs.getPlayer();
	this->m_alpha = rhs.getAlpha();
	this->m_beta = rhs.getBeta();
	this->m_parentIndex = rhs.getParentIndex();

	return *this;
}

// Create OthelloBot object with specific parameters.
OthelloBot::OthelloBot(const char& playerDisk, const int& maxDepth, const int& heuristic, const int& moveTime, const OthelloGame& player)
	: OthelloGame(playerDisk, maxDepth, heuristic, moveTime), m_currentGameNode{ GameNode(playerDisk, maxDepth, heuristic, moveTime, 
		0, 2, player) }, m_dequeGameNodes{ this->createTree() }, m_player{ player }, m_currentDequeIndex{ 0 }, m_timer{ 0 }
{
}

// Destroy OthelloBot object.
OthelloBot::~OthelloBot()
{
}

// Getter for current bot's verion of a player.
OthelloGame& OthelloBot::getPlayer()
{
	return this->m_player;
}

// Getter for current bot's deque of game node's.
std::deque<GameNode> OthelloBot::getDequeGameNodes()
{
	return this->m_dequeGameNodes;
}

// Getter for current bot's index of deque of game node's.
const size_t& OthelloBot::getDequeGameNodesIndex()
{
	return this->m_currentDequeIndex;
}

// Start counting time for m_timer.
void OthelloBot::startTimer()
{
	this->m_timer = clock();
}

// Getter for m_timer.
const clock_t& OthelloBot::getTimer()
{
	return this->m_timer;
}

// Updates bot based on player's choice.
void OthelloBot::updateBot(OthelloGame& player)
{
	this->setGameState(player.getGameState());
	this->m_player = player;
}

// Updates bot's m_dequeGameNodes.
void OthelloBot::updateDeque()
{
	while (this->m_currentDequeIndex < this->m_dequeGameNodes.size() && 
		this->getPlayer().getGameState() != this->m_dequeGameNodes[this->m_currentDequeIndex].getGameState())
	{
		++this->m_currentDequeIndex;
	}

	if (this->m_currentDequeIndex < m_dequeGameNodes.size() && this->m_dequeGameNodes[this->m_currentDequeIndex].getDepth() == this->m_maxDepth)
	{
		this->m_currentGameNode = this->m_dequeGameNodes[this->m_currentDequeIndex];
		this->m_currentDequeIndex = 0;
		this->m_dequeGameNodes = this->createTree();
	}

	else if (this->m_currentDequeIndex >= m_dequeGameNodes.size())
	{
		this->m_currentDequeIndex = 0;
		this->m_currentGameNode = this->m_dequeGameNodes[this->m_currentDequeIndex];
		this->m_dequeGameNodes = this->createTree();
		this->rateDeque();
	}
}

// Make move on a game board based on player's choice.
void OthelloBot::makeMove(OthelloGame& player)
{
	this->updateBot(player);
	this->m_timer = clock();
	if (this->getDequeGameNodes().empty())
	{
		this->m_dequeGameNodes = this->createTree();
		this->rateDeque();
	}
	else
		this->updateDeque();

	// find right node
	size_t bestStateIndex = this->m_currentDequeIndex + 1;
	while (bestStateIndex < this->m_dequeGameNodes.size() && this->m_currentDequeIndex != this->m_dequeGameNodes[bestStateIndex].getParentIndex())
	{
		++bestStateIndex; 
	}

	// find best child 
	for (size_t dequeIndex = bestStateIndex + 1; dequeIndex < this->m_dequeGameNodes.size() && 
		this->m_dequeGameNodes[bestStateIndex].getParentIndex() == this->m_dequeGameNodes[dequeIndex].getParentIndex(); 
		++dequeIndex)
	{
		if (this->m_dequeGameNodes[dequeIndex].getBeta() > this->m_dequeGameNodes[bestStateIndex].getBeta())
		{
			bestStateIndex = dequeIndex;
		}
	}

	// if there is a possible move, make it
	if (bestStateIndex < this->m_dequeGameNodes.size())
	{
		player.setGameState(this->m_dequeGameNodes[bestStateIndex].getGameState());
		player.setScore(this->m_dequeGameNodes[bestStateIndex].getPlayer().getScore());
		this->m_score = this->m_dequeGameNodes[bestStateIndex].getScore();
		this->m_currentDequeIndex = bestStateIndex;
	}
}

// Rate leafs for heuristic function.
void OthelloBot::rateLeafs()
{
	for (size_t dequeIndex = this->m_dequeGameNodes.size() - 1; dequeIndex > 0; --dequeIndex)
	{
		auto& node = this->m_dequeGameNodes[dequeIndex];

		if (!node.isLeaf()) continue;

		// minimax value for mini
		if (node.getDepth() % 2 == 1) node.setBeta(node.getScore());

		// minimax value for max
		else node.setAlpha(node.getScore());
	}
}

// Determines if disk is stable in up left corner.
int OthelloBot::checkUpLeftCorner(GameNode& node, const char& disk)
{
	// check board from up left corner to the right
	for (size_t boardIndex = 0; boardIndex < this->m_boardWidth; ++boardIndex)
	{
		// disk is already placed
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == disk)
			continue;

		// parent left up corner was free and now is taken by player
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == DiskState::EMPTY
			&& node.getGameState().at(boardIndex) == disk)
			return 1;

		// from left up corner to the right is an empty space or opponent disk
		if (node.getGameState().at(boardIndex) != disk)
			break;
	}

	// check board from up left corner down
	for (size_t boardIndex = 0; boardIndex < this->m_boardSize; boardIndex += this->m_boardWidth)
	{
		// disk is already placed
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == disk)
			continue;

		// parent left up corner was free and now is taken by player
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == DiskState::EMPTY
			&& node.getGameState().at(boardIndex) == disk)
			return 1;

		// from left up corner down is an empty space or opponent disk
		if (node.getGameState().at(boardIndex) != disk)
			break;
	}
	return 0;
}

// Determines if disk is stable in up right corner.
int OthelloBot::checkUpRightCorner(GameNode& node, const char& disk)
{
	// check board from up right corner to the left
	for (int boardIndex = static_cast<int>(this->m_boardWidth) - 1; boardIndex > -1; --boardIndex)
	{
		// disk is already placed
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == disk)
			continue;

		// parent right up corner was free and now is taken by player
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == DiskState::EMPTY
			&& node.getGameState().at(boardIndex) == disk)
			return 1;

		// from left up corner to the right is an empty space or opponent disk
		if (node.getGameState().at(boardIndex) != disk)
			break;
	}

	// check board from up right corner down
	for (size_t boardIndex = this->m_boardWidth - 1; boardIndex < this->m_boardSize; boardIndex += this->m_boardWidth)
	{
		// disk is already placed
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == disk)
			continue;

		// parent left up corner was free and now is taken by player
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == DiskState::EMPTY
			&& node.getGameState().at(boardIndex) == disk)
			return 1;

		// from left up corner down is an empty space or opponent disk
		if (node.getGameState().at(boardIndex) != disk)
			break;
	}
	return 0;
}

// Determines if disk is stable in down left corner.
int OthelloBot::checkDownLeftCorner(GameNode& node, const char& disk)
{
	// check board from down left corner to the right
	for (size_t boardIndex = 56; boardIndex < this->m_boardSize; ++boardIndex)
	{
		// disk is already placed
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == disk)
			continue;

		// parent left up corner was free and now is taken by player
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == DiskState::EMPTY
			&& node.getGameState().at(boardIndex) == disk)
			return 1;

		// from left up corner to the right is an empty space or opponent disk
		if (node.getGameState().at(boardIndex) != disk)
			break;
	}

	// check board from down left corner up
	for (int boardIndex = 56; boardIndex > -1; boardIndex -= static_cast<int>(this->m_boardWidth))
	{
		// disk is already placed
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == disk)
			continue;

		// parent left up corner was free and now is taken by player
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == DiskState::EMPTY
			&& node.getGameState().at(boardIndex) == disk)
			return 1;

		// from left up corner down is an empty space or opponent disk
		if (node.getGameState().at(boardIndex) != disk)
			break;
	}
	return 0;
}

// Determines if disk is stable in down right corner.
int OthelloBot::checkDownRightCorner(GameNode& node, const char& disk)
{
	// check board from down right corner to the left
	for (size_t boardIndex = this->m_boardSize - 1; boardIndex > 55; --boardIndex)
	{
		// disk is already placed
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == disk)
			continue;

		// parent right up corner was free and now is taken by player
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == DiskState::EMPTY
			&& node.getGameState().at(boardIndex) == disk)
			return 1;

		// from left up corner to the right is an empty space or opponent disk
		if (node.getGameState().at(boardIndex) != disk)
			break;
	}

	// check board from down right corner up
	for (int boardIndex = static_cast<int>(this->m_boardSize) - 1; boardIndex > 6; boardIndex -= static_cast<int>(this->m_boardWidth))
	{
		// disk is already placed
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == disk)
			continue;

		// parent left up corner was free and now is taken by player
		if (this->m_dequeGameNodes[node.getParentIndex()].getGameState().at(boardIndex) == DiskState::EMPTY
			&& node.getGameState().at(boardIndex) == disk)
			return 1;

		// from left up corner down is an empty space or opponent disk
		if (node.getGameState().at(boardIndex) != disk)
			break;
	}
	return 0;
}

// Determines if disk is stable and therefore in corner.
int OthelloBot::determineStableDisk(GameNode& node)
{
	char disk = node.getDisk();
	if (node.getDepth() % 2 == 0)
		disk = node.getPlayer().getDisk();

	if (this->checkUpLeftCorner(node, disk)) 
		return 1;

	if (this->checkUpRightCorner(node, disk))
		return 1;

	if (this->checkDownLeftCorner(node, disk))
		return 1;

	if (this->checkDownRightCorner(node, disk))
		return 1;

	return 0;
}

// Rate parents for heuristic function.
void OthelloBot::rateParents(const int heuristicConstant)
{
	for (size_t dequeIndex = this->m_dequeGameNodes.size() - 1; dequeIndex > 0; --dequeIndex)
	{
		auto& deque = this->m_dequeGameNodes;
		auto& node = this->m_dequeGameNodes[dequeIndex];

		// alpha - bot's decision
		if (deque[node.getParentIndex()].getDepth() % 2 == 1 && node.getAlpha() != std::numeric_limits<int>::min()
			&& deque[node.getParentIndex()].getBeta() > node.getAlpha())
		{
			// heuristic is 2 and therefore check out corners and determine stable disk
			if (heuristicConstant == HeuristicConstant::CORNERS && this->determineStableDisk(deque[node.getParentIndex()]))
				this->m_dequeGameNodes[node.getParentIndex()].setBeta(node.getAlpha() * heuristicConstant);

			// heuristic is 1 and therefore it is material count
			else this->m_dequeGameNodes[node.getParentIndex()].setBeta(node.getAlpha());
		}

		// beta - bot's prediction for player
		else if (deque[node.getParentIndex()].getDepth() % 2 == 0 && node.getBeta() != std::numeric_limits<int>::max()
			&& deque[node.getParentIndex()].getAlpha() < node.getBeta())
		{
			// heuristic is 2 and therefore check out corners and determine stable disk
			if (heuristicConstant == HeuristicConstant::CORNERS && this->determineStableDisk(deque[node.getParentIndex()]))
				this->m_dequeGameNodes[node.getParentIndex()].setAlpha(node.getBeta() * heuristicConstant);

			// heuristic is 1 and therefore it is material count
			else this->m_dequeGameNodes[node.getParentIndex()].setAlpha(node.getBeta());
		}
	}
}

// Heuristic function - rate deque with material count, meaning with current node's score.
void OthelloBot::rateDeque_MaterialCount()
{
	this->rateLeafs();
	this->rateParents(HeuristicConstant::MATERIAL_COUNT);
}

// Heuristic function - rate deque on a base of corners.
void OthelloBot::rateDeque_Corners()
{
	this->rateLeafs();
	this->rateParents(HeuristicConstant::CORNERS);
}

// Determines heuristic function based on given command line argument.
void OthelloBot::rateDeque()
{
	if (this->m_heuristic == 1)
		this->rateDeque_MaterialCount();

	else if (this->m_heuristic == 2)
		this->rateDeque_Corners();
}

// Init m_dequeGameNodes.
std::deque<GameNode> OthelloBot::createTree()
{
	if (this->m_disk == DiskState::WHITE && this->m_score == 2 && this->getPlayer().getScore() == 2) 
		return std::deque<GameNode>();

	this->m_currentGameNode = *this;
	this->m_currentGameNode.setPlayer(this->getPlayer());

	std::deque<GameNode> dequeGameNodes = { this->m_currentGameNode };
	const char& opponentDisk = this->getPlayer().getDisk();

	this->m_timer = clock();
	for (int dequeIndex = 0; !dequeGameNodes.empty(); ++dequeIndex)
	{
		if (static_cast<size_t>(dequeIndex) > dequeGameNodes.size() - 1) 
			break;

		if (((clock() - this->m_timer) / CLOCKS_PER_SEC) > this->m_moveTime / 2)
		{
			std::cout << "TIME: " << (clock() - this->m_timer) / CLOCKS_PER_SEC << '\n';
			const auto& parent = dequeGameNodes[dequeGameNodes.size() - 1].getParentIndex();
			for (size_t index = dequeGameNodes.size() - 2; index != parent; --index)
				dequeGameNodes[index].setLeaf(true);
			break;
		}

		const int& depth = dequeGameNodes[dequeIndex].getDepth();
		if (depth >= this->m_maxDepth) 
			break;

		std::vector<int> vectorValidMove;
		if (depth % 2 == 1)
		{
			vectorValidMove = getValidMoves(dequeGameNodes[dequeIndex].getGameState(), opponentDisk, this->m_disk, true);
		}
		else vectorValidMove = getValidMoves(dequeGameNodes[dequeIndex].getGameState(), this->m_disk, opponentDisk, true);

		// if there are not valid moves, game is over
		if (vectorValidMove.empty())
		{
			dequeGameNodes[dequeIndex].setLeaf(true);
			continue;
		}

		for (int validIndexMove : vectorValidMove)
		{
			GameNode oldGameState{ dequeGameNodes[dequeIndex] };
			dequeGameNodes.push_back(createGameNode(dequeGameNodes[dequeIndex], validIndexMove));
			dequeGameNodes[dequeIndex] = oldGameState;
			dequeGameNodes[dequeGameNodes.size() - 1].setParentIndex(dequeIndex);
			if (dequeGameNodes[dequeGameNodes.size() - 1].getDepth() == this->m_maxDepth)
				dequeGameNodes[dequeGameNodes.size() - 1].setLeaf(true);
		}
	}
	return dequeGameNodes;
}

// Creates a new GameNode for m_dequeGameNodes.
GameNode OthelloBot::createGameNode(GameNode& node, const int& validIndexMove)
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