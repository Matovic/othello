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
* Checks all vertical moves on Othello board.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return vector of integers with all possible indexes on gameBoard
*/
//std::vector<int> checkVertical(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);

/**
* Checks all horizontal moves on Othello board.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return vector of integers with all possible indexes on gameBoard
*/
//std::vector<int> checkHorizontal(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);

/**
* Checks all diagonal moves on Othello board.
* @param gameBoard represents board with O for being white disk and X being black disk
* @param diskIndex represents index on game board to be checked
* @param opponentDisk represents current disk color
* @return vector of integers with all possible indexes on gameBoard
*/
//std::vector<int> checkDiagonal(const std::string& gameBoard, const size_t& diskIndex, const char& opponentDisk);


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
* @return vector of valid indexes representing valid moves on Othello board
*/
std::vector<int> getValidMoves(OthelloBot& othelloBot);

/**
* Moves disk on Othello board based on given command.
* @param othelloBot object of class OthelloBot
* @param command to move disk
* @return
*/
void moveDisk(OthelloBot& othelloBot, const std::string& command);

/**
* Writes current game state to output stream on a console.
* @param gameState represents current Othello board with O for being white disk and X being black disk
*/
void printGameState(const std::string& gameState);