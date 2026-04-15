#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Bits.h"

int BestMove (int depth)
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
	OrderMoves    (0, depth, moves, movesCount);


	for (int i = 0; i < movesCount; i ++)
	{
		if (timeStop)
			return 0;

		Move &move = moves [i];

		MakeMove (playerToMoveAtStart, opponentAtStart, move);

		int nextDepth = check ? depth : depth - 1;
		int value     = -Alfabeta (opponentAtStart, playerToMoveAtStart, 0, 1, nextDepth, NO_MOVE, -bestValue);

		UnmakeMove (playerToMoveAtStart, opponentAtStart, move);
		
		if (value > bestValue)
		{
			PrincipalVariationEntry (0, move);
			bestValue = value;
		}
	}


	return bestValue;
}