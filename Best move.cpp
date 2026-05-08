#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Transposition table.h"

int BestMove (int depth)
{
	uint64_t pinnedPieces [64]; fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);

	uint64_t attackedSquares = 0;
	uint64_t    checkSquares = FULL_UINT;
	uint64_t trspTabIndex    = actualPath [0] & (TrspTab::SIZE - 1ULL);

	int movesCount = 0;
	int bestValue  = NO_MOVE;

	bool check       = false;
	bool doubleCheck = false;

	Move moves [250];


	AttackedSquares (playerAtStart, opponentAtStart, attackedSquares, check, doubleCheck, checkSquares);
	PinnedPieces    (playerAtStart, opponentAtStart, pinnedPieces   , check, doubleCheck, checkSquares);

	GenerateMoves (playerAtStart, opponentAtStart, enpassantAtStart, doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);
	OrderMoves    (0, depth, moves, movesCount, trspTabIndex);


	for (int i = 0; i < movesCount; i ++)
	{
		if (stopSearch)
			return 0;

		Move     &move            = moves [i];
		bool      resetFiftyMoves = false;
		uint64_t  nextEnpassant;

		MakeMove (playerAtStart, opponentAtStart, nextEnpassant, resetFiftyMoves, move);

		int nextDepth      = check           ? depth : depth             - 1;
		int nextFiftyMoves = resetFiftyMoves ? 0     : fiftyMovesAtStart + 1;

		int value = -Alphabeta (opponentAtStart, playerAtStart, nextEnpassant, nextFiftyMoves, 1, nextDepth, NO_MOVE, -bestValue, true);

		UnmakeMove (playerAtStart, opponentAtStart, move);
		
		if (value > bestValue)
		{
			PrincVarEntry (0, move);
			bestValue = value;
		}
	}


	TrspTab::Entry (trspTabIndex, actualPath [0], bestValue, TrspTab::PV_NODE, 0, depth, princVar [0] [0] [FROM], princVar [0] [0] [TO], princVar [0] [0] [TYPE]);


	return bestValue;
}