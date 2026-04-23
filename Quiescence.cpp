#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Moves.h"

int Quiescence (bool player, bool opponent, uint64_t enpassant, int ply, int alfa, int beta)
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


	if (check)
	{
		GenerateQuiescenceInCheckMoves (player, opponent, 0    , doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);
		                    OrderMoves (ply   , 0       , moves, movesCount, 0, 0);

		if (!movesCount)
			return CHECKMATE + ply;
	}
	else
	{
		int value = Evaluate (player);

		if (value >= beta) return beta;
		if (value >  alfa) alfa = value;

		GenerateQuiescenceMoves (player, opponent, 0    , pinnedPieces, attackedSquares, moves, movesCount);
		   OrderQuiescenceMoves (ply   , 0       , moves, movesCount);

		if (!movesCount)
			return value;
	}


	for (int i = 0; i < movesCount; i ++)
	{
		if (timeStop)
			return 0;

		Move     &move = moves [i];
		uint64_t  nextEnpassant;

		MakeQuiescenceMove (player, opponent, nextEnpassant, move);

		int value = -Quiescence (opponent, player, nextEnpassant, ply + 1, -beta, -alfa);

		UnmakeQuiescenceMove (player, opponent, move);

		if (value >= beta) return beta;
		if (value >  alfa) alfa = value;
	}

	return alfa;
}