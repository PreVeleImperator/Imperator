#pragma warning (disable : 4146)

#include <bit>
#include "Bits.h"
#include "Search.h"
#include "Pieces.h"
#include "Moves.h"

static void Piece (uint64_t myKingU, uint64_t myPieces, uint64_t evilPieces, uint64_t pinnedPieces [], bool &check, bool &doubleCheck, uint64_t &checkSquares, 
				   const uint64_t combinations [], const int offsets [], uint64_t Moves1 (int square), uint64_t Moves2 (int square, uint64_t PieceException))
{
	int      myKingI            = countr_zero (myKingU);
	uint64_t myKingMove         = Moves1      (myKingI);
	uint64_t checkingEvilPieces = evilPieces & myKingMove;


	// double check
	if ((check  &&  checkingEvilPieces)  ||  popcount (checkingEvilPieces) == 2)
	{
		doubleCheck = true;
		return;
	}


	// check by sliding piece
	if (checkingEvilPieces)
	{
		check        = true;
		checkSquares = (myKingMove & Moves1 (countr_zero (checkingEvilPieces))) | checkingEvilPieces;
	}


	// pinned pieces
	myPieces &= myKingMove;	

	for (; myPieces; myPieces &= myPieces - 1)
	{
		uint64_t myPieceU    = myPieces & -myPieces;
		int      myPieceI    = countr_zero (myPieceU);
		uint64_t myKingMove2 = Moves2 (myKingI, myPieceU); 
		uint64_t evilPiece   = (evilPieces & myKingMove2) ^ checkingEvilPieces;
		
		if (evilPiece)
			pinnedPieces [myPieceI] = (combinations [offsets [myPieceI]] & myKingMove2) | evilPiece;
	}
}

void PinnedPieces (bool player, bool opponent, uint64_t pinnedPieces [], bool &check, bool &doubleCheck, uint64_t &checkSquares)
{
	uint64_t myKing   = pieces [KING   [player]];
	uint64_t myPieces = pieces [PIECES [player]];

	uint64_t   rookQueen = pieces [ROOK   [opponent]] | pieces [QUEEN [opponent]];
	uint64_t bishopQueen = pieces [BISHOP [opponent]] | pieces [QUEEN [opponent]];

	Piece (myKing, myPieces, rookQueen, pinnedPieces, check, doubleCheck, checkSquares, rookCombinations, rookOffsets, RookMoves, RookMoves);

	if (doubleCheck)
		return;

	Piece (myKing, myPieces, bishopQueen, pinnedPieces, check, doubleCheck, checkSquares, bishopCombinations, bishopOffsets, BishopMoves, BishopMoves);
}