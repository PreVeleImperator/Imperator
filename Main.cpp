#pragma warning (disable : 4146)

#include <iostream>
#include <string>
#include <bit>
#include "Pieces.h"
#include "Search.h"
#include "Bits.h"
#include "Moves.h"
#include "Xoshiro256.h"
#include "Transposition table.h"
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
		DisplayBoard (playerAtStart, enpassantAtStart, fiftyMovesAtStart);

		Search ();
		cout << "\n";
	}

	/*Fen ("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");

	uint64_t pinnedPieces [64];
	uint64_t attackedSquares = 0;
	uint64_t    checkSquares = FULL_UINT;

	uint64_t enpassant = 0;

	int movesCount = 0;

	bool check = false;
	bool doubleCheck = false;
	bool reset = false;

	Move moves [250];

	fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);


	AttackedSquares (playerAtStart, opponentAtStart, attackedSquares, check, doubleCheck, checkSquares);
	PinnedPieces (playerAtStart, opponentAtStart, pinnedPieces, check, doubleCheck, checkSquares);

	GenerateMoves (playerAtStart, opponentAtStart, 0, doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);
	OrderMoves (0, 1, moves, movesCount);


	MakeMove (playerAtStart, opponentAtStart, enpassant, reset, moves [19]);

	DisplayBoard (playerAtStart, enpassant, 0);
	Bits::Display (pieces [ALL_PIECES]);


	UnmakeMove (playerAtStart, opponentAtStart, moves [19]);

	DisplayBoard (playerAtStart, enpassant, 0);
	Bits::Display (pieces [ALL_PIECES]);*/
	

	/*for (int i = 0; i < movesCount; i ++)
	{
		Move &move = moves [i];
		cout << i << " " << Coordinates (move.fromI) << Coordinates (move.toI) << "\n";
	}*/


	return 0;
}