#pragma warning (disable : 4146)


#include <bit>
#include "Search.h"
#include "Pieces.h"
#include "Pieces moves.h"
#include "Bits.h"


static void NonSlidingPieces (uint64_t pieces, const uint64_t moves [], const uint64_t myKing, uint64_t &attackedSquares, bool &check, uint64_t &checkSquares)
{
	for (; pieces; pieces &= pieces - 1)
	{
		uint64_t piece   = pieces & -pieces;
		uint64_t squares = moves [countr_zero (piece)];

		attackedSquares |= squares;

		if (squares & myKing)
		{
			check        = true;
			checkSquares = piece;
		}
	}
}

static void SlidingPieces (uint64_t pieces, uint64_t Moves (int square, uint64_t pieceException), const uint64_t combinations [], const int offsets [], const uint64_t myKing, uint64_t &attackedSquares, 
						   bool &check, bool &doubleCheck, uint64_t &checkSquares)
{
	for (; pieces; pieces &= pieces - 1)
	{
		uint64_t piece   = pieces & -pieces;
		uint64_t squares = Moves (countr_zero (piece), myKing);

		attackedSquares |= squares;

		if (squares & myKing)
		{
			if (check)
			{
				doubleCheck = true;
				return;
			}

			check        = true; 
			checkSquares = (Moves (countr_zero (piece), 0) & combinations [offsets [countr_zero (myKing)]]) | piece;
		}
	}
}


void AttackedSquares (bool playerToMove, uint64_t &attackedSquares, bool &check, bool &doubleCheck, uint64_t &checkSquares)
{
	uint64_t opponent = !playerToMove;
	uint64_t myKing   = pieces [KING [playerToMove]];

	NonSlidingPieces (pieces [PAWN   [opponent]], pawnCaptMoves [opponent], myKing, attackedSquares, check, checkSquares);
	NonSlidingPieces (pieces [KNIGHT [opponent]], knightMoves             , myKing, attackedSquares, check, checkSquares);
	NonSlidingPieces (pieces [KING   [opponent]],   kingMoves             , myKing, attackedSquares, check, checkSquares);

	SlidingPieces (pieces [ROOK   [opponent]] | pieces [QUEEN [opponent]],   RookMoves,   rookCombinations,   rookOffsets, myKing, attackedSquares, check, doubleCheck, checkSquares);
	SlidingPieces (pieces [BISHOP [opponent]] | pieces [QUEEN [opponent]], BishopMoves, bishopCombinations, bishopOffsets, myKing, attackedSquares, check, doubleCheck, checkSquares);
}