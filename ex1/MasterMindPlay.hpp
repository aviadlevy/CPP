/**
* file that contain the declaring for helping methods in MasterMindPlay.cpp
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#ifndef MASTERMINDPLAY_HPP
#define MASTERMINDPLAY_HPP

#include <string>

//used for switch case in printing the user (special for MasterMindPlay.cpp)
#define ENTER_GUESS 0
#define WINNING 1
#define END_OF_TURN 2

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
void printToUser(int typeOfPrinting, int lengthOrBull, int letterOrCow, int turns = 0);

/**
* the function that will manage the game
*
* @param mind hold the user initial input
*/
int playGame(GameArgs mind);

/**
* function that creates randomize string with specific length and letters
*
* @param mind hold the user initial input
* @return randomize string
*/
std::string createRandString(GameArgs mind);

/**
* check if the strings the user inputs during the game is legit
*
* @param input the user's string
* @param letter max letter of the game
* @return true if legit, false otherwise
*/
bool checkStringInput(std::string input, char letter);

#endif