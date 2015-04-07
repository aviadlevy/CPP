/**
* file that contain the declaring for class of Rook piece, and its function
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Piece.hpp"

#ifndef ROOK_HPP
#define ROOK_HPP

/**
* class for Rook
*/
class Rook : public virtual Piece
{
private:
	std::string _unicode = "\u265C";
	char _sign = 'r';

protected:

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
	virtual int _isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
											 int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
											 bool moveOrCheck);
public:

	/**
	* default constructor for Rook
	*/
	Rook()
	{
	}

	/**
	* constructor for Rook
	*
	* @param player the color for the player
	*/
	Rook(char player) : Piece(player)
	{
	}

	/**
	* destructor for Rook
	*/
	~Rook()
	{
	}

	/**
	* virtual function that get unicode symbol for Rook
	*
	* @return string of unicode for Rook ("\u265C")
	*/
	virtual std::string getUnicodeSymbol() const;

	/**
	* virtual function that get sign for Rook
	*
	* @return one letter of Rook ('r')
	*/
	char getSign() const;

	/**
	* function to use in case of deep copy
	*
	* @return pointer for new Rook class
	*/
	virtual Piece* clone() const;
};

#endif