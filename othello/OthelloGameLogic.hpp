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

static const std::string column = "ABCDEFGH"; 
static const std::string row = "12345678";

void moveDisk(OthelloBot& othelloBot, const std::string& command);