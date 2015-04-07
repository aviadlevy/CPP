/**
* file that contain the declaring for helping methods in MasterMindSolver.cpp
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#ifndef MASTERMINDSOLVER_HPP
#define MASTERMINDSOLVER_HPP

#include "GameArgs.hpp"
#include <string>

#define CHOOSE_STRING 0
#define MY_GUESS_IS 1
#define I_DID_IT 2

/**
* the function that will manage the game
*
* @param mind hold the user initial input
* @return 0 if exit normally, 1 if error happen
*/
int playGame(GameArgs mind);

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
void createAllPossibleRecursive(std::string *&stringArr, std::string str, std::string
set, const std::string setToCompare, int bulls, int cows,
								GameArgs mind);

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
void clearPossible(int bulls, int cows, std::string guess, std::string **stringArr, int *pos,
				   GameArgs mind);

/**
* printing informative massages for user
*
* @param typeOfPrinting the requested massage
* @param mind hold user initial input
* @param guess the conputer guess
* @param turns the number of turns it took to guess
*/
void printToUser(int typeOfPrinting, GameArgs mind, std::string guess = "", int turns = 0);

/**
* check if user's bulls and cows are legal
*
* @param bulls the user's bulls
* @param cows the user's cows
* @param mind hold user initial input
* @return true if everything is ok, false otherwise
*/
bool checkBullsAndCows(int bulls, int cows, GameArgs mind);

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
std::string createSet(GameArgs mind, int &turns, int *&countChar, int &bulls, int &cows);

/**
* calculate factorial of number
*
* @param num the number we want to calculate its factorial
* @return the factorial
*/
int factorial(int num);

/**
* calculate the factorial when some objects are coming in groups, and we don't want to return
*
* @param num the number of all objects
* @param countChars the number of repetition for each object
* @param the number of different objects
*/
int factorialWithReturns(int num, int *countObjects, int length);

#endif