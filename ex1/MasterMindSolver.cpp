/**
* file that contain the main function and the helping methods for guessing string from user
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <bits/stl_numeric.h>
#include "MasterMind.hpp"
#include "MasterMindSolver.hpp"

#define STRING_FINISH "finish"
#define EMPTY_STRING ""

using namespace std;

/**
* global param contain the number of strings entered in createAllPossibleRecursive
*/
int gCellInStringArr = 0;

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
* @return 0 if exit normally, 1 if error happen
*/
int playGame(GameArgs mind)
{
	printToUser(CHOOSE_STRING, mind);
	int turns = 0, bulls = 0, cows = 0, *countChars;
	string set = createSet(mind, turns, countChars, bulls, cows);
	if (set.empty())
	{
		return 1;
	}
	if (!set.compare(STRING_FINISH))
	{
		return 0;
	}
	int pos = factorialWithReturns(mind.getLength(), countChars,
								   mind.getMaxLetter() - CHAR_TO_START);
	string *allPossible = new string[pos];
	createAllPossibleRecursive(allPossible, EMPTY_STRING, set, set, bulls, cows, mind);
	pos = gCellInStringArr;
	bool isFinish = false;
	while (!isFinish)
	{
		//check if we still got an option to guess
		if (!pos)
		{
			delete[] allPossible;
			printError(WRONG_BULLS_AND_COWS);
			return 1;
		}
		// we raffles index in range of [0..allPossible.length] so we'll pick one string.
		int i = rand() % pos;
		turns++;
		printToUser(MY_GUESS_IS, mind, allPossible[i]);
		cin >> bulls >> cows;
		if (cin.fail() || !checkBullsAndCows(bulls, cows, mind))
		{
			delete[] allPossible;
			printError(ILLIGAL_INPUT);
			return 1;
		}
		if (bulls == mind.getLength() && !cows)
		{
			printToUser(I_DID_IT, mind, "", turns);
			isFinish = true;
		}
		else
		{
			clearPossible(bulls, cows, allPossible[i], &allPossible, &pos, mind);
		}
	}
	delete[] allPossible;
	return 0;
}

/**
* calculate the factorial when some objects are coming in groups, and we don't want to return
*
* @param num the number of all objects
* @param countChars the number of repetition for each object
* @param the number of different objects
*/
int factorialWithReturns(int num, int *countObjects, int length)
{
	int factor = factorial(num);
	int sumOfReturns = 1;
	for (int i = 0; i <= length - CHAR_TO_START; i++)
	{
		sumOfReturns *= factorial(countObjects[i]);
	}
	return factor / sumOfReturns;
}

/**
* calculate factorial of number
*
* @param num the number we want to calculate its factorial
* @return the factorial
*/
int factorial(int num)
{
	return (num == 1 || num == 0) ? 1 : factorial(num - 1) * num;
}

/**
* figure out the letters the user think about.
*
* @param mind the game arguments
* @param turns the number of turns it took. update also in playGame
* @param countChar array in length of possible letters, initialize to zero, and update the num of
* 		 letter for each cell ('a' to maxLetter)
* @param bulls update every user input, and keep the last bulls entered
* @param cows update every user input, and keep the last cows entered
* @return set of letters in user's brain
*/
string createSet(GameArgs mind, int &turns, int *&count, int &bulls, int &cows)
{
	string set = "";
	char ch = CHAR_TO_START;
	count = new int[mind.getMaxLetter() - ch + 1]();
	bool isFinish = false;
	for (int i = 0; !isFinish && ch <= mind.getMaxLetter(); ch++, i++)
	{
		int sum = accumulate(count, count + (mind.getMaxLetter() - CHAR_TO_START), 0);
		string temp((unsigned int) (mind.getLength() - sum), ch);
		set += temp;
		turns++;
		printToUser(MY_GUESS_IS, mind, set);
		cin >> bulls >> cows;
		if (cin.fail() || !checkBullsAndCows(bulls, cows, mind))
		{
			printError(ILLIGAL_INPUT);
			return EMPTY_STRING;
		}
		if (bulls == mind.getLength() && !cows)
		{
			printToUser(I_DID_IT, mind, "", turns);
			isFinish = true;
			return STRING_FINISH;
		}
		else
		{
			count[i] += bulls + cows - sum;
			set = "";
			for (int j = 0, c = CHAR_TO_START; j <= i; j++, c++)
			{
				string newTemp((unsigned int) count[j], (char) c);
				set += newTemp;
			}
			sum = accumulate(count, count + mind.getMaxLetter() - CHAR_TO_START + 1, 0);
			if (sum >= mind.getLength())
			{
				isFinish = true;
			}
		}
	}
	return set;
}

/**
* clear all unpossible strings to guess, so we'll not use them again. we'll enter all the srings
* that still possible to a temp array, and in the end we'll update the pointer to our new temp
* array, and we'll free the old one.
*
* @param bulls num of bulls the user entered
* @param cows num of cows the user entered
* @guess the computer guess
* @param stringArr pointer to an array of strings. all changes will apply on the variable in the
* 		 function which sent the array
* @param pos pointer to number of possible strings. we'll update when clearing ends
* @param mind hold user initial input
*/
void clearPossible(int bulls, int cows, string guess, string **stringArr, int *pos,
				   GameArgs mind)
{
	int tempBulls = 0, tempCows = 0;
	string *tempStringArr = new string[(int) *pos];
	int newPosIndex = 0;
	for (int i = 0; i < (int) *pos; i++)
	{
		tempBulls = claculateBullsAndCows((*stringArr)[i], guess, tempCows, mind);
		if (tempBulls == bulls && tempCows == cows)
		{
			tempStringArr[newPosIndex] = (*stringArr)[i];
			newPosIndex++;
		}
	}
	*pos = newPosIndex;
	delete[] *stringArr;
	*stringArr = tempStringArr;
}

/**
* building all possible string with specific letter from set and length of mind.getLength().
* the function will work recursively. on first iteration, we got an empty string, and we'll add
* new char every iteration. when we reach the requested length, we'll check if the string is
* match with same bulls and cows, and if yes, we'll add the string we have, and stop current
* recursion. when we go back one step, we'll add the next char to the string and again we've
* reached the requested length. and again, and again we'll have eventually all the possible
* strings.
*
* @param stringArr the array of string we'll keep the string to
* @param str the string we building
* @param set holds the letters possible
* @param setToCompare to check the bulls and cows against
* @param bulls the num of bulls in setToCompare
* @param cows the num of cows in setToCompare
* @param mind the arguments of the game
*/
void createAllPossibleRecursive(string *&stringArr, string str, string set,
								const string setToCompare, int bulls, int cows, GameArgs mind)
{
	int len = set.length();
	//we accomplished the correct length
	if (len == 0)
	{
		int tempBulls = 0, tempCows = 0;
		tempBulls = claculateBullsAndCows(str, setToCompare, tempCows, mind);
		if (tempBulls == bulls && tempCows == cows)
		{
			stringArr[gCellInStringArr] = str;
			gCellInStringArr++;
		}
		return;
	}

	for (unsigned int i = 0; i < (unsigned int) len; i++)
	{
		string newStr = str + set[i];
		string newSet = set.substr(0, i) + set.substr(i + 1, set.length() - (i + 1));
		createAllPossibleRecursive(stringArr, newStr, newSet, setToCompare, bulls, cows, mind);
	}
}

/**
* check if user's bulls and cows are legal
*
* @param bulls the user's bulls
* @param cows the user's cows
* @param mind hold user initial input
*/
bool checkBullsAndCows(int bulls, int cows, GameArgs mind)
{
	return cows + bulls <= mind.getLength();
}

/**
* printing informative massages for user
*
* @param typeOfPrinting the requested massage
* @param mind hold user initial input
* @param guess the computer guess
* @param turns the number of turns it took to guess
*/
void printToUser(int typeOfPrinting, GameArgs mind, string guess, int turns)
{
	switch (typeOfPrinting)
	{
		case CHOOSE_STRING:
		{
			cout << "Please choose " << mind.getLength() << " letters in the range 'a' to '" <<
					mind.getMaxLetter() << "':" << endl;
			break;
		}
		case MY_GUESS_IS:
		{
			cout << "My guess is " << guess << endl;
			break;
		}
		case I_DID_IT:
		{
			cout << "I did it in " << turns << " guesses!" << endl;
			break;
		}
		default:
		{
			break;
		}
	}
}

