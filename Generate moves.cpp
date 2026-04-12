#pragma warning (disable : 4146)


#include <iostream>
#include <bit>
#include "Search.h"
#include "Pieces.h"
#include "Pieces moves.h"
#include "Move struct.h"
#include "Coordinates.h"
#include "Bits.h";


static void Pawn (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t pawns    = pieces [PAWN [playerToMove]];
	uint64_t opponent = !playerToMove;

	for (; pawns; pawns &= pawns - 1)
	{
		uint64_t fromU = pawns & -pawns;
		int      fromI = countr_zero (fromU);
		int      piece = PAWN [playerToMove];

		uint64_t pieceMoves  =     pawnMoves [playerToMove] [fromI] & ~pieces [ALL_PIECES];
		         pieceMoves |= pawnCaptMoves [playerToMove] [fromI] &  pieces [PIECES [opponent]];
				 pieceMoves &= checkSquares & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			uint64_t toI = countr_zero (toU);

			move.fromU = fromU;
			move.fromI = fromI;

			move.toU = toU;
			move.toI = toI;

			move.type          = PAWN_MOVE;
			move.piece         = piece;
			move.capturedPiece = board [toI];
		}
	}
}

static void Rook (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t rooks = pieces [ROOK [playerToMove]];

	for (; rooks; rooks &= rooks - 1)
	{
		uint64_t fromU = rooks & -rooks;
		int      fromI = countr_zero (fromU);
		int      piece = ROOK [playerToMove];
		int      type;

		uint64_t pieceMoves = (RookMoves (fromI) & ~pieces [PIECES [playerToMove]]) & checkSquares & pinnedPieces [fromI];


		if (!qRookMoved [playerToMove]  &&  fromU & 0x100000000000001)
		{
			type = FIRST_Q_ROOK_MOVE;
		}
		else if (!kRookMoved [playerToMove]  &&  fromU & 0x8000000000000080)
		{
			type = FIRST_K_ROOK_MOVE;
		}
		else
		{
			type = MOVE;
		}


		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			uint64_t toI = countr_zero (toU);

			move.fromU = fromU;
			move.fromI = fromI;

			move.toU = toU;
			move.toI = toI;

			move.type          = type;
			move.piece         = piece;
			move.capturedPiece = board [toI];
		}
	}
}

static void Knight (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t knights = pieces [KNIGHT [playerToMove]];

	for (; knights; knights &= knights - 1)
	{
		uint64_t fromU = knights & -knights;
		int      fromI = countr_zero (fromU);
		int      piece = KNIGHT [playerToMove];

		uint64_t pieceMoves = (knightMoves [fromI] & ~pieces [PIECES [playerToMove]]) & checkSquares & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			uint64_t toI = countr_zero (toU);

			move.fromU = fromU;
			move.fromI = fromI;

			move.toU = toU;
			move.toI = toI;

			move.type          = MOVE;
			move.piece         = piece;
			move.capturedPiece = board [toI];
		}
	}
}

static void Bishop (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t bishops = pieces [BISHOP [playerToMove]];

	for (; bishops; bishops &= bishops - 1)
	{
		uint64_t fromU = bishops & -bishops;
		int      fromI = countr_zero (fromU);
		int      piece = BISHOP [playerToMove];

		uint64_t pieceMoves = (BishopMoves (fromI) & ~pieces [PIECES [playerToMove]]) & checkSquares & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			uint64_t toI = countr_zero (toU);

			move.fromU = fromU;
			move.fromI = fromI;

			move.toU = toU;
			move.toI = toI;

			move.type          = MOVE;
			move.piece         = piece;
			move.capturedPiece = board [toI];
		}
	}
}

static void Queen (bool playerToMove, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t queens = pieces [QUEEN [playerToMove]];

	for (; queens; queens &= queens - 1)
	{
		uint64_t fromU = queens & -queens;
		int      fromI = countr_zero (fromU);
		int      piece = QUEEN [playerToMove];

		uint64_t pieceMoves = ((RookMoves (fromI) | BishopMoves (fromI)) & ~pieces [PIECES [playerToMove]]) & checkSquares & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			uint64_t toI = countr_zero (toU);

			move.fromU = fromU;
			move.fromI = fromI;

			move.toU = toU;
			move.toI = toI;

			move.type          = MOVE;
			move.piece         = piece;
			move.capturedPiece = board [toI];
		}
	}
}

static void King (bool playerToMove, uint64_t attackedSquares, Move moves [], int &movesCount)
{
	uint64_t fromU = pieces [KING [playerToMove]];
	int      fromI = countr_zero (fromU);
	int      piece = KING [playerToMove];

	uint64_t pieceMoves = (kingMoves [fromI] & ~pieces [PIECES [playerToMove]]) & ~attackedSquares;

	for (; pieceMoves; pieceMoves &= pieceMoves - 1)
	{
		Move &move = moves [movesCount ++];

		uint64_t toU = pieceMoves & -pieceMoves;
		uint64_t toI = countr_zero (toU);

		move.fromU = fromU;
		move.fromI = fromI;

		move.toU = toU;
		move.toI = toI;

		move.type          = kingMoved [playerToMove] ? MOVE : FIRST_KING_MOVE;
		move.piece         = piece;
		move.capturedPiece = board [toI];
	}
}


void GenerateMoves (bool playerToMove, uint64_t enpassant, bool doubleCheck, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move moves [], int &movesCount)
{
	if (!doubleCheck)
	{
		Pawn   (playerToMove, checkSquares, pinnedPieces, moves, movesCount);
		Rook   (playerToMove, checkSquares, pinnedPieces, moves, movesCount);
		Knight (playerToMove, checkSquares, pinnedPieces, moves, movesCount);
		Bishop (playerToMove, checkSquares, pinnedPieces, moves, movesCount);
		Queen  (playerToMove, checkSquares, pinnedPieces, moves, movesCount);
	}

	King (playerToMove, attackedSquares, moves, movesCount);
}