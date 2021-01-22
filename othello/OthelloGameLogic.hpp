/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloGameLogic.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include <string>
#include "OthelloBot.hpp"

/**
* Constant represents columns in visualization
*/
static const std::string COLUMN = "ABCDEFGH";

/**
* Constant represents rows in visualization
*/
static const std::string ROW = "12345678";

/**
* Checks possible move on Othello board by going up.
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
* Checks possible move on Othello board by going diagonal up and left.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return integer value -1 for not possible move or free index on gameBoard
*/
int checkDiagonalUpLeft(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);

/**
* Checks possible move on Othello board by going diagonal up and right.
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
* @param othelloBot object of class OthelloBot
* @param color integer to specify color of a disk
* @return vector of valid indexes representing valid moves on Othello board
*/
std::vector<int> getValidMoves(OthelloBot& othelloBot, const int& color);

/**
* Moves disk on Othello board based on given command.
* @param othelloBot object of class OthelloBot
* @param gameBoardIndex to move disk
* @param color integer to specify color of a disk
* @return
*/
void moveDisk(OthelloBot& othelloBot, const int& gameBoardIndex, const int& color);

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