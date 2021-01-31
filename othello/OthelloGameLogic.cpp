/**
* Course: Application programming in C++ 2020/2021
* Purpose: Othello game logic with move operations.
*
* @file OthelloGameLogic.cpp
* @author Erik Matovic
* @version 31/01/2021
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "OthelloGameLogic.hpp"

// Checks possible move on Othello board by going left.
int checkLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex % 8 != 0 && gameBoard[diskIndex] == opponentDisk)
		return checkLeft(gameBoard, diskIndex + GameDirection::LEFT, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going right.
int checkRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex % 8 != 7 && gameBoard[diskIndex] == opponentDisk)
		return checkRight(gameBoard, diskIndex + GameDirection::RIGHT, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going UP.
int checkUp(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex > 7 && gameBoard[diskIndex] == opponentDisk)
		return checkUp(gameBoard, diskIndex + GameDirection::UP, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going down.
int checkDown(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex < 56 && gameBoard[diskIndex] == opponentDisk)
		return checkDown(gameBoard, diskIndex + GameDirection::DOWN, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going diagonal UP and left.
int checkDiagonalUpLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex > 7 && diskIndex % 8 != 0 && gameBoard[diskIndex] == opponentDisk)
		return checkDiagonalUpLeft(gameBoard, diskIndex + GameDirection::DIAGONAL_UP_LEFT, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going diagonal UP and right.
int checkDiagonalUpRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex > 7 && diskIndex % 8 != 7 && gameBoard[diskIndex] == opponentDisk)
		return checkDiagonalUpRight(gameBoard, diskIndex + GameDirection::DIAGONAL_UP_RIGHT, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going diagonal down and left.
int checkDiagonalDownLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex < 56 && diskIndex % 8 != 0 && gameBoard[diskIndex] == opponentDisk)
		return checkDiagonalDownLeft(gameBoard, diskIndex + GameDirection::DIAGONAL_DOWN_LEFT, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks possible move on Othello board by going diagonal down and right.
int checkDiagonalDownRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	if (diskIndex < 56 && diskIndex % 8 != 7 && gameBoard[diskIndex] == opponentDisk)
		return checkDiagonalDownRight(gameBoard, diskIndex + GameDirection::DIAGONAL_DOWN_RIGHT, opponentDisk);

	if (gameBoard[diskIndex] == '-')
		return static_cast<int>(diskIndex);

	return -1;
}

// Checks all directions for possible moves on Othello board.
std::vector<int> checkDirections(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk)
{
	std::vector<int> vectorValidMoves;
	int tmp = -1;

	// check UP
	if (diskIndex > 7 && gameBoard[diskIndex + GameDirection::UP] == opponentDisk)
	{
		tmp = checkUp(gameBoard, diskIndex + GameDirection::UP, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check down
	if (diskIndex < 56 && gameBoard[diskIndex + GameDirection::DOWN] == opponentDisk)
	{
		tmp = checkDown(gameBoard, diskIndex + GameDirection::DOWN, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check left
	if (diskIndex % 8 != 0 && gameBoard[diskIndex + GameDirection::LEFT] == opponentDisk)
	{
		tmp = checkLeft(gameBoard, diskIndex + GameDirection::LEFT, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check right
	if (diskIndex % 8 != 7 && gameBoard[diskIndex + GameDirection::RIGHT] == opponentDisk)
	{
		tmp = checkRight(gameBoard, diskIndex + GameDirection::RIGHT, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check diagonal UP-left
	if (diskIndex > 7 && diskIndex % 8 != 0 && gameBoard[diskIndex + GameDirection::DIAGONAL_UP_LEFT] == opponentDisk)
	{
		tmp = checkDiagonalUpLeft(gameBoard, diskIndex + GameDirection::DIAGONAL_UP_LEFT, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check diagonal UP-right
	if (diskIndex > 7 && diskIndex % 8 != 7 && gameBoard[diskIndex + GameDirection::DIAGONAL_UP_RIGHT] == opponentDisk)
	{
		tmp = checkDiagonalUpRight(gameBoard, diskIndex + GameDirection::DIAGONAL_UP_RIGHT, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check diagonal down-left
	if (diskIndex < 56 && diskIndex % 8 != 0 && gameBoard[diskIndex + GameDirection::DIAGONAL_DOWN_LEFT] == opponentDisk)
	{
		tmp = checkDiagonalDownLeft(gameBoard, diskIndex + GameDirection::DIAGONAL_DOWN_LEFT, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	// check diagonal down-right
	if (diskIndex < 56 && diskIndex % 8 != 7 && gameBoard[diskIndex + GameDirection::DIAGONAL_DOWN_RIGHT] == opponentDisk)
	{
		tmp = checkDiagonalDownRight(gameBoard, diskIndex + GameDirection::DIAGONAL_DOWN_RIGHT, opponentDisk);
		if (tmp != -1 && !isIntInVector(vectorValidMoves, tmp))
			vectorValidMoves.insert(vectorValidMoves.end(), tmp);
	}

	return vectorValidMoves;
}

// Gets all possible moves on Othello board.
std::vector<int> getValidMoves(const std::string& board, const char& disk, const char& opponentDisk, const bool& isBot)
{
	std::string possibleGameState = board;
	std::vector<int> vectorValidMoves;										// possible indexes of game state

	size_t pos = 0;
	while (1)
	{
		size_t movePosition = possibleGameState.find(disk, pos);			// position of my disk

		if (movePosition == std::string::npos) 
			break;

		std::vector<int> tmp = checkDirections(possibleGameState, movePosition, opponentDisk);
		vectorValidMoves.insert(vectorValidMoves.end(), tmp.begin(), tmp.end());
		
		pos = movePosition + 1;
	}
	if (!isBot) showPossibleMoves(possibleGameState, vectorValidMoves);
	return vectorValidMoves;
}

// Shows possible moves to the player on game board.
void showPossibleMoves(std::string& possibleGameState, const std::vector<int>& vectorValidMoves)
{
	for (int x : vectorValidMoves)
		possibleGameState[x] = '*';
	std::cout << '\n';
	printGameState(possibleGameState);
}

// Flips all disks on given direction.
void flipDiskOnGivenDirection(OthelloGame& player, OthelloGame& opponent, int& diskIndexToChange, const int direction)
{
	const std::string& gameBoard = player.getGameState();
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();

	while (diskIndexToChange > 0 && gameBoard[diskIndexToChange] == opponentDisk)
	{
		player.setGameState(diskIndexToChange, disk);
		player.incrementScore();
		opponent.decrementScore();
		diskIndexToChange += direction;
	}
}

// Checks down.
int checkFlipDown(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	if (gameBoardIndex > 55)
		return -1;

	int diskIndex = gameBoardIndex + GameDirection::DOWN, diskIndexToChange = -1;
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();
	const std::string& gameBoard = player.getGameState();

	while (1)
	{
		if (diskIndex < 56 && gameBoard[diskIndex] == opponentDisk)
		{
			diskIndex += GameDirection::DOWN;
			diskIndexToChange = -2;
		}

		else if (diskIndexToChange == -2 && gameBoard[diskIndex] == disk)
			return diskIndex - GameDirection::DOWN;

		//else if (diskIndexToChange == -1 || gameBoard[diskIndex] == '-')
		else return -1;
	}
	return -1;
}

// Checks up.
int checkFlipUp(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	if (gameBoardIndex < 8)
		return -1;

	int diskIndex = gameBoardIndex + GameDirection::UP, diskIndexToChange = -1;
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();
	const std::string& gameBoard = player.getGameState();

	while (1)
	{
		if (diskIndex > 7 && gameBoard[diskIndex] == opponentDisk)
		{
			diskIndex += GameDirection::UP;
			diskIndexToChange = -2;
		}

		else if (diskIndexToChange == -2 && gameBoard[diskIndex] == disk)
			return diskIndex - GameDirection::UP;

		//else if (diskIndexToChange == -1 || gameBoard[diskIndex] == '-')
		else return -1;
	}
	return -1;
}

// Checks left.
int checkFlipLeft(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	if (gameBoardIndex % 8 == 0)
		return -1;

	int diskIndex = gameBoardIndex + GameDirection::LEFT, diskIndexToChange = -1;
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();
	const std::string& gameBoard = player.getGameState();

	while (diskIndex > -1)
	{
		if (diskIndex % 8 != 0 && gameBoard[diskIndex] == opponentDisk)
		{
			diskIndex += GameDirection::LEFT;
			diskIndexToChange = -2;
		}

		else if (diskIndexToChange == -2 && gameBoard[diskIndex] == disk)
			return diskIndex - GameDirection::LEFT;

		// else if (diskIndexToChange == -1 || gameBoard[diskIndex] == '-')
		else return -1;
	}
	return -1;
}

// Checks right.
int checkFlipRight(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	if (gameBoardIndex % 8 == 7)
		return -1;

	int diskIndex = gameBoardIndex + GameDirection::RIGHT, diskIndexToChange = -1;
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();
	const std::string& gameBoard = player.getGameState();

	while (1)
	{
		if (diskIndex % 8 != 7 && gameBoard[diskIndex] == opponentDisk)
		{
			diskIndex += GameDirection::RIGHT;
			diskIndexToChange = -2;
		}

		else if (diskIndexToChange == -2 && gameBoard[diskIndex] == disk)
			return diskIndex - GameDirection::RIGHT;

		// else if (diskIndexToChange == -1 || gameBoard[diskIndex] == '-')
		else return -1;
	}
	return -1;
}

// Checks diagonal up left.
int checkFlipDiagonalUpLeft(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	if (gameBoardIndex < 8 || gameBoardIndex % 8 == 0)
		return -1;

	int diskIndex = gameBoardIndex + GameDirection::DIAGONAL_UP_LEFT, diskIndexToChange = -1;
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();
	const std::string& gameBoard = player.getGameState();

	while (1)
	{
		if (diskIndex > 7 && diskIndex % 8 != 0 && gameBoard[diskIndex] == opponentDisk)
		{
			diskIndex += GameDirection::DIAGONAL_UP_LEFT;
			diskIndexToChange = -2;
		}

		else if (diskIndexToChange == -2 && gameBoard[diskIndex] == disk)
			return diskIndex - GameDirection::DIAGONAL_UP_LEFT;

		// else if (diskIndexToChange == -1 || gameBoard[diskIndex] == '-')
		else return -1;
	}
	return -1;
}

// Checks diagonal up right.
int checkFlipDiagonalUpRight(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	if (gameBoardIndex < 8 || gameBoardIndex % 8 == 7)
		return -1;

	int diskIndex = gameBoardIndex + GameDirection::DIAGONAL_UP_RIGHT, diskIndexToChange = -1;
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();
	const std::string& gameBoard = player.getGameState();

	while (1)
	{
		if (diskIndex > 7 && diskIndex % 8 != 7 && gameBoard[diskIndex] == opponentDisk)
		{
			diskIndex += GameDirection::DIAGONAL_UP_RIGHT;
			diskIndexToChange = -2;
		}

		else if (diskIndexToChange == -2 && gameBoard[diskIndex] == disk)
			return diskIndex - GameDirection::DIAGONAL_UP_RIGHT;

		// else if (diskIndexToChange == -1 || gameBoard[diskIndex] == '-')
		else return -1;
	}
	return -1;
}

// Checks diagonal down left.
int checkFlipDiagonalDownLeft(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	if (gameBoardIndex > 55 || gameBoardIndex % 8 == 0)
		return -1;

	int diskIndex = gameBoardIndex + GameDirection::DIAGONAL_DOWN_LEFT, diskIndexToChange = -1;
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();
	const std::string& gameBoard = player.getGameState();

	while (1)
	{
		if (diskIndex < 56 && diskIndex % 8 != 0 && gameBoard[diskIndex] == opponentDisk)
		{
			diskIndex += GameDirection::DIAGONAL_DOWN_LEFT;
			diskIndexToChange = -2;
		}

		else if (diskIndexToChange == -2 && gameBoard[diskIndex] == disk)
			return diskIndex - GameDirection::DIAGONAL_DOWN_LEFT;

		// else if (diskIndexToChange == -1 || gameBoard[diskIndex] == '-')
		else return -1;
	}
	return -1;
}

// Checks diagonal down right.
int checkFlipDiagonalDownRight(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	if (gameBoardIndex > 55 || gameBoardIndex % 8 == 7)
		return -1;

	int diskIndex = gameBoardIndex + GameDirection::DIAGONAL_DOWN_RIGHT, diskIndexToChange = -1;
	const char& disk = player.getDisk(), opponentDisk = opponent.getDisk();
	const std::string& gameBoard = player.getGameState();

	while (1)
	{
		if (diskIndex < 56 && diskIndex % 8 != 7 && gameBoard[diskIndex] == opponentDisk)
		{
			diskIndex += GameDirection::DIAGONAL_DOWN_RIGHT;
			diskIndexToChange = -2;
		}

		else if (diskIndexToChange == -2 && gameBoard[diskIndex] == disk)
			return diskIndex - GameDirection::DIAGONAL_DOWN_RIGHT;

		// else if (diskIndexToChange == -1 || gameBoard[diskIndex] == '-')
		else return -1;
	}
	return -1;
}

// Flips all disks based on game's rules.
void flipAllDisks(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	int diskIndexToChange = checkFlipDown(player, opponent, gameBoardIndex);
	if (diskIndexToChange > 0)
		flipDiskOnGivenDirection(player, opponent, diskIndexToChange, GameDirection::UP);

	diskIndexToChange = checkFlipUp(player, opponent, gameBoardIndex);
	if (diskIndexToChange > 0)
		flipDiskOnGivenDirection(player, opponent, diskIndexToChange, GameDirection::DOWN);

	diskIndexToChange = checkFlipLeft(player, opponent, gameBoardIndex);
	if (diskIndexToChange > 0)
		flipDiskOnGivenDirection(player, opponent, diskIndexToChange, GameDirection::RIGHT);

	diskIndexToChange = checkFlipRight(player, opponent, gameBoardIndex);
	if (diskIndexToChange > 0)
		flipDiskOnGivenDirection(player, opponent, diskIndexToChange, GameDirection::LEFT);

	diskIndexToChange = checkFlipDiagonalUpLeft(player, opponent, gameBoardIndex);
	if (diskIndexToChange > 0)
		flipDiskOnGivenDirection(player, opponent, diskIndexToChange, GameDirection::DIAGONAL_DOWN_RIGHT);

	diskIndexToChange = checkFlipDiagonalUpRight(player, opponent, gameBoardIndex);
	if (diskIndexToChange > 0)
		flipDiskOnGivenDirection(player, opponent, diskIndexToChange, GameDirection::DIAGONAL_DOWN_LEFT);

	diskIndexToChange = checkFlipDiagonalDownLeft(player, opponent, gameBoardIndex);
	if (diskIndexToChange > 0)
		flipDiskOnGivenDirection(player, opponent, diskIndexToChange, GameDirection::DIAGONAL_UP_RIGHT);

	diskIndexToChange = checkFlipDiagonalDownRight(player, opponent, gameBoardIndex);
	if (diskIndexToChange > 0)
		flipDiskOnGivenDirection(player, opponent, diskIndexToChange, GameDirection::DIAGONAL_UP_LEFT);
}

// Places disk on Othello board based on given command.
void placeDisk(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex)
{
	player.setGameState(gameBoardIndex, player.getDisk());
	flipAllDisks(player, opponent, gameBoardIndex);
	opponent.setGameState(player.getGameState());
	player.incrementScore();
}


// Writes current game state to output stream on a console.
void printGameState(const std::string& gameState)
{
	std::cout << "  a b c d e f g h";
	for (size_t i = 0, row = 0; i < 64; ++i)
	{
		if (i % 8 == 0)	std::cout << '\n' << ++row << ' ';
		std::cout << gameState[i] << ' ';
	}
	std::cout << '\n';
}

// Checks if given vector has already element with value of given integer.
int isIntInVector(const std::vector<int>& v, const int& iValue)
{
	return std::find(v.begin(), v.end(), iValue) != v.end();
}