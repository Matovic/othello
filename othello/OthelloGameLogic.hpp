/**
* Course: Application programming in C++ 2020/2021
* Purpose: Othello game logic with move operations.
*
* @file OthelloGameLogic.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include <string>
#include "OthelloGame.hpp"

/**
* Struct GameDirection representing all posible direction for one disk.
*/
struct GameDirection
{
	static const int
		UP = -8,
		DOWN = 8,
		LEFT = -1,
		RIGHT = 1,
		DIAGONAL_UP_LEFT = -9,
		DIAGONAL_UP_RIGHT = -7,
		DIAGONAL_DOWN_LEFT = 7,
		DIAGONAL_DOWN_RIGHT = 9;
};

/**
* Constant represents columns in visualization
*/
static const std::string COLUMN = "ABCDEFGH";

/**
* Constant represents rows in visualization
*/
static const std::string ROW = "12345678";

/**
* Checks possible move on Othello board by going UP.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color 
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkUp(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);

/**
* Checks possible move on Othello board by going down.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkDown(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);


/**
* Checks possible move on Othello board by going left.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);


/**
* Checks possible move on Othello board by going right.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);

/**
* Checks possible move on Othello board by going diagonal UP and left.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkDiagonalUpLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);

/**
* Checks possible move on Othello board by going diagonal UP and right.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkDiagonalUpRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);


/**
* Checks possible move on Othello board by going diagonal down and left.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkDiagonalDownLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);


/**
* Checks possible move on Othello board by going diagonal down and right.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkDiagonalDownRight(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);

/**
* Checks all directions for possible moves on Othello board.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return vector of integers with all possible indexes on gameBoard
*/
std::vector<int> checkDirections(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);

/**
* Gets all possible moves on Othello board.
* @param othelloGame object of class OthelloGame
* @param disk char to specify color of a disk
* @return vector of valid indexes representing valid moves on Othello board
*/
std::vector<int> getValidMoves(const std::string& board, const char& disk, const char& opponentDisk, const bool& isBot);

/**
* Places disk on Othello board based on given command.
* @param othelloGame object of class OthelloGame
* @param OthelloGame& opponent
* @param gameBoardIndex to move disk
* @return
*/
void placeDisk(OthelloGame& othelloGame, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Writes current game state to output stream on a console.
* @param gameState represents current Othello board with O for being white disk and X being black disk
*/
void printGameState(const std::string& gameState);

/**
* Checks if given vector has already element with value of given integer.
* @param v vector of integers
* @param iValue integer value
* @return 0, if vector has no such element, or 1, if vector already has element with given value
*/
int isIntInVector(const std::vector<int>& v, const int& iValue);

/**
* Shows possible moves to the player on game board.
* @param possibleGameState to be shown
* @param vectorValidMoves with possible user's moves
*/
void showPossibleMoves(std::string& possibleGameState, const std::vector<int>& vectorValidMoves);

/**
* Flips all disks based on game's rules.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
*/
void flipAllDisks(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Checks diagonal down right.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @return index of game state to be changed or -1 if there is no one
*/
int checkFlipDiagonalDownRight(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Checks diagonal down left.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @return index of game state to be changed or -1 if there is no one
*/
int checkFlipDiagonalDownLeft(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Checks diagonal up right.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @return index of game state to be changed or -1 if there is no one
*/
int checkFlipDiagonalUpRight(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Checks diagonal up left.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @return index of game state to be changed or -1 if there is no one
*/
int checkFlipDiagonalUpLeft(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Checks right.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @return index of game state to be changed or -1 if there is no one
*/
int checkFlipRight(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Checks left.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @return index of game state to be changed or -1 if there is no one
*/
int checkFlipLeft(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Checks up.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @return index of game state to be changed or -1 if there is no one
*/
int checkFlipUp(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Checks down.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @return index of game state to be changed or -1 if there is no one
*/
int checkFlipDown(OthelloGame& player, OthelloGame& opponent, const int& gameBoardIndex);

/**
* Flips all disks on given direction.
* @param player class
* @param opponent class
* @param gameBoardIndex to be examined
* @param direction is integer number for specifing direction
*/
void flipDiskOnGivenDirection(OthelloGame& player, OthelloGame& opponent, int& diskIndexToChange, const int direction);