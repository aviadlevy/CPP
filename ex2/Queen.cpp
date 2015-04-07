/**
* file that contain the functions declared in class for Queen piece
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Queen.hpp"


/**
* virtual function that get sign for Queen
*
* @return one letter of Queen ('q')
*/
char Queen::getSign() const
{
	return _sign;
}

/**
* function that check if move is legal for Queen.
*
* @param positionRow the row the Queen in
* @param positionCol the column the Queen in
* @param targetRow the row the Queen want to go to
* @param targetCol the column the Queen want to go to
* @param _board the game _board with all pieces
* @param moveOrCheck true if we want to move the Queen. false if we just want to check.
* @return 1 if legal. 0 otherwise.
*/
int Queen::_isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
										int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
										bool moveOrCheck)
{
	//check if we can move diagonally or straight, like the bishop or the rook
	if (Bishop::_isMoveLegalForSpecificPiece(positionRow, positionCol, targetRow, targetCol, board,
		moveOrCheck) ||
		Rook::_isMoveLegalForSpecificPiece(positionRow, positionCol, targetRow, targetCol, board,
		moveOrCheck))
	{
		return 1;
	}
	return 0;
}

/**
* virtual function that get unicode symbol for Queen
*
* @return string of unicode for Queen ("\u265B")
*/
std::string Queen::getUnicodeSymbol() const
{
	return _unicode;
}

/**
* function to use in case of deep copy
*
* @return pointer for new Queen class
*/
Piece *Queen::clone() const
{
	return new Queen(*this);
}
