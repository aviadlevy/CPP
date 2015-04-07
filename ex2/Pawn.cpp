/**
* file that contain the functions declared in class for Pawn piece
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include <stdlib.h>
#include "Pawn.hpp"
#include "Queen.hpp"


/**
* virtual function that get sign for Pawn
*
* @return one letter of Pawn ('p')
*/
char Pawn::getSign() const
{
	return _sign;
}

/**
* function that check if move is legal for Pawn.
*
* @param positionRow the row the Pawn in
* @param positionCol the column the Pawn in
* @param targetRow the row the Pawn want to go to
* @param targetCol the column the Pawn want to go to
* @param _board the game _board with all pieces
* @param moveOrCheck true if we want to move the Pawn. false if we just want to check.
* @return 1 if legal. 0 otherwise.
*/
int Pawn::_isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
									   int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
									   bool moveOrCheck)
{
	//if the target cell is empty, we allowing the pawn to move only forward
	if (!board[targetRow][targetCol])
	{
		if (positionCol == targetCol)
		{
			switch (getPlayer())
			{
				case WHITE:
				{
					//check if not moved yet and if so we allow the pawn to move 2 steps, or if
					// we want to move only 1 step
					if ((positionRow == 1 && (targetRow - positionRow == 2) &&
						!board[2][positionCol]) || ((targetRow - positionRow) == 1))
					{
						if(positionRow == 6)
						{
							if(moveOrCheck)
							{
								delete board[positionRow][positionCol];
								board[positionRow][positionCol] = new Queen(WHITE);
							}
						}
						return 1;
					}
					break;
				}
				case BLACK:
				{
					//check if not moved yet and if so we allow the pawn to move 2 steps, or if
					// we want to move only 1 step
					if ((positionRow == 6 && (positionRow - targetRow == 2) &&
						!board[5][positionCol]) || ((positionRow - targetRow) == 1))
					{
						if(positionRow == 1)
						{
							if(moveOrCheck)
							{
								delete board[positionRow][positionCol];
								board[positionRow][positionCol] = new Queen(BLACK);
							}
						}
						return 1;
					}
					break;
				}
			}
		}
	}
	//the target cell isn't empty, so we allow the pawn to move one step diagonally
	else
	{
		if (abs(positionCol - targetCol) == 1)
		{
			switch (getPlayer())
			{
				case WHITE:
				{
					if (positionRow == targetRow - 1)
					{
						if(positionRow == 6)
						{
							if(moveOrCheck)
							{
								delete board[positionRow][positionCol];
								board[positionRow][positionCol] = new Queen(WHITE);
							}
						}
						return 1;
					}
				}
				case BLACK:
				{
					if (positionRow == targetRow + 1)
					{
						if(positionRow == 1)
						{
							if(moveOrCheck)
							{
								delete board[positionRow][positionCol];
								board[positionRow][positionCol] = new Queen(BLACK);
							}
						}
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

/**
* virtual function that get unicode symbol for Pawn
*
* @return string of unicode for Pawn ("\u265F")
*/
std::string Pawn::getUnicodeSymbol() const
{
	return std::string(_unicode);
}

/**
* function to use in case of deep copy
*
* @return pointer for new Pawn class
*/
Piece *Pawn::clone() const
{
	return new Pawn(*this);
}
