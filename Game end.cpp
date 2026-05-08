#include <bit>
#include "Search.h"
#include "Pieces.h"
using namespace std;

static bool InsufficientMaterial ()
{
	if (*PAWNS [WHITE] | *PAWNS [BLACK])
		return false;

	if (*QUEENS [WHITE] | *QUEENS [BLACK])
		return false;

	if (*ROOKS [WHITE] | *ROOKS [BLACK])
		return false;

	if (popcount (*KNIGHTS [WHITE]) >= 2  ||  popcount (*KNIGHTS [BLACK]) >= 2)
		return false;

	if (popcount (*BISHOPS [WHITE]) >= 2  ||  popcount (*BISHOPS [BLACK]) >= 2)
		return false;


	return true;
}

int GameEnd (int ply, bool check, int movesCount, int fiftyMoves)
{
	if (!movesCount)
		return check ? CHECKMATE + ply : 0;

	if (fiftyMoves == 100)
		return 0;

	if (InsufficientMaterial ())
		return 0;

	return NO_END;
}

int PositionRepeated (int ply, int fiftyMoves)
{
	int count = 0;
	
	for (int i = ply - 2; i >= ply - fiftyMoves; i -= 2)
		if (actualPath [i] == actualPath [ply])
			count ++;

	return count;
}