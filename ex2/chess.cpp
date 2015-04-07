/**
* file that contain the implementing for all functions relevant for the board game
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "Board.hpp"
#include "chess.hpp"

#define USER_MOVE_LENGTH 4

using namespace std;

/**
* global char for the player turn (what color playing now)
*/
char gTurn;

/**
* main function to manage chess.cpp
*/
int main()
{
	//reset _board game
	Board *boardGame = new Board();
	playGame(boardGame);
	delete boardGame;
	return 0;
}

/**
* function that manage the game.
*
* @param boardGame initialize _board to play
*/
void playGame(Board *boardGame)
{
	string whitePlayer, blackPlayer;
	printToUser(GET_NAMES, "white");
	getline(cin, whitePlayer);
	printToUser(GET_NAMES, "black");
	getline(cin, blackPlayer);
	gTurn = WHITE;
	//continue playing as long as the game isn't over
	while (!isOver(boardGame, whitePlayer, blackPlayer))
	{
		getNextMove(boardGame, whitePlayer, blackPlayer);
		//after turn is over switch player turn
		gTurn = (gTurn == WHITE) ? BLACK : WHITE;
	}
}

/**
* check if game is over. if yes check if it's checkmate or stalemate
*
* @param _board game _board
* @param whitePlayer white player name
* @param blackPlayer black player name
* @return 1 if over, 0 otherwise
*/
int isOver(Board *board, string whitePlayer, string blackPlayer)
{
	//check if user can move
	int canMove = board->canMove(gTurn);
	if (!canMove)
	{
		board->print();
		//if can't move and also in check, then it's checkmate
		if (board->isInCheck(gTurn))
		{
			printToUser(CHECKMATE, (gTurn == BLACK) ? whitePlayer : blackPlayer);
		}
		//if can't move and not in check then it's satelmate
		else
		{
			printToUser(TIE, (gTurn == WHITE) ? whitePlayer : blackPlayer);
		}
	}
	return !canMove;
}

/**
* manage each turn for specific player
*
* @param _board the _board game
* @param whitePlayer white player name
* @param blackPlayer black player name
*/
void getNextMove(Board *board, string whitePlayer, string blackPlayer)
{
	int isValid = 0, positionRow, positionCol, targetRow, targetCol;
	string move;
	do
	{
		board->print();
		//first check if player in check
		if (board->isInCheck(gTurn))
		{
			printToUser(CHECK, "");
		}
		printToUser(USER_TURN, (gTurn == WHITE) ? whitePlayer : blackPlayer);
		cin >> move;
		if (checkMoveString(move, &positionRow, &positionCol, &targetRow, &targetCol))
		{
			Piece *piece = board->_board[positionRow][positionCol];
			//check if piece in starting position is with player color
			if (piece && piece->getPlayer() == gTurn)
			{
				//check if piece can be moved to target
				if (piece->isMoveLegal(positionRow, positionCol, targetRow, targetCol,
					board->_board, true))
				{
					//save target cell temporally
					Piece *tempPiece = board->_board[targetRow][targetCol];
					board->_board[targetRow][targetCol] = board->_board[positionRow][positionCol];
					board->_board[positionRow][positionCol] = 0;
					//check if not in check, we can delete origianl target piece, and exit the
					// function
					if (!board->isInCheck(gTurn))
					{
						delete tempPiece;
						isValid = 1;
					}
					//if in check return _board to its original state
					else
					{
						board->_board[positionRow][positionCol] = board->_board[targetRow][targetCol];
						board->_board[targetRow][targetCol] = tempPiece;
					}
				}
			}
		}
		if (!isValid)
		{
			printToUser(INVALID, "");
		}
	}
	while (!isValid);
}

/**
* check if the moving string the user entered is legal
*
* @param move the move string
* @param positionRow update inside the function to converted value (between 0 to 7)
* @param positionCol update inside the function to converted value (between 0 to 7)
* @param targetRow update inside the function to converted value (between 0 to 7)
* @param targetCol update inside the function to converted value (between 0 to 7)
* @return 1 if the string is legal, 0 otherwise
*/
int checkMoveString(string move, int *positionRow, int *positionCol, int *targetRow,
					int *targetCol)
{
	if (move.length() != USER_MOVE_LENGTH)
	{
		return 0;
	}
	//convert sring to value between [0..7]
	*positionCol = (move[0] - 'A');
	*positionRow = (move[1] - '1');
	*targetCol = (move[2] - 'A');
	*targetRow = (move[3] - '1');
	//check if is actually in desired range
	if (checkIfInRange(*positionCol) && checkIfInRange(*positionRow) && checkIfInRange(*targetCol)
		&& checkIfInRange(*targetRow))
	{
		return 1;
	}
	return 0;
}

/**
* check if number is in range of zero to 7
*
* @param num the number to check
* @return 1 if in range, 0 otherwise
*/
int checkIfInRange(int num)
{
	return (num > NUM_OF_ROWS - 1 || num < 0) ? 0 : 1;
}

/**
* some printing with information to users
*
* @param typeOfPrinting the type of massage we want to print
* @param str some additional string added to massage
*/
void printToUser(int typeOfPrinting, string const str)
{
	switch (typeOfPrinting)
	{
		case GET_NAMES:
		{
			cout << "Enter " << str << " player name:" << endl;
			break;
		}
		case USER_TURN:
		{
			cout << str << ": Please enter your move:" << endl;
			break;
		}
		case INVALID:
		{
			cout << "\33[37;41millegal move\33[0m" << endl;
			break;
		}
		case CHECK:
		{
			cout << "\33[37;41mCheck!\33[0m" << endl;
			break;
		}
		case CHECKMATE:
		{
			cout << str << " won!" << endl;
			break;
		}
		case TIE:
		{
			cout << str << " can't move! It's a stalemate" << endl;
			break;
		}
		default:
		{
			break;
		}
	}
}
