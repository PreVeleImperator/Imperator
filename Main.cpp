#pragma warning (disable : 4146)

#include <iostream>
#include <string>
#include <bit>
#include "Pieces.h"
#include "Coordinates.h"
#include "Search.h"
#include "Bits.h"
#include "Pieces moves.h"
#include "Xoshiro256.h"
using namespace std;
using namespace PiecesMoves;
using namespace Search;

int main ()
{
	Xoshiro256Seed (0x123456789ABCDEF);

	GenerateNonSlidingMoves (knightDirections, knightBorders, 8);

	/*while (true)
	{
		string fen;
		cout << "FEN: ";
		getline (cin, fen);

		system ("cls");

		Fen (fen);
		DisplayBoard (toMoveAtStart, enpassantAtStart, fiftyMovesAtStart);
	}*/

	return 0;
}