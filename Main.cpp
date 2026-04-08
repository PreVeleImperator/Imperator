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


		uint64_t pinnedPieces [64];
		uint64_t attackedSquares = 0;
		uint64_t    checkSquares = FULL_UINT;

		int movesCount = 0;
		
		bool check       = false;
		bool doubleCheck = false;

		fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);


		AttackedSquares (playerToMoveAtStart, attackedSquares, check, doubleCheck, checkSquares);
		PinnedPieces    (playerToMoveAtStart, pinnedPieces);


		cout << check << " " << doubleCheck << "\n";

		cout << "attackedSquares\n";
		Bits::Display (attackedSquares);

		cout << "checkSquares\n";
		Bits::Display (checkSquares);

		cout << "pinnedPieces\n";
		for (int square = 0; square < 64; square ++)
			if (pinnedPieces [square] != FULL_UINT)
			{
				cout << Coordinates (square) << "\n";
				Bits::Display (pinnedPieces [square]);
			}
	}

	return 0;
}