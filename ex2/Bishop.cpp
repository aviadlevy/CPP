/**
* file that contain the functions declared in class for Bishop piece
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include <stdlib.h>
#include "Bishop.hpp"


/**
* virtual function that get sign for Bishop
*
* @return one letter of Bishop ('b')
*/
char Bishop::getSign() const
{
	return _sign;
}

/**
* function that check if move is legal for bishop. (also the Queen will use this function.
* that's why this is protected. see more on Queen.hpp)
*
* @param positionRow the row the bishop in
* @param positionCol the column the bishop in
* @param targetRow the row the bishop want to go to
* @param targetCol the column the bishop want to go to
* @param _board the game _board with all pieces
* @param moveOrCheck true if we want to move the bishop. false if we just want to check.
* @return 1 if legal. 0 otherwise.
*/
int Bishop::_isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
										 int targetCol, Piece *board[8][8], bool moveOrCheck)
{
	//pass the unused warning. we dont need this vars in this specific subClass
	(void) moveOrCheck;

	int deltaCol = abs(positionCol - targetCol), deltaRow = abs(positionRow - targetRow);
	//check if we go diagonally
	if (deltaCol != deltaRow)
	{
		return 0;
	}

	//for the loop later. 1 symbolize right, -1 left
	int rightOrLeft = (targetCol - positionCol > 0) ? 1 : -1;
	//for the loop later. 1 symbolize up, -1 down
	int upOrDown = (targetRow - positionRow > 0) ? 1 : -1;

	// i for rows, j for cols
	for (int i = positionRow + upOrDown, j = positionCol + rightOrLeft; i != targetRow;
		 i += upOrDown, j += rightOrLeft)
	{
		//cell is occupied
		if (board[i][j])
		{
			return 0;
		}
	}
	return 1;
}

/**
* virtual function that get unicode symbol for Bishop
*
* @return string of unicode for Bishop ("\u265D")
*/
std::string Bishop::getUnicodeSymbol() const
{
	return _unicode;
}

/**
* function to use in case of deep copy
*
* @return pointer for new Bishop class
*/
Piece *Bishop::clone() const
{
	return new Bishop(*this);
}
