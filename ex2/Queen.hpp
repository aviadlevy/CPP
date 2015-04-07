/**
* file that contain the declaring for class of Queen piece, and its function
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Piece.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"

#ifndef QUEEN_HPP
#define QUEEN_HPP

/**
* class of Queen. the queen also inherit the bishop and the rook because the queen can move like
* both of them, and we want to prevent double code.
*/
class Queen : public virtual Piece, Rook, Bishop
{
	std::string _unicode = "\u265B";
	char _sign = 'q';

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
	virtual int _isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
											 int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
											 bool moveOrCheck);

public:

	/**
	* constructor for Queen
	*
	* @param player the color for the player
	*/
	Queen(char player) : Piece(player)
	{
	}

	/**
	* destructor for Queen
	*/
	~Queen()
	{
	}

	/**
	* virtual function that get sign for Queen
	*
	* @return one letter of Queen ('q')
	*/
	virtual char getSign() const;

	/**
	* virtual function that get unicode symbol for Queen
	*
	* @return string of unicode for Queen ("\u265B")
	*/
	virtual std::string getUnicodeSymbol() const;

	/**
	* function to use in case of deep copy
	*
	* @return pointer for new Queen class
	*/
	virtual Piece* clone() const;
};

#endif