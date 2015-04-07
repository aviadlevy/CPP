/**
* file that contain the functions declared in class for Rook piece
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Rook.hpp"

/**
* virtual function that get sign for Rook
*
* @return one letter of Rook ('r')
*/
char Rook::getSign() const
{
	return _sign;
}

/**
* function that check if move is legal for Rook. we'll also use this on Queen.cpp
*
* @param positionRow the row the Rook in
* @param positionCol the column the Rook in
* @param targetRow the row the Rook want to go to
* @param targetCol the column the Rook want to go to
* @param _board the game _board with all pieces
* @param moveOrCheck true if we want to move the Rook. false if we just want to check.
* @return 1 if legal. 0 otherwise.
*/
int Rook::_isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
									   int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
									   bool moveOrCheck)
{
	//pass the unused warning. we dont need this vars in this specific subClass
	(void) moveOrCheck;

	//if we want to move left or right.
	if (positionRow == targetRow)
	{
		int rightOrLeft = (targetCol - positionCol > 0) ? 1 : -1;
		for (int i = positionCol + rightOrLeft; i != targetCol; i += rightOrLeft)
		{
			if (board[positionRow][i] != 0)
			{
				return 0;
			}
		}
		return 1;
	}

	//if we want to move up or down.
	else if (positionCol == targetCol)
	{
		int upOrDown = (targetRow - positionRow > 0) ? 1 : -1;
		for (int i = positionRow + upOrDown; i != targetRow; i += upOrDown)
		{
			if (board[i][positionCol] != 0)
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}


/**
* virtual function that get unicode symbol for Rook
*
* @return string of unicode for Rook ("\u265C")
*/
std::string Rook::getUnicodeSymbol() const
{
	return _unicode;
}

/**
* function to use in case of deep copy
*
* @return pointer for new Rook class
*/
Piece *Rook::clone() const
{
	return new Rook(*this);
}
