/**
* file that contain the main function and the helping methods for leting the user solve string
* from computer
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include <iostream>
#include "erand.h"
#include "GameArgs.hpp"
#include "MasterMindPlay.hpp"
#include "MasterMind.hpp"

using namespace std;

/**
* the main function
*/
int main(int argc, char **argv)
{
	if (argc > NUM_OF_PARAM)
	{
		return printError(TOO_MUCH_ENOUGH_PARAM);
	}
	GameArgs masterMind = checkInput(argc, argv);
	if (masterMind.getLength() == ERROR_NUM)
	{
		return 1;
	}
	return playGame(masterMind);
}

/**
* the function that will manage the game
*
* @param mind hold the user initial input
*/
int playGame(GameArgs mind)
{
	string randString = createRandString(mind);
	bool isFinished = false;
	int turns = 0;
	while (!isFinished)
	{
		turns++;
		printToUser(ENTER_GUESS, mind.getLength(), mind.getMaxLetter());
		string input = "";
		getline(cin, input);
		if (!checkStringInput(input, mind.getMaxLetter()))
		{
			return printError(ILLIGAL_INPUT);
		}
		if ((int) input.length() != mind.getLength())
		{
			return printError(ILLIGAL_INPUT);
		}
		int cow = 0;
		int bull = claculateBullsAndCows(input, randString, cow, mind);
		printToUser(END_OF_TURN, bull, cow);
		if (bull == mind.getLength())
		{
			printToUser(WINNING, bull, cow, turns);
			isFinished = true;
		}
	}
	return 0;
}

/**
* function that creates randomize string with specific length and letters
*
* @param mind hold the user initial input
* @return randomize string
*/
string createRandString(GameArgs mind)
{
	string str = "";
	for (int i = 0; i < mind.getLength(); i++)
	{
		str += randomChar(mind.getMaxLetter());
	}
	return str;
}

/**
* check if the strings the user inputs during the game is legit
*
* @param input the user's string
* @param letter max letter of the game
* @return true if legit, false otherwise
*/
bool checkStringInput(string input, char letter)
{
	for (unsigned int i = 0; i < input.length(); i++)
	{
		if (input[i] > letter || input[i] < CHAR_TO_START)
		{
			return false;
		}
	}
	return true;
}

/**
* printing informative massages for user
*
* @param typeOfPrinting the requested massage
* @param lengthOrBull for some printing will hold the length of string, and for others will hold
* 		 the number of bulls
* @param letterOrCow for some printing will hold the max letter, and for others will hold
* 		 the number of cows
* @param turns the number of turns it took to guess
*/
void printToUser(int typeOfPrinting, int lengthOrBull, int letterOrCow, int turns)
{
	switch (typeOfPrinting)
	{
		case ENTER_GUESS:
		{
			cout << "Please enter a guess of " << lengthOrBull << " letters between 'a' and '" <<
					(char) letterOrCow << "':" << endl;
			break;
		}
		case END_OF_TURN:
		{
			cout << "You got " << lengthOrBull << " bulls and " << letterOrCow << " cows." << endl;
			break;
		}
		case WINNING:
		{
			cout << "It took you " << turns << " guesses." << endl;
			break;
		}
		default:
		{
			break;
		}
	}
}