#include <iostream>
#include "Search.h"
#include "Pieces.h"

void Search::GenerateMoves (bool toMove, uint64_t enpassant, bool &check, bool &doubleCheck)
{
	uint64_t pawns   = pieces [PAWN   [toMove]];
	uint64_t rooks   = pieces [ROOK   [toMove]];
	uint64_t knights = pieces [KNIGHT [toMove]];
	uint64_t bishops = pieces [BISHOP [toMove]];
	uint64_t queens  = pieces [QUEEN  [toMove]];

	for (; rooks; rooks &= rooks - 1)
	{

	}
}