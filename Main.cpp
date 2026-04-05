#include <iostream>
#include <string>

#include "Pieces.h"
#include "Coordinates.h"
#include "Search.h"
#include "Bits.h"
#include "Pieces moves.h"
#include "Xoshiro256.h"
using namespace std;

int main ()
{
	Xoshiro256Seed (0xDEADBEEFCAFEBABEULL);

	/*string fen;
	cout << "FEN: ";
	getline (cin, fen);

	Fen (fen);
	DisplayBoard (toMoveAtStart, enpassantAtStart, fiftyMovesAtStart);*/

	PiecesMoves::GenerateMagics (PiecesMoves::bishopCombinations, PiecesMoves::bishopShifts, PiecesMoves::bishopCombinationsCounts, PiecesMoves::bishopOffsets);

	return 0;
}