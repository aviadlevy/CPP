/**
* file that contain the declaring for class of Knight piece, and its function
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Piece.hpp"

#ifndef KNIGHT_HPP
#define KNIGHT_HPP

class Knight : public Piece
{
	std::string _unicode = "\u265E";
	char _sign = 'n';

	/**
	* function that check if move is legal for Knight.
	*
	* @param positionRow the row the Knight in
	* @param positionCol the column the Knight in
	* @param targetRow the row the Knight want to go to
	* @param targetCol the column the Knight want to go to
	* @param _board the game _board with all pieces
	* @param moveOrCheck true if we want to move the Knight. false if we just want to check.
	* @return 1 if legal. 0 otherwise.
	*/
	virtual int _isMoveLegalForSpecificPiece(int positionRow, int positionCol, int targetRow,
											 int targetCol, Piece *board[NUM_OF_ROWS][NUM_OF_ROWS],
											 bool moveOrCheck);

public:

	/**
	* constructor for Knight
	*
	* @param player the color for the player
	*/
	Knight(char player) : Piece(player)
	{
	}

	/**
	* destructor for Knight
	*/
	~Knight()
	{
	}

	/**
	* virtual function that get sign for Knight
	*
	* @return one letter of Knight ('n')
	*/
	virtual char getSign() const;

	/**
	* virtual function that get unicode symbol for Knight
	*
	* @return string of unicode for Knight ("\u265E")
	*/
	virtual std::string getUnicodeSymbol() const;

	/**
	* function to use in case of deep copy
	*
	* @return pointer for new Knight class
	*/
	virtual Piece* clone() const;
};

#endif