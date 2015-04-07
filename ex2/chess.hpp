/**
* file that contain the declaring for  all function relevant for managing the game
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Board.hpp"

#ifndef CHESS_HPP
#define CHESS_HPP


#define GET_NAMES 0
#define USER_TURN 1
#define INVALID 3
#define CHECKMATE 4
#define TIE 5
#define CHECK 6

/**
* function that manage the game.
*
* @param boardGame initialize _board to play
*/
void playGame(Board *boardGame);

/**
* some printing with information to users
*
* @param typeOfPrinting the type of massage we want to print
* @param str some additional string added to massage
*/
void printToUser(int typeOfPrinting, std::string const str);

/**
* manage each turn for specific player
*
* @param _board the _board game
* @param whitePlayer white player name
* @param blackPlayer black player name
*/
void getNextMove(Board *board, std::string whitePlayer, std::string blackPlayer);

/**
* check if the moving string the user entered is legal
*
* @param move the move string
* @param positionRow update inside the function to converted value (between 0 to 7)
* @param positionCol update inside the function to converted value (between 0 to 7)
* @param targetRow update inside the function to converted value (between 0 to 7)
* @param targetCol update inside the function to converted value (between 0 to 7)
* @return 1 if the string is legal, 0 otherwise
*/
int checkMoveString(std::string move, int *positionRow, int *positionCol, int *targetRow,
					int *targetCol);

/**
* check if number is in range of zero to 7
*
* @param num the number to check
* @return 1 if in range, 0 otherwise
*/
int checkIfInRange(int num);

/**
* check if game is over. if yes check if it's checkmate or stalemate
*
* @param _board game _board
* @param whitePlayer white player name
* @param blackPlayer black player name
* @return 1 if over, 0 otherwise
*/
int isOver(Board *board, std::string whitePlayer, std::string blackPlayer);

#endif