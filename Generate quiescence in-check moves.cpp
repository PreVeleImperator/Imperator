#pragma warning (disable : 4146)


#include <iostream>
#include <bit>
#include "Search.h"
#include "Pieces.h"
#include "Moves.h"
#include "Move struct.h"
#include "Bits.h"


static void DoubleMovingPawns (bool player, uint64_t pawns, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	for (; pawns; pawns &= pawns - 1)
	{
		uint64_t fromU = pawns & -pawns;
		int      fromI = countr_zero (fromU);
		int      piece = PAWN [player];

		if (pawnMoves [player] [fromI] & ~pieces [ALL_PIECES] && doublePawnMoves [fromI] & ~pieces [ALL_PIECES] & checkSquares & pinnedPieces [fromI])
		{
			Move &move = moves [movesCount ++];

			uint64_t toU = doublePawnMoves [fromI];
			int toI = countr_zero (toU);

			move.fromU = fromU;
			move.fromI = fromI;

			move.toU = toU;
			move.toI = toI;

			move.type = DOUBLE_PAWN_MOVE;
			move.piece = piece;
			move.capturedPiece = NO_PIECE;
		}
	}
}

static void PromotingPawns (bool player, bool opponent, uint64_t pawns, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	for (; pawns; pawns &= pawns - 1)
	{
		uint64_t fromU = pawns & -pawns;
		int      fromI = countr_zero (fromU);
		int      piece = PAWN [player];

		uint64_t pieceMoves  =     pawnMoves [player] [fromI] & ~pieces [ALL_PIECES];
		         pieceMoves |= pawnCaptMoves [player] [fromI] &  pieces [PIECES [opponent]];
				 pieceMoves &= checkSquares & pinnedPieces [fromI];

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

static void OtherPawns (bool player, bool opponent, uint64_t pawns, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	for (; pawns; pawns &= pawns - 1)
	{
		uint64_t fromU = pawns & -pawns;
		int      fromI = countr_zero (fromU);
		int      piece = PAWN [player];

		uint64_t pieceMoves  =     pawnMoves [player] [fromI] & ~pieces [ALL_PIECES];
		         pieceMoves |= pawnCaptMoves [player] [fromI] &  pieces [PIECES [opponent]];
				 pieceMoves &= checkSquares & pinnedPieces [fromI];

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

static void Rooks (bool player, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t rooks = pieces [ROOK [player]];

	for (; rooks; rooks &= rooks - 1)
	{
		uint64_t fromU = rooks & -rooks;
		int      fromI = countr_zero (fromU);
		int      piece = ROOK [player];

		uint64_t pieceMoves = RookMoves (fromI) & ~pieces [PIECES [player]] & checkSquares & pinnedPieces [fromI];

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

static void Knights (bool player, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t knights = pieces [KNIGHT [player]];

	for (; knights; knights &= knights - 1)
	{
		uint64_t fromU = knights & -knights;
		int      fromI = countr_zero (fromU);
		int      piece = KNIGHT [player];

		uint64_t pieceMoves = knightMoves [fromI] & ~pieces [PIECES [player]] & checkSquares & pinnedPieces [fromI];

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

static void Bishops (bool player, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t bishops = pieces [BISHOP [player]];

	for (; bishops; bishops &= bishops - 1)
	{
		uint64_t fromU = bishops & -bishops;
		int      fromI = countr_zero (fromU);
		int      piece = BISHOP [player];

		uint64_t pieceMoves = BishopMoves (fromI) & ~pieces [PIECES [player]] & checkSquares & pinnedPieces [fromI];

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

static void Queens (bool player, uint64_t checkSquares, uint64_t pinnedPieces [], Move moves [], int &movesCount)
{
	uint64_t queens = pieces [QUEEN [player]];

	for (; queens; queens &= queens - 1)
	{
		uint64_t fromU = queens & -queens;
		int      fromI = countr_zero (fromU);
		int      piece = QUEEN [player];

		uint64_t pieceMoves = (RookMoves (fromI) | BishopMoves (fromI)) & ~pieces [PIECES [player]] & checkSquares & pinnedPieces [fromI];

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

static void King (bool player, uint64_t attackedSquares, Move moves [], int &movesCount)
{
	uint64_t fromU = pieces [KING [player]];
	int      fromI = countr_zero (fromU);
	int      piece = KING [player];

	uint64_t pieceMoves = kingMoves [fromI] & ~pieces [PIECES [player]] & ~attackedSquares;

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


void GenerateQuiescenceInCheckMoves (bool player, bool opponent, uint64_t enpassant, bool doubleCheck, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, 
									 Move moves [], int &movesCount)
{
	if (!doubleCheck)
	{
		uint64_t    promotingPawns = pieces [PAWN [player]] &       promotionSquares [player];
		uint64_t doubleMovingPawns = pieces [PAWN [player]] &  doublePawnMoveSquares [player];
		uint64_t nonPromotingPawns = pieces [PAWN [player]] & ~promotingPawns;

		   PromotingPawns (player, opponent,    promotingPawns, checkSquares, pinnedPieces, moves, movesCount);
		DoubleMovingPawns (player,           doubleMovingPawns, checkSquares, pinnedPieces, moves, movesCount);
		       OtherPawns (player, opponent,        nonPromotingPawns, checkSquares, pinnedPieces, moves, movesCount);

		Rooks   (player, checkSquares, pinnedPieces, moves, movesCount);
		Knights (player, checkSquares, pinnedPieces, moves, movesCount);
		Bishops (player, checkSquares, pinnedPieces, moves, movesCount);
		Queens  (player, checkSquares, pinnedPieces, moves, movesCount);
	}

	King (player, attackedSquares, moves, movesCount);
}