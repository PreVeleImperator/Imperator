#pragma warning (disable : 6262)


#include "Search.h"
#include "Pieces.h"


enum {PROMOTION, WINNING_CAPTURE, EQUAL_CAPTURE = 9, LOSING_CAPTURE};

constexpr int capturePreValues [6] [5] = {
	 9,  5,  7,  7, 2,
	11,  9, 10, 10, 5,
	10,  7,  9,  9, 3,
	10,  7,  9,  9, 3,
	13, 11, 12, 12, 9,
	 8,  4,  6,  6, 1
};

constexpr int PREVALUES_COUNT = 14;


static int PreValue (int ply, int depth, Move &move)
{
	// promotion
	if (move.type == Q_PROMOTION  ||  move.type == N_PROMOTION  ||  move.type == R_PROMOTION  ||  move.type == B_PROMOTION)
		return PROMOTION;

	// capturing
	return capturePreValues [move.piece / 2] [move.capturedPiece / 2];
}

void OrderQuiescenceMoves (int ply, int depth, Move moves [], int movesCount)
{
	Move orderedMoves  [PREVALUES_COUNT] [250];
	int  preValsCounts [PREVALUES_COUNT];

	fill (preValsCounts, preValsCounts + PREVALUES_COUNT, 0);

	for (int i = 0; i < movesCount; i ++)
	{
		Move &move     = moves [i];
		int   preValue = PreValue (ply, depth, move);
		
		orderedMoves [preValue] [preValsCounts [preValue] ++] = move;
	}

	int count = 0;

	for (int preValue = 0; preValue < PREVALUES_COUNT; preValue ++)
		for (int move = 0; move < preValsCounts [preValue]; move ++)
			moves [count ++] = orderedMoves [preValue] [move];
}