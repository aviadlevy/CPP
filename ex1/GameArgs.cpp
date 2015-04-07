/**
* file that contain the geters for our peivate arguments
*
* @Author - Aviad Levy
* @CS Login - aviadle
*/

#include "GameArgs.hpp"

/**
* function to get _length which is private argument
*
* @return the length the user requested
*/
int GameArgs::getLength() const
{
	return _length;
}

/**
* function to get _maxLetter which is private argument
*
* @return the maximum letter the user requested
*/
char GameArgs::getMaxLetter() const
{
	return GameArgs::_maxLetter;
}