/**
* file that contain the declaring for class of Bishop piece, and its function
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Piece.hpp"

#ifndef BISHOP_HPP
#define BISHOP_HPP

/**
* class for Bishop
*/
class Bishop : public virtual Piece
{
	std::string _unicode = "\u265D";
	char _sign = 'b';

protected:

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
	virtual int _isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
											 int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
											 bool moveOrCheck);

public:

	/**
	* default constructor for Bishop
	*/
	Bishop()
	{
	}

	/**
	* constructor for Bishop
	*
	* @param player the color for the player
	*/
	Bishop(char player) : Piece(player)
	{
	}

	/**
	* destructor for Bishop
	*/
	~Bishop()
	{
	}

	/**
	* virtual function that get sign for Bishop
	*
	* @return one letter of Bishop ('b')
	*/
	virtual char getSign() const;

	/**
	* virtual function that get unicode symbol for Bishop
	*
	* @return string of unicode for Bishop ("\u265D")
	*/
	virtual std::string getUnicodeSymbol() const;

	/**
	* function to use in case of deep copy
	*
	* @return pointer for new Bishop class
	*/
	virtual Piece* clone() const;
};

#endif