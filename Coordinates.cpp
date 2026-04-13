#pragma warning (disable : 4146)

#include "Pieces.h"

string Coordinates (int square)
{
	char ch1 = (square % 8) + 'a';
	char ch2 = (7 - (square / 8)) + '1';

	return {ch1, ch2};
}