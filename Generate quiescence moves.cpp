#pragma warning (disable : 4146)


#include <iostream>
#include <bit>
#include "Search.h"
#include "Pieces.h"
#include "Moves.h"
#include "Move struct.h"
#include "Bits.h"


static void PromotingPawns (bool player, bool opponent, uint64_t pawns, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	for (; pawns; pawns &= pawns - 1)
	{
		uint64_t fromU = pawns & -pawns;
		int      fromI = countr_zero (fromU);
		int      piece = PAWN [player];

		uint64_t pieceMoves  =     pawnMoves [player] [fromI] & ~pieces [ALL_PIECES];
		         pieceMoves |= pawnCaptMoves [player] [fromI] &  pieces [PIECES [opponent]];
				 pieceMoves &= pinnedPieces  [fromI ];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
			for (int type = Q_PROMOTION; type <= B_PROMOTION; type ++)
			{
				Move &move = moves [movesCount ++];

				uint64_t toU = pieceMoves & -pieceMoves;
				int      toI = countr_zero (toU);

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

static void OtherPawns (bool player, bool opponent, uint64_t pawns, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	for (; pawns; pawns &= pawns - 1)
	{
		uint64_t fromU = pawns & -pawns;
		int      fromI = countr_zero (fromU);
		int      piece = PAWN [player];

		uint64_t pieceMoves = pawnCaptMoves [player] [fromI] & pieces [PIECES [opponent]] & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			     int toI = countr_zero (toU);

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

static void Rooks (bool player, bool opponent, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t rooks = pieces [ROOK [player]];

	for (; rooks; rooks &= rooks - 1)
	{
		uint64_t fromU = rooks & -rooks;
		int      fromI = countr_zero (fromU);
		int      piece = ROOK [player];

		uint64_t pieceMoves = RookMoves (fromI) & pieces [PIECES [opponent]] & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			     int toI = countr_zero (toU);

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

static void Knights (bool player, bool opponent, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t knights = pieces [KNIGHT [player]];

	for (; knights; knights &= knights - 1)
	{
		uint64_t fromU = knights & -knights;
		int      fromI = countr_zero (fromU);
		int      piece = KNIGHT [player];

		uint64_t pieceMoves = knightMoves [fromI] & pieces [PIECES [opponent]] & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			     int toI = countr_zero (toU);

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

static void Bishops (bool player, bool opponent, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t bishops = pieces [BISHOP [player]];

	for (; bishops; bishops &= bishops - 1)
	{
		uint64_t fromU = bishops & -bishops;
		int      fromI = countr_zero (fromU);
		int      piece = BISHOP [player];

		uint64_t pieceMoves = BishopMoves (fromI) & pieces [PIECES [opponent]] & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			     int toI = countr_zero (toU);

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

static void Queens (bool player, bool opponent, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t queens = pieces [QUEEN [player]];

	for (; queens; queens &= queens - 1)
	{
		uint64_t fromU = queens & -queens;
		int      fromI = countr_zero (fromU);
		int      piece = QUEEN [player];

		uint64_t pieceMoves = (RookMoves (fromI) | BishopMoves (fromI)) & pieces [PIECES [opponent]] & pinnedPieces [fromI];

		for (; pieceMoves; pieceMoves &= pieceMoves - 1)
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = pieceMoves & -pieceMoves;
			     int toI = countr_zero (toU);

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

static void King (bool player, bool opponent, uint64_t attackedSquares, Move moves [], int &movesCount)
{
	uint64_t fromU = pieces [KING [player]];
	int      fromI = countr_zero (fromU);
	int      piece = KING [player];

	uint64_t pieceMoves = kingMoves [fromI] & pieces [PIECES [opponent]] & ~attackedSquares;

	for (; pieceMoves; pieceMoves &= pieceMoves - 1)
	{
		Move &move = moves [movesCount ++];

		uint64_t toU = pieceMoves & -pieceMoves;
		     int toI = countr_zero (toU);

		move.fromU = fromU;
		move.fromI = fromI;

		move.toU = toU;
		move.toI = toI;

		move.type          = MOVE;
		move.piece         = piece;
		move.capturedPiece = board [toI];
	}
}


void GenerateQuiescenceMoves (bool player, bool opponent, uint64_t enpassant, uint64_t pinnedPieces [], uint64_t attackedSquares, Move moves [], int &movesCount)
{
	uint64_t promotingPawns = pieces [PAWN [player]] & promotionSquares [player];
	uint64_t     otherPawns = pieces [PAWN [player]] ^ promotingPawns;

	PromotingPawns (player, opponent, promotingPawns, pinnedPieces, moves, movesCount);
		OtherPawns (player, opponent,     otherPawns, pinnedPieces, moves, movesCount);

	Rooks   (player, opponent, pinnedPieces, moves, movesCount);
	Knights (player, opponent, pinnedPieces, moves, movesCount);
	Bishops (player, opponent, pinnedPieces, moves, movesCount);
	Queens  (player, opponent, pinnedPieces, moves, movesCount);
	
	King (player, opponent, attackedSquares, moves, movesCount);
}