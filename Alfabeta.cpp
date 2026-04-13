#include "Search.h"
#include "Pieces.h"

int Alfabeta (bool player, bool opponent, uint64_t enpassant, int ply, int depth, int alfa, int beta)
{
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


	if (int value = GameEnd (ply, check, movesCount); value != NO_END)
	{
		pvLength [ply] = ply;
		return value;
	}

	if (depth <= 0)
	{
		pvLength [ply] = ply;
		return Evaluate (player);
	}


	for (int i = 0; i < movesCount; i ++)
	{
		Move &move = moves [i];

		MakeMove (player, opponent, move);

		int value = -Alfabeta (opponent, player, 0, ply + 1, depth - 1, NO_MOVE, -alfa);

		UnmakeMove (player, opponent, move);

		if (value > alfa)
		{
			PvEntry (ply, move.fromI, move.toI, move.type);
			alfa = value;
		}
	}


	return alfa;
}