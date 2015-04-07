/**
* file that contain the function declared in class for Piece - the base class for all pieces
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Piece.hpp"

/**
* constructor for Piece
*
* @param player the color for the player
*/
Piece::Piece(char player)
{
	_player = player;
}

/**
* getter for color of player (_player)
*
* @return the color of player
*/
char Piece::getPlayer()
{
	return _player;
}

/**
* common checking for all pieces. if pass checking will call _isMoveLegalForSpecificPiece.
*
* @param positionRow the row the piece in
* @param positionCol the column the piece in
* @param targetRow the row the piece want to go to
* @param targetCol the column the piece want to go to
* @param _board the game _board with all pieces
* @param moveOrCheck true if we want to move the piece. false if we just want to check. (we
* 		 want this specifically for case of castling in King.cpp)
* @return 1 if legal. 0 otherwise.
*/
int Piece::isMoveLegal(int positionRow, int positionCol, int targetRow, int targetCol,
					   Piece *board[NUM_OF_ROWS][NUM_OF_ROWS], bool moveOrCheck)
{
	//check if the target cell is unoccupied or if occupied if is opponent player
	if (!board[targetRow][targetCol] || (_player != board[targetRow][targetCol]->getPlayer()))
	{
		return _isMoveLegalForSpecificPiece(positionRow, positionCol, targetRow, targetCol, board,
											moveOrCheck);
	}
	return 0;
}


