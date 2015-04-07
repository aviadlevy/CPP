/**
* file that contain the declaring of the class GameGUI and the declaring for the constructor
* we'll implement in GameGUI.cpp
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#ifndef GAMEGUI_HPP
#define GAMEGUI_HPP

#define DEFAULT_NUM 4
#define DEFAULT_CHAR 'd'

/**
* class that hold the game arguments: length and letter
*/
class GameArgs
{
private:
	int _length;
	char _maxLetter;
public:
	//default constructor
	GameArgs() : GameArgs(DEFAULT_NUM, DEFAULT_CHAR)
	{
	};

	//only 1 int input, the letter will be default
	GameArgs(int length) : GameArgs(length, DEFAULT_CHAR)
	{
	};

	//only 1 char input, the length will be default
	GameArgs(char maxLetter) : GameArgs(DEFAULT_NUM, maxLetter)
	{
	};

	//user gave us 2 arguments
	GameArgs(int length, char maxLetter) : _length(length), _maxLetter(maxLetter)
	{
	};

	//geters for both arguments

	/**
	* function to get _length which is private argument
	*
	* @return the length the user requested
	*/
	int getLength() const;

	/**
	* function to get _maxLetter which is private argument
	*
	* @return the maximum letter the user requested
	*/
	char getMaxLetter() const;
};

#endif