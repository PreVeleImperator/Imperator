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

int main ()
{
	Xoshiro256Seed (0x123456789ABCDEF);

	while (true)
	{
		string fen;
		cout << "FEN: ";
		getline (cin, fen);


		system ("cls");
		Fen (fen);
		DisplayBoard (playerToMoveAtStart, enpassantAtStart, fiftyMovesAtStart);


		Move bestMove;
		int  bestValue;

		for (int depth = 1; depth < MAX_DEPTH; depth ++)
		{
			BestMove (bestMove, bestValue, depth);
			cout << bestValue << " | " << Coordinates (bestMove.fromI) << Coordinates (bestMove.toI) << "\n";
		}
	}

	return 0;
}