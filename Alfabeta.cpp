#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Pieces moves.h"

int Alfabeta (bool player, bool opponent, uint64_t enpassant, int ply, int depth, int alfa, int beta)
{
	if (GetTickCount64 () - timeStart >= timeLimit)
	{
		timeStop = true;
		return 0;
	}


	uint64_t pinnedPieces [64];
	uint64_t attackedSquares = 0;
	uint64_t    checkSquares = FULL_UINT;

	int movesCount = 0;

	bool check       = false;
	bool doubleCheck = false;

	Move moves [250];

	fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);


	AttackedSquares (player, opponent, attackedSquares, check, doubleCheck, checkSquares);
	PinnedPieces    (player, opponent, pinnedPieces   , check, doubleCheck, checkSquares);

	GenerateMoves (player, opponent, enpassant, doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);
	OrderMoves    (ply   , depth   , moves    , movesCount);


	// nullmoves
	if (depth >= 4  &&  !check  &&  endgameRate [player])
	{
		int value = -Alfabeta (opponent, player, 0, ply + 1, depth / 3, -beta, 1 - beta);

		if (value >= beta)
			return beta;
	}

	// game end
	if (int value = GameEnd (ply, check, movesCount); value != NO_END)
	{
		pvLength [ply] = ply;
		return value;
	}

	// search end
	if (depth <= 0)
	{
		pvLength [ply] = ply;
		return Evaluate (player);
	}


	for (int i = 0; i < movesCount; i ++)
	{
		if (timeStop)
			return 0;

		Move &move = moves [i];

		MakeMove (player, opponent, move);
		
		int nextDepth = check ? depth : depth - 1;
		int value     = -Alfabeta (opponent, player, 0, ply + 1, nextDepth, -beta, -alfa);

		UnmakeMove (player, opponent, move);

		if (value >= beta)
		{
			KillerMovesEntry (ply, move);
			return beta;
		}

		if (value > alfa)
		{
			PrincipalVariationEntry (ply, move);
			alfa = value;
		}
	}


	return alfa;
}