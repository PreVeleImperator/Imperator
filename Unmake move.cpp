#include "Search.h"
#include "Pieces.h"

void UnmakeMove (bool playerToMove, Move &move)
{
	bool opponent = !playerToMove;

	uint64_t fromU = move.fromU;
	uint64_t   toU = move.  toU;

	uint64_t fromTo = fromU | toU;

	int fromI = move.fromI;
	int   toI = move.  toI;

	int piece         = move.piece;
	int capturedPiece = move.capturedPiece;


	board [fromI] = board [toI];
	board [  toI] = capturedPiece;

	pieces [piece                ] ^= fromTo;
	pieces [PIECES [playerToMove]] ^= fromTo;
	pieces [ALL_PIECES           ] ^= fromTo;


	if (capturedPiece != NO_PIECE)
	{
		pieces [capturedPiece    ] ^= toU;
		pieces [PIECES [opponent]] ^= toU;
		pieces [ALL_PIECES       ] ^= toU;

		material += piecesValues [capturedPiece];
	}
}