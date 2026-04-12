#pragma warning (disable : 4146)

#include <bit>
#include "Bits.h"
#include "Search.h"
#include "Pieces.h"
#include "Pieces moves.h"

static void Piece (uint64_t myKingU, uint64_t myPieces, uint64_t evilPieces, uint64_t pinnedPieces [], const uint64_t combinations [], const int offsets [], uint64_t Moves (int square), 
				   uint64_t Moves2 (int square, uint64_t PieceException))
{
	int      myKingI         = countr_zero (myKingU);
	uint64_t myKingMove      = Moves       (myKingI);
	uint64_t relevEvilPieces = evilPieces & myKingMove;

	myPieces &= myKingMove;	

	for (; myPieces; myPieces &= myPieces - 1)
	{
		uint64_t myPieceU    = myPieces & -myPieces;
		int      myPieceI    = countr_zero (myPieceU);
		uint64_t myKingMove2 = Moves2 (myKingI, myPieceU); 
		uint64_t evilPiece   = (evilPieces & myKingMove2) ^ relevEvilPieces;
		
		if (evilPiece)
			pinnedPieces [myPieceI] = (combinations [offsets [myPieceI]] & myKingMove2) | evilPiece;
	}
}

void PinnedPieces (bool playerToMove, uint64_t pinnedPieces [], bool doubleCheck)
{
	if (doubleCheck)
		return;

	bool opponent = !playerToMove;

	uint64_t myKing   = pieces [KING   [playerToMove]];
	uint64_t myPieces = pieces [PIECES [playerToMove]];

	Piece (myKing, myPieces, pieces [ROOK   [opponent]] | pieces [QUEEN [opponent]], pinnedPieces,   rookCombinations,   rookOffsets,   RookMoves,   RookMoves);
	Piece (myKing, myPieces, pieces [BISHOP [opponent]] | pieces [QUEEN [opponent]], pinnedPieces, bishopCombinations, bishopOffsets, BishopMoves, BishopMoves);
}