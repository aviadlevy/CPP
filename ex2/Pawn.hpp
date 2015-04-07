/**
* file that contain the declaring for class of Pawn piece, and its function
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Piece.hpp"

#ifndef PAWN_HPP
#define PAWN_HPP

/**
* class for Pawn
*/
class Pawn : public Piece
{
	std::string _unicode = "\u265F";
	char _sign = 'p';

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
	virtual int _isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
											 int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
											 bool moveOrCheck);

public:

	/**
	* constructor for Pawn
	*
	* @param player the color for the player
	*/
	Pawn(char player) : Piece(player)
	{
	}

	/**
	* destructor for Pawn
	*/
	~Pawn()
	{
	}

	/**
	* virtual function that get sign for Pawn
	*
	* @return one letter of Pawn ('p')
	*/
	char getSign() const;

	/**
	* virtual function that get unicode symbol for Pawn
	*
	* @return string of unicode for Pawn ("\u265F")
	*/
	virtual std::string getUnicodeSymbol() const;

	/**
	* function to use in case of deep copy
	*
	* @return pointer for new Pawn class
	*/
	virtual Piece* clone() const;
};

#endif