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

static const std::string COLUMN = "ABCDEFGH"; 
static const std::string ROW = "12345678";

std::vector<int> checkUp(const std::string& gameBoard, const size_t& diskIndex, const int& color);
std::vector<int> checkDown(const std::string& gameBoard, const size_t& diskIndex, const int& color);
std::vector<int> checkLeft(const std::string& gameBoard, const size_t& diskIndex, const int& color);
std::vector<int> checkRight(const std::string& gameBoard, const size_t& diskIndex, const int& color);

std::vector<int> checkVertical(const std::string& gameBoard, const size_t& diskIndex, const int& color);
std::vector<int> checkHorizontal(const std::string& gameBoard, const size_t& diskIndex, const int& color);
std::vector<int> checkDiagonal(const std::string& gameBoard, const size_t& diskIndex, const int& color);

void movePossibilities(OthelloBot& othelloBot);
void moveDisk(OthelloBot& othelloBot, const std::string& command);