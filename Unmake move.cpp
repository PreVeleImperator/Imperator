#include "Search.h"
#include "Pieces.h"

void UnmakeMove (bool player, bool opponent, Move &move)
{
	uint64_t fromU = move.fromU;
	uint64_t   toU = move.  toU;

	uint64_t fromTo = fromU | toU;

	int fromI = move.fromI;
	int   toI = move.  toI;

	int piece         = move.piece;
	int capturedPiece = move.capturedPiece;


	switch (move.type)
	{
		case Q_PROMOTION:
		{
			material -= materialChanges [QUEEN [player]];

			board [toI] = PAWN [player];

			pieces [PAWN  [player]] ^= toU;
			pieces [QUEEN [player]] ^= toU;

			break;
		}
		case R_PROMOTION:
		{
			material -= materialChanges [ROOK [player]];

			board [toI] = PAWN [player];

			pieces [PAWN [player]] ^= toU;
			pieces [ROOK [player]] ^= toU;

			break;
		}
		case N_PROMOTION:
		{
			material -= materialChanges [KNIGHT [player]];

			board [toI] = PAWN [player];

			pieces [PAWN   [player]] ^= toU;
			pieces [KNIGHT [player]] ^= toU;

			break;
		}
		case B_PROMOTION:
		{
			material -= materialChanges [BISHOP [player]];

			board [toI] = PAWN [player];

			pieces [PAWN   [player]] ^= toU;
			pieces [BISHOP [player]] ^= toU;

			break;
		}
	}


	board [fromI] = board [toI];
	board [  toI] = capturedPiece;

	pieces [piece          ] ^= fromTo;
	pieces [PIECES [player]] ^= fromTo;
	pieces [ALL_PIECES     ] ^= fromTo;


	if (capturedPiece != NO_PIECE)
	{
		pieces [capturedPiece    ] ^= toU;
		pieces [PIECES [opponent]] ^= toU;
		pieces [ALL_PIECES       ] ^= toU;

		material               += piecesValues       [capturedPiece];
		endgameRate [opponent] += endgameRateChanges [capturedPiece];
	}
}