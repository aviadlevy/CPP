/**
* file that contain the declaring for class of Piece - the base class for all pieces, and its
* function (some pure virtual)
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include <iostream>

#ifndef PIECE_HPP
#define PIECE_HPP

#define NUM_OF_ROWS 8

#define BLACK 'b'
#define WHITE 'w'

/**
* class for piece. the parent for all type of pieces.
*/
class Piece
{
	char _player;

	/**
	* pure virtual function that check if move is legal for the subclasses of piece.
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
	virtual int _isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
											 int targetCol, Piece *board[8][8], bool moveOrCheck)
											= 0;

public:
	/**
	* default constructor for Piece
	*/
	Piece()
	{
	}

	/**
	* constructor for Piece
	*
	* @param player the color for the player
	*/
	Piece(char player);

	/**
	* destructor for Piece
	*/
	virtual ~Piece()
	{
	}

	/**
	* getter for color of player (_player)
	*
	* @return the color of player
	*/
	char getPlayer();

	/**
	* pure virtual function that get sign for specific piece
	*
	* @return one letter of specific piece (e.g. King is 'k')
	*/
	virtual char getSign() const = 0;

	/**
	* pure virtual function that get unicode symbol for specific piece
	*
	* @return string of unicode for specific piece (e.g. King is "\u265A")
	*/
	virtual std::string getUnicodeSymbol() const = 0;

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
	virtual int isMoveLegal(int positionRow, int positionCol, int targetRow, int targetCol,
							Piece *board[8][8], bool moveOrCheck);

	/**
	* function to use in case of deep copy
	*
	* @return pointer for new derived class
	*/
	virtual Piece* clone() const = 0;
};

#endif