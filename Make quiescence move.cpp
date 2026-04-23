#include "Search.h"
#include "Pieces.h"
#include "Moves.h"

void MakeQuiescenceMove (bool player, bool opponent, uint64_t &enpassant, Move &move)
{
	uint64_t fromU = move.fromU;
	uint64_t   toU = move.  toU;

	uint64_t fromTo = fromU | toU;

	int fromI = move.fromI;
	int   toI = move.  toI;

	int piece         = move.piece;
	int capturedPiece = move.capturedPiece;


	board [  toI] = board [fromI];
	board [fromI] = NO_PIECE;

	pieces [piece          ] ^= fromTo;
	pieces [PIECES [player]] ^= fromTo;
	pieces [ALL_PIECES     ] ^= fromTo;


	if (capturedPiece != NO_PIECE)
	{
		pieces [capturedPiece    ] ^= toU;
		pieces [PIECES [opponent]] ^= toU;
		pieces [ALL_PIECES       ] ^= toU;

		material -= piecesValues [capturedPiece];
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
		case DOUBLE_PAWN_MOVE:
		{
			enpassant = pawnMoves [opponent] [toI];
			break;
		}
	}
}