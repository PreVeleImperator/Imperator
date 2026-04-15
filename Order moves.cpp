#pragma warning (disable : 6262)


#include "Search.h"
#include "Pieces.h"


/*
0) principalVariation
1) hash move
2) promotions
3) winning captures
4) equal captures
5) killer moves
6) losing captures
7) quiet moves
*/


static int PreValue (int ply, int depth, Move &move)
{
	// principal variation
	if (depth >= 2)
	{
		auto &pv = principalVariation [0] [ply];

		if (move.fromI == pv [FROM]  &&  move.toI == pv [TO]  &&  move.type == pv [TYPE])
			return PREVALUE_PV;
	}

	// promotion
	if (move.type == Q_PROMOTION  ||  move.type == N_PROMOTION  ||  move.type == R_PROMOTION  ||  move.type == B_PROMOTION)
		return PREVALUE_PROMOTION;

	// capturing
	if (move.capturedPiece != NO_PIECE)
		return capturePreValues [move.piece / 2] [move.capturedPiece / 2];

	// killer move 1
	if (depth >= 2  &&  ply >= 1)
	{
		auto &km = killerMoves [ply] [0];

		if (move.fromI == km [FROM]  &&  move.toI == km [TO]  &&  move.type == km [TYPE])
			return PREVALUE_KILLER1;
	}

	// killer move 2
	if (depth >= 2  &&  ply >= 1)
	{
		auto &km = killerMoves [ply] [1];

		if (move.fromI == km [FROM]  &&  move.toI == km [TO]  &&  move.type == km [TYPE])
			return PREVALUE_KILLER2;
	}

	// other
	return PREVALUE_OTHER;
}

void OrderMoves (int ply, int depth, Move moves [], int movesCount)
{
	Move orderedMoves  [PREVALUES_COUNT] [250];
	int  preValsCounts [PREVALUES_COUNT];

	fill (preValsCounts, preValsCounts + PREVALUES_COUNT, 0);

	for (int i = 0; i < movesCount; i ++)
	{
		Move &move         = moves [i];
		int   preValue     = PreValue (ply, depth, move);
		int  &preValsCount = preValsCounts [preValue];
		
		orderedMoves [preValue] [preValsCount ++] = move;
	}

	int count = 0;

	for (int preValue = 0; preValue < PREVALUES_COUNT; preValue ++)
		for (int move = 0; move < preValsCounts [preValue]; move ++)
			moves [count ++] = orderedMoves [preValue] [move];
}