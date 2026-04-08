#pragma warning (disable : 4146)

#include <iostream>
#include <bit>
#include "Search.h"
#include "Pieces.h"
#include "Pieces moves.h"
#include "Move struct.h"
#include "Coordinates.h"
#include "Bits.h";


static void AddMove (uint64_t fromU, int fromI, uint64_t toU, int toI, int type, int piece, Move &move)
{
	move.fromU = fromU;
	move.fromI = fromI;

	move.toU = toU;
	move.toI = toI;

	move.type          = type;
	move.piece         = piece;
	move.capturedPiece = board [toI];
}


static void Pawn (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move &move)
{
	uint64_t pawns = pieces [PAWN [playerToMove]];

	for (; pawns; pawns &= pawns - 1)
	{
		uint64_t fromU = pawns & -pawns;
		int      fromI = countr_zero (fromU);

		uint64_t moves = (pawnMoves [playerToMove] [fromI] & ~pieces [ALL_PIECES]) | (pawnCaptMoves [playerToMove] [fromI] & pieces [PIECES [!playerToMove]]);

		cout << Coordinates (fromI) << "\n";
		Bits::Display (moves);
	}
}

static void Rook (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move &move)
{
	uint64_t rooks = pieces [ROOK [playerToMove]];

	for (; rooks; rooks &= rooks - 1)
	{
		uint64_t fromU = rooks & -rooks;
		int      fromI = countr_zero (fromU);

		uint64_t moves = RookMoves (fromI) & ~pieces [PIECES [playerToMove]];

		cout << Coordinates (fromI) << "\n";
		Bits::Display (moves);
	}
}

static void Knight (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move &move)
{
	uint64_t knights = pieces [KNIGHT [playerToMove]];

	for (; knights; knights &= knights - 1)
	{
		uint64_t fromU = knights & -knights;
		int      fromI = countr_zero (fromU);

		uint64_t moves = knightMoves [fromI] & ~pieces [PIECES [playerToMove]];

		cout << Coordinates (fromI) << "\n";
		Bits::Display (moves);
	}
}

static void Bishop (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move &move)
{
	uint64_t bishops = pieces [BISHOP [playerToMove]];

	for (; bishops; bishops &= bishops - 1)
	{
		uint64_t fromU = bishops & -bishops;
		int      fromI = countr_zero (fromU);

		uint64_t moves = BishopMoves (fromI) & ~pieces [PIECES [playerToMove]];

		cout << Coordinates (fromI) << "\n";
		Bits::Display (moves);
	}
}

static void Queen (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move &move)
{
	uint64_t queens = pieces [QUEEN [playerToMove]];

	for (; queens; queens &= queens - 1)
	{
		uint64_t fromU = queens & -queens;
		int      fromI = countr_zero (fromU);

		uint64_t moves = (RookMoves (fromI) | BishopMoves (fromI)) & ~pieces [PIECES [playerToMove]];

		cout << Coordinates (fromI) << "\n";
		Bits::Display (moves);
	}
}

static void King (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move &move)
{
	uint64_t fromU = pieces [KING [playerToMove]];
	int      fromI = countr_zero (fromU);

	if (!fromU)
		return;

	uint64_t moves = kingMoves [fromI] & ~pieces [PIECES [playerToMove]];

	cout << Coordinates (fromI) << "\n";
	Bits::Display (moves);
}


void GenerateMoves (bool playerToMove, uint64_t enpassant, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, int &movesCount, Move moves [])
{
	Pawn   (playerToMove, checkSquares, pinnedPieces, attackedSquares, moves [movesCount ++]);
	Rook   (playerToMove, checkSquares, pinnedPieces, attackedSquares, moves [movesCount ++]);
	Knight (playerToMove, checkSquares, pinnedPieces, attackedSquares, moves [movesCount ++]);
	Bishop (playerToMove, checkSquares, pinnedPieces, attackedSquares, moves [movesCount ++]);
	Queen  (playerToMove, checkSquares, pinnedPieces, attackedSquares, moves [movesCount ++]);
	King   (playerToMove, checkSquares, pinnedPieces, attackedSquares, moves [movesCount ++]);
}