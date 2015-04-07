/**
* file that contain the functions declared in class for Knight piece
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include <stdlib.h>
#include "Knight.hpp"

/**
* virtual function that get sign for Knight
*
* @return one letter of Knight ('n')
*/
char Knight::getSign() const
{
	return _sign;
}

/**
* function that check if move is legal for Knight.
*
* @param positionRow the row the Knight in
* @param positionCol the column the Knight in
* @param targetRow the row the Knight want to go to
* @param targetCol the column the Knight want to go to
* @param _board the game _board with all pieces
* @param moveOrCheck true if we want to move the Knight. false if we just want to check.
* @return 1 if legal. 0 otherwise.
*/
int Knight::_isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
										 int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
										 bool moveOrCheck)
{
	//pass the unused warning. we dont need this vars in this specific subClass
	(void) board, (void) moveOrCheck;

	int deltaCol = abs(positionCol - targetCol), deltaRow = abs(positionRow - targetRow);
	if (deltaCol == 1 && deltaRow == 2)
	{
		return 1;
	}
	if (deltaCol == 2 && deltaRow == 1)
	{
		return 1;
	}
	return 0;
}

/**
* virtual function that get unicode symbol for Knight
*
* @return string of unicode for Knight ("\u265E")
*/
std::string Knight::getUnicodeSymbol() const
{
	return _unicode;
}

/**
* function to use in case of deep copy
*
* @return pointer for new Knight class
*/
Piece *Knight::clone() const
{
	return new Knight(*this);
}
