#pragma warning (disable : 6262)


#include "Search.h"
#include "Pieces.h"
#include "Transposition table.h"


enum {PRINC_VAR, TRSP_TAB, PROMOTION, WINNING_CAPTURE, EQUAL_CAPTURE = 11, KILLER_MOVE_1, KILLER_MOVE_2, LOSING_CAPTURE, OTHER = 18};

constexpr int capturePreValues [6] [5] = {
	11,  7,  9,  9,  4,
	15, 11, 14, 14,  7,
	14,  9, 11, 11,  5,
	14,  9, 11, 11,  5,
	17, 15, 16, 16, 11,
	10,  6,  8,  8,  3
};

constexpr int PREVALUES_COUNT = 19;


static int PreValue (int ply, int depth, Move &move, TrspTab::Table *trspTabEntry)
{
	// principal variation
	if (depth >= 2)
	{
		auto &pv = princVar [0] [ply];

		if (move.fromI == pv [FROM]  &&  move.toI == pv [TO]  &&  move.type == pv [TYPE])
			return PRINC_VAR;
	}

	// transposition table move
	if (trspTabEntry  &&  trspTabEntry->fromI == move.fromI  &&  trspTabEntry->toI == move.toI  &&  trspTabEntry->moveType == move.type)
		return TRSP_TAB;

	// promotion
	if (move.type == Q_PROMOTION  ||  move.type == N_PROMOTION  ||  move.type == R_PROMOTION  ||  move.type == B_PROMOTION)
		return PROMOTION;

	// capturing
	if (move.capturedPiece != NO_PIECE)
		return capturePreValues [move.piece / 2] [move.capturedPiece / 2];

	// killer move 1
	if (depth >= 2  &&  ply >= 1)
	{
		auto &km = killerMoves [ply] [0];

		if (move.fromI == km [FROM]  &&  move.toI == km [TO]  &&  move.type == km [TYPE])
			return KILLER_MOVE_1;
	}

	// killer move 2
	if (depth >= 2  &&  ply >= 1)
	{
		auto &km = killerMoves [ply] [1];

		if (move.fromI == km [FROM]  &&  move.toI == km [TO]  &&  move.type == km [TYPE])
			return KILLER_MOVE_2;
	}

	// other
	return OTHER;
}

void OrderMoves (int ply, int depth, Move moves [], int movesCount, uint64_t trspTabIndex, uint64_t trspTabCode)
{
	Move orderedMoves  [PREVALUES_COUNT] [250];
	int  preValsCounts [PREVALUES_COUNT];

	TrspTab::Table *trspTabEntry = &TrspTab::table [trspTabIndex];

		
	fill (preValsCounts, preValsCounts + PREVALUES_COUNT, 0);

	if (trspTabEntry->code != trspTabCode)
		trspTabEntry = nullptr;


	for (int i = 0; i < movesCount; i ++)
	{
		Move &move     = moves [i];
		int   preValue = PreValue (ply, depth, move, trspTabEntry);
		
		orderedMoves [preValue] [preValsCounts [preValue] ++] = move;
	}

	int count = 0;

	for (int preValue = 0; preValue < PREVALUES_COUNT; preValue ++)
		for (int move = 0; move < preValsCounts [preValue]; move ++)
			moves [count ++] = orderedMoves [preValue] [move];
}