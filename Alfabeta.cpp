#include "Search.h"
#include "Pieces.h"

int Alfabeta (bool playerToMove, int ply, int depth, int alfa, int beta)
{
	if (depth <= 0)
	{
		return PositionValue (playerToMove);
	}


	uint64_t pinnedPieces [64];
	uint64_t attackedSquares = 0;
	uint64_t    checkSquares = FULL_UINT;

	int movesCount = 0;

	bool check       = false;
	bool doubleCheck = false;

	Move moves [250];


	fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);


	AttackedSquares (playerToMoveAtStart, attackedSquares, check, doubleCheck, checkSquares);
	PinnedPieces    (playerToMoveAtStart, pinnedPieces, doubleCheck);

	GenerateMoves (playerToMoveAtStart, enpassantAtStart, doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);


	for (int i = 0; i < movesCount; i ++)
	{
		Move &move = moves [i];

		MakeMove (playerToMoveAtStart, move);

		int value = -Alfabeta (!playerToMove, ply + 1, depth - 1, -beta, -alfa);

		UnmakeMove (playerToMoveAtStart, move);

		if (value > alfa)
		{
			alfa = value;
		}
	}

	return alfa;
}