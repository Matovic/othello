/**
* Course: Application programming in C++ 2020/2021
* Purpose: Bot for the game Othello, with console visualization.
*
* @file OthelloGame.hpp
* @author Erik Matovic
* @version 31/01/2021
*/

#pragma once

#include <string>

/**
* Makes all characters uppercase in given string.
* @param str string to make all characters uppercase.
*/
void toUpper(std::string& str);

/**
* Checks if string is an integer number.
* @param str string to check.
* @return true if str is int or false if str is not int
*/
bool isStringInt(const std::string& str);

/**
* Get parameters from command line arguments.
* @param argument count
* @param argument vector
* @return tuple of color, max depth, heuristic function, time
*/
std::tuple<int, int, int, int> getParameters(const int& argc, char* argv[]);

/**
* Processes command line arguments into a tuple of color, max depth, heuristic function and time.
* @param argument count
* @param argument vector
* @return tuple of color, max depth, heuristic function, time
*/
std::tuple<int, int, int, int> processArguments(const int& argc, char* argv[]);

/**
* Checks if given command line arguments are fit to be parameters for Othello game.
* @param color 
* @param maxDepth
* @param heuristic function
* @param moveTime
* @return 0 if arguments are fine or 1 if arguments are not fit for Othello game
*/
int checkParameters(const int& color, const int& maxDepth, const int& heuristic, const int& moveTime);

/**
* Reads user's commands
* @param argument count
* @param argument vector
* @return 0 if arguments are fine or 1 if arguments are not fit for Othello game
*/
void readCommand(int argc, char* argv[]);

/**
* Gets index from valid user's command
* @param command is valid user's command 
* @return index to be used on Othello game board
*/
int getIndexFromCommand(const std::string& command);