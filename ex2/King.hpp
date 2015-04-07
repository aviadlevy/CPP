/**
* file that contain the declaring for class of King piece, and its function
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Piece.hpp"

#ifndef KING_HPP
#define KING_HPP

/**
* class for King
*/
class King : public Piece
{
	std::string _unicode = "\u265A";
	char _sign = 'k';

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
	virtual int _isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
											 int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
											 bool moveOrCheck);

public:

	/**
	* constructor for King
	*
	* @param player the color for the player
	*/
	King(char player) : Piece(player)
	{
	}

	/**
	* destructor for King
	*/
	~King()
	{
	}

	/**
	* virtual function that get unicode symbol for King
	*
	* @return string of unicode for King ("\u265A")
	*/
	virtual std::string getUnicodeSymbol() const;

	/**
	* virtual function that get sign for King
	*
	* @return one letter of King ('k')
	*/
	virtual char getSign() const;

	/**
	* function to use in case of deep copy
	*
	* @return pointer for new King class
	*/
	virtual Piece* clone() const;
};

#endif