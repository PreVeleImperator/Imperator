#include "Search.h"
#include "Pieces.h"

void BestMove (Move &bestMove, int &bestValue, int depth)
{
	uint64_t pinnedPieces [64];
	uint64_t attackedSquares = 0;
	uint64_t    checkSquares = FULL_UINT;

	int movesCount = 0;

	bool check       = false;
	bool doubleCheck = false;

	Move moves [250];


	bestValue = NO_MOVE;
	fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);


	AttackedSquares (playerToMoveAtStart, attackedSquares, check, doubleCheck, checkSquares);
	PinnedPieces    (playerToMoveAtStart, pinnedPieces, doubleCheck);

	GenerateMoves (playerToMoveAtStart, enpassantAtStart, doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);


	for (int i = 0; i < movesCount; i ++)
	{
		Move &move = moves [i];

		MakeMove (playerToMoveAtStart, move);

		int value = -Alfabeta (!playerToMoveAtStart, 1, depth - 1, NO_MOVE, -NO_MOVE);

		UnmakeMove (playerToMoveAtStart, move);

		if (value > bestValue)
		{
			bestValue = value;
			bestMove  = move;
		}
	}
}