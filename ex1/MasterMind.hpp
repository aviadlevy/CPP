/**
* file that contain the declaring for the helping methods for both play and solve games
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#ifndef MASTERMIND_HPP
#define MASTERMIND_HPP

#include <string>
#include "GameArgs.hpp"

#define NUM_OF_PARAM 3

//used for switch in printError
#define TOO_MUCH_ENOUGH_PARAM 0
#define USAGE 1
#define ILLIGAL_INPUT 2
#define WRONG_BULLS_AND_COWS 3

#define LENGTH argv[1]
#define MAX_LETTER argv[2]

#define ERROR_NUM -1

#define CHAR_TO_START 'a'

/**
* common error printing for both files
*
* @param typeOfError the type of error to print
* @return 1 the return exit code for error during process
*/
int printError(int typeOfError);

/**
* function that check correction and construct GameArgs that hold the length and letter that the
* program will work with.
*
* @param numOfArgs the number of arguments the user entered
* @param argv array of char* which hold the input from user
* @return new GameArgs that hold the requested length and letter, or the default
*/
GameArgs checkInput(int numOfArgs, char **argv);

/**
* clculate the num of bulls and string with 2 given strings.
*
* @param input string we want to check
* @param stringToFigure the string we check against
* @param cow a pointer to the cows, which will updates in the function
* @param mind hold the user initial input
* @return num of bulls
*/
int claculateBullsAndCows(std::string input, std::string stringToFigure, int &cow, GameArgs mind);

#endif