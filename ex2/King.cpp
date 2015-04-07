/**
* file that contain the functions declared in class for King piece
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include <stdlib.h>
#include "King.hpp"
#include "Board.hpp"

#define ROOK_SIGN 'r'

/**
* virtual function that get sign for King
*
* @return one letter of King ('k')
*/
char King::getSign() const
{
	return _sign;
}

/**
* function that check if move is legal for King.
*
* @param positionRow the row the King in
* @param positionCol the column the King in
* @param targetRow the row the King want to go to
* @param targetCol the column the King want to go to
* @param _board the game _board with all pieces
* @param moveOrCheck true if we want to move the King. false if we just want to check.
* @return 1 if legal. 0 otherwise.
*/
int King::_isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
									   int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
									   bool moveOrCheck)
{
	int deltaCol = abs(positionCol - targetCol), deltaRow = abs(positionRow - targetRow);
	if (deltaCol <= 1 && deltaRow <= 1)
	{
		return 1;
	}

	Board *tempBoard = new Board(board);
	bool isDelete = false;

	//check for castling. first check if in check
	if(!tempBoard->isInCheck(board[positionRow][positionCol]->getPlayer()))
	{
		delete tempBoard;
		isDelete = true;
		//then check that the king not moved
		if (positionCol == 4 && (positionRow == 0 || positionRow == 7))
		{
			//castling to the right
			if (targetCol == 6)
			{
				//check if rook not moved and if the space between them is empty
				if (board[positionRow][7] && board[positionRow][7]->getSign() == ROOK_SIGN &&
					!board[positionRow][5] && !board[positionRow][6])
				{
					//if we just checking, skip if not, move the rook
					if (moveOrCheck)
					{
						board[positionRow][5] = board[positionRow][7];
						board[positionRow][7] = 0;
						return 1;
					}
				}
			}

			//castling to the left
			else if (targetCol == 2)
			{
				//check if rook not moved and if the space between them is empty
				if (board[positionRow][0] && board[positionRow][0]->getSign() == ROOK_SIGN &&
					!board[positionRow][1] && !board[positionRow][2] && !board[positionRow][3])
				{
					//if we just checking, skip if not, move the rook
					if (moveOrCheck)
					{
						board[positionRow][3] = board[positionRow][0];
						board[positionRow][0] = 0;
						return 1;
					}
				}
			}
		}
	}
	if(!isDelete)
	{
		delete tempBoard;
	}
	return 0;
}



/**
* virtual function that get unicode symbol for King
*
* @return string of unicode for King ("\u265A")
*/
std::string King::getUnicodeSymbol() const
{
	return _unicode;
}

/**
* function to use in case of deep copy
*
* @return pointer for new King class
*/
Piece *King::clone() const
{
	return new King(*this);
}
