/**
* file that contain the  helping methods for both solver and play files
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include <iostream>
#include <bits/stl_algo.h>
#include <string.h>
#include "GameArgs.hpp"
#include "MasterMind.hpp"

using namespace std;

/**
* function that check correction and construct GameArgs that hold the length and letter that the
* program will work with.
*
* @param numOfArgs the number of arguments the user entered
* @param argv array of char* which hold the input from user
* @return new GameArgs that hold the requested length and letter, or the default
*/
GameArgs checkInput(int numOfArgs, char **argv)
{
	GameArgs masterMindError(ERROR_NUM);
	GameArgs *masterMind;
	switch (numOfArgs)
	{
		case NUM_OF_PARAM:
		{
			string len(LENGTH);
			//check if first argument is all digit non-zero and second is one lower case letter
			if (!std::all_of(len.begin(), len.end(), ::isdigit) || !atoi(LENGTH) ||
					strlen(MAX_LETTER) != 1 || !islower(*MAX_LETTER))
			{
				printError(USAGE);
				return masterMindError;
			}
			char letter = MAX_LETTER[0];
			masterMind = new GameArgs(atoi(LENGTH), letter);
			break;
		}
		case NUM_OF_PARAM - 1:
		{
			string unkown(argv[1]);
			//if the param entered is digit
			if (std::all_of(unkown.begin(), unkown.end(), ::isdigit))
			{
				masterMind = new GameArgs(atoi(argv[1]));
			}
			else if (strlen(argv[1]) == 1 && islower(*argv[1]))
			{
				char letter = argv[1][0];
				masterMind = new GameArgs(letter);
			}
			else
			{
				printError(USAGE);
				return masterMindError;
			}
			break;
		}
		case NUM_OF_PARAM - 2:
		{
			masterMind = new GameArgs();
			break;
		}
		default:
		{
			return masterMindError;
		}
	}
	GameArgs mindToReturn = *masterMind;
	delete masterMind;
	return mindToReturn;
}

/**
* clculate the num of bulls and string with 2 given strings.
*
* @param input string we want to check
* @param stringToFigure the string we check against
* @param cow a pointer to the cows, which will updates in the function
* @param mind hold the user initial input
* @return num of bulls
*/
int claculateBullsAndCows(string input, string stringToFigure, int &cow, GameArgs mind)
{
	int bull = 0;
	cow = 0;
	for (int ch = CHAR_TO_START; ch <= mind.getMaxLetter(); ch++)
	{
		int appearInGuess = 0, appearInRand = 0, tempBull = 0;
		for (int i = 0; i < mind.getLength(); i++)
		{
			if (ch == input[i])
			{
				appearInGuess++;
				if (input[i] == stringToFigure[i])
				{
					tempBull++;
				}
			}
			if (ch == stringToFigure[i])
			{
				appearInRand++;
			}
		}
		cow += (appearInRand <= appearInGuess ? appearInRand : appearInGuess) - tempBull;
		bull += tempBull;
	}
	return bull;
}

/**
* common error printing for both files
*
* @param typeOfError the type of error to print
* @return 1 the return exit code for error during process
*/
int printError(int typeOfError)
{
	switch (typeOfError)
	{
		case TOO_MUCH_ENOUGH_PARAM:
		{
			cout << "You entered too much parameters" << endl << "Exiting..." << endl;
			break;
		}
		case USAGE:
		{
			cout << "Usage: ./mastermindplay <length> <max letter>" << endl << "Exiting..." <<
					endl;
			break;
		}
		case ILLIGAL_INPUT:
		{
			cout << "You entered illegal string" << endl << "Exiting..." << endl;
			break;
		}
		case WRONG_BULLS_AND_COWS:
		{
			cout << "You didn't calculate the score correctly" << endl << "Exiting..." << endl;
			break;
		}
		default:
		{
			break;
		}

	}
	return 1;
}
