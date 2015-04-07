#ifndef ERAND_H
#define ERAND_H

#include <cstdlib>
#include <ctime>
#include <cassert>

/**
* @brief randomChar returns a random character, in the range 'a' to a givven character
* @param C the maximal character to be returned
* @return a random character
*/
inline char randomChar(char C = 'd');

char randomChar(char C)
{
	return (char) (rand() % (C - 'a' + 1) + 'a');
}

#endif // ERAND_H
