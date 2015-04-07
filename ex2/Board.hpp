/**
* file that contain the declaring for class of Board - the class that hold all function relevant
* for the board game
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Piece.hpp"

#ifndef BOARD_HPP
#define BOARD_HPP

/**
* class for _board game.
*/
class Board
{
public:
	Piece *_board[NUM_OF_ROWS][NUM_OF_ROWS];

	/**
	* default constructor for _board. reset _board to start point
	*/
	Board();

	/**
	* copy constructor
	*
	* @param boardToCopy type Board to copy to new Board
	*/
	Board(const Board &boardToCopy);

	/**
	* deep copy _board
	*
	* @param boardToCopy the 2d array of pieces for specific _board
	*/
	Board(Piece *boardToCopy[NUM_OF_ROWS][NUM_OF_ROWS]);

	/**
	* destructor for Board
	*/
	~Board();

	/**
	* print the _board
	*/
	void print();

	/**
	* check if player is in check
	*
	* @param playerColor the player we want to check if in check
	* @return 1 if in check. 0 otherwise
	*/
	int isInCheck(char playerColor);

	/**
	* check if player can move, without causing check.
	*
	* @param player the player we want to check if can move
	* @return 1 if can move. 0 otherwise.
	*/
	int canMove(char player);
};

/**
* print row of letters between 'A' to 'H'
*/
void printRowLetters();

#endif