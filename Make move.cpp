#include "Search.h"
#include "Pieces.h"
#include "Moves.h"
#include "Castlings.h"

void MakeMove (bool player, bool opponent, uint64_t &enpassant, bool &resetFiftyMoves, Move &move)
{
	uint64_t fromU = move.fromU;
	uint64_t   toU = move.  toU;

	uint64_t fromTo = fromU | toU;

	int fromI = move.fromI;
	int   toI = move.  toI;

	int         piece = move.        piece;
	int capturedPiece = move.capturedPiece;


	board [  toI] = piece;
	board [fromI] = NO_PIECE;

	pieces [piece          ] ^= fromTo;
	pieces [PIECES [player]] ^= fromTo;
	pieces [ALL_PIECES     ] ^= fromTo;


	if (capturedPiece != NO_PIECE)
	{
		pieces [capturedPiece    ] ^= toU;
		pieces [PIECES [opponent]] ^= toU;
		pieces [ALL_PIECES       ] ^= toU;

		material               -= piecesValues       [capturedPiece];
		endgameRate [opponent] -= endgameRateChanges [capturedPiece];

		resetFiftyMoves = true;
	}


	switch (move.type)
	{
		case Q_PROMOTION:
		{
			material += promotionMaterialChanges [QUEEN [player]];

			board [toI] = QUEEN [player];

			pieces [PAWN  [player]] ^= toU;
			pieces [QUEEN [player]] ^= toU;

			break;
		}
		case R_PROMOTION:
		{
			material += promotionMaterialChanges [ROOK [player]];

			board [toI] = ROOK [player];

			pieces [PAWN [player]] ^= toU;
			pieces [ROOK [player]] ^= toU;

			break;
		}
		case N_PROMOTION:
		{
			material += promotionMaterialChanges [KNIGHT [player]];

			board [toI] = KNIGHT [player];

			pieces [PAWN   [player]] ^= toU;
			pieces [KNIGHT [player]] ^= toU;

			break;
		}
		case B_PROMOTION:
		{
			material += promotionMaterialChanges [BISHOP [player]];

			board [toI] = BISHOP [player];

			pieces [PAWN   [player]] ^= toU;
			pieces [BISHOP [player]] ^= toU;

			break;
		}
		case PAWN_MOVE:
		{
			resetFiftyMoves = true;
			break;
		}
		case DOUBLE_PAWN_MOVE:
		{
			enpassant       = pawnMoves [opponent] [toI];
			resetFiftyMoves = true;
			break;
		}
		case FIRST_KING_MOVE:
		{
			kingMoved [player] = true;
			break;
		}
		case FIRST_K_ROOK_MOVE:
		{
			kRookMoved [player] = true;
			break;
		}
		case FIRST_Q_ROOK_MOVE:
		{
			qRookMoved [player] = true;
			break;
		}
		case K_CASTLING:
		{
			pieces [ROOK   [player]] ^= KCastling::RookMoveU [player];
			pieces [PIECES [player]] ^= KCastling::RookMoveU [player];
			pieces [ALL_PIECES     ] ^= KCastling::RookMoveU [player];

			board [KCastling::RookFromI [player]] = NO_PIECE;
			board [KCastling::RookToI   [player]] = ROOK [player];

			kingMoved [player] = kRookMoved [player] = true;
			break;
		}
		case Q_CASTLING:
		{
			pieces [ROOK   [player]] ^= QCastling::RookMoveU [player];
			pieces [PIECES [player]] ^= QCastling::RookMoveU [player];
			pieces [ALL_PIECES     ] ^= QCastling::RookMoveU [player];

			board [QCastling::RookFromI [player]] = NO_PIECE;
			board [QCastling::RookToI   [player]] = ROOK [player];

			kingMoved [player] = qRookMoved [player] = true;
			break;
		}
	}
}