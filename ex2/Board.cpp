/**
* file that contain the implementing for class of Board - the class that hold all function relevant
* for the board game
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Pawn.hpp"
#include "Knight.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Board.hpp"

#define START_RANGE 'A'
#define END_RANGE 'H'

#define CLEAN_SCREEN "\33[2J"

#define KING_SIGN 'k'

#define WHITE_TEXT "37"
#define BLACK_TEXT "30"

using namespace std;

/**
* default constructor for _board. reset _board to start point
*/
Board::Board()
{
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_ROWS; j++)
		{
			_board[i][j] = 0;
		}
	}

	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		_board[1][i] = new Pawn(WHITE);
		_board[6][i] = new Pawn(BLACK);
	}

	_board[7][0] = new Rook(BLACK);
	_board[0][0] = new Rook(WHITE);
	_board[7][1] = new Knight(BLACK);
	_board[0][1] = new Knight(WHITE);
	_board[7][2] = new Bishop(BLACK);
	_board[0][2] = new Bishop(WHITE);
	_board[7][4] = new King(BLACK);
	_board[0][4] = new King(WHITE);
	_board[7][3] = new Queen(BLACK);
	_board[0][3] = new Queen(WHITE);
	_board[7][5] = new Bishop(BLACK);
	_board[0][5] = new Bishop(WHITE);
	_board[7][6] = new Knight(BLACK);
	_board[0][6] = new Knight(WHITE);
	_board[7][7] = new Rook(BLACK);
	_board[0][7] = new Rook(WHITE);
}

/**
* destructor for Board
*/
Board::~Board()
{
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_ROWS; j++)
		{
			delete _board[i][j];
			_board[i][j] = 0;
		}
	}
}

/**
* copy constructor
*
* @param boardToCopy type Board to copy to new Board
*/
Board::Board(const Board &boardToCopy)
{
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_ROWS; j++)
		{
			_board[i][j] = boardToCopy._board[i][j];
		}
	}
}

/**
* deep copy _board
*
* @param boardToCopy the 2d array of pieces for specific _board
*/
Board::Board(Piece *boardToCopy[NUM_OF_ROWS][NUM_OF_ROWS])
{
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_ROWS; j++)
		{
			if(boardToCopy[i][j])
			{
				//use clone() for deep copy
				_board[i][j] = boardToCopy[i][j]->clone();
			}
			else
			{
				_board[i][j] = 0;
			}
		}
	}
}

/**
* print the _board
*/
void Board::print()
{
	//clear the screen
	cout << CLEAN_SCREEN;
	printRowLetters();
	for (int i = 7; i >= 0; i--)
	{
		cout << (char) ('1' + i) << " ";
		for (int j = 0; j < NUM_OF_ROWS; j++)
		{
			//initialize to values for non-occupied cell
			string isColor = "0";
			string pieceUnicode = " ";
			if (_board[i][j])
			{
				isColor = (_board[i][j]->getPlayer() == WHITE) ? WHITE_TEXT : BLACK_TEXT;
				pieceUnicode = _board[i][j]->getUnicodeSymbol();
			}
			//print the cell (with current cell colors)
			cout << "\33[" << isColor
					<< ((j % 2 && i % 2) || (!(j % 2) && !(i % 2)) ? ";42m" : ";46m")
					<< pieceUnicode << "\33[0m";
		}
		cout << " " << (char) ('1' + i) << endl;
	}
	cout << endl;
	printRowLetters();
}

/**
* check if player is in check
*
* @param playerColor the player we want to check if in check
* @return 1 if in check. 0 otherwise
*/
int Board::isInCheck(char playerColor)
{
	int kingRow = 0, kingCol = 0;
	bool isBreak = false;
	//find king position
	for (int i = 0; i < NUM_OF_ROWS && !isBreak; i++)
	{
		for (int j = 0; j < NUM_OF_ROWS; j++)
		{
			if (_board[i][j] && _board[i][j]->getPlayer() == playerColor)
			{
				if (_board[i][j]->getSign() == 'k')
				{
					kingRow = i;
					kingCol = j;
					isBreak = true;
					break;
				}
			}
		}
	}
	//find out if any of the opposite pieces can move to king location
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_ROWS; j++)
		{
			if (_board[i][j] && _board[i][j]->getPlayer() != playerColor)
			{
				//because there is no chance that the other king is within step for our king,
				// and we don't want to enter infinity loop (in isMoveLegal we check again if
				// isInCheck) so let's continue!
				if(_board[i][j]->getSign() == KING_SIGN)
				{
					continue;
				}
				if (_board[i][j]->isMoveLegal(i, j, kingRow, kingCol, _board, false))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

/**
* check if player can move, without causing check.
*
* @param player the player we want to check if can move
* @return 1 if can move. 0 otherwise.
*/
int Board::canMove(char player)
{
	//search all _board for piece with "player" color
	for (int i = 0; i < NUM_OF_ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_ROWS; j++)
		{
			//we found out the location for our piece
			if (_board[i][j] && _board[i][j]->getPlayer() == player)
			{
				for (int iTarget = 0; iTarget < NUM_OF_ROWS; iTarget++)
				{
					for (int jTarget = 0; jTarget < NUM_OF_ROWS; jTarget++)
					{
						//check if our piece can move to target location
						if (_board[i][j]->isMoveLegal(i, j, iTarget, jTarget, _board, false))
						{
							//move the piece temporally
							Piece *temp = _board[iTarget][jTarget];
							_board[iTarget][jTarget] = _board[i][j];
							_board[i][j] = 0;
							//check if move causing check
							int notCheck = !isInCheck(player);
							//return _board to its state
							_board[i][j] = _board[iTarget][jTarget];
							_board[iTarget][jTarget] = temp;
							if (notCheck)
							{
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

/**
* print row of letters between 'A' to 'H'
*/
void printRowLetters()
{
	cout << "  ";
	for (char row = START_RANGE; row <= END_RANGE; row++)
	{
		cout << row;
	}
	cout << endl << endl;
}
