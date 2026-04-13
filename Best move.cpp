#include "Search.h"
#include "Pieces.h"
#include "Bits.h"

int BestMove (Move &bestMove, int depth)
{
	uint64_t pinnedPieces [64];
	uint64_t attackedSquares = 0;
	uint64_t    checkSquares = FULL_UINT;

	int movesCount = 0;
	int bestValue  = NO_MOVE;

	bool check       = false;
	bool doubleCheck = false;

	Move moves [250];

	fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);


	AttackedSquares (playerToMoveAtStart, opponentAtStart, attackedSquares, check, doubleCheck, checkSquares);
	PinnedPieces    (playerToMoveAtStart, opponentAtStart, pinnedPieces   , check, doubleCheck, checkSquares);

	GenerateMoves (playerToMoveAtStart, opponentAtStart, enpassantAtStart, doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);


	for (int i = 0; i < movesCount; i ++)
	{
		Move &move = moves [i];

		MakeMove (playerToMoveAtStart, opponentAtStart, move);

		int value = -Alfabeta (opponentAtStart, playerToMoveAtStart, 0, 1, depth - 1, bestValue, -bestValue);

		UnmakeMove (playerToMoveAtStart, opponentAtStart, move);
		
		if (value > bestValue)
		{
			PvEntry (0, move.fromI, move.toI, move.type);

			bestValue = value;
			bestMove  = move;
		}
	}


	return bestValue;
}