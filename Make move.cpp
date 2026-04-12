#include "Search.h"
#include "Pieces.h"

void MakeMove (bool playerToMove, Move &move)
{
	bool opponent = !playerToMove;

	uint64_t fromU = move.fromU;
	uint64_t   toU = move.  toU;

	uint64_t fromTo = fromU | toU;

	int fromI = move.fromI;
	int   toI = move.  toI;

	int piece         = move.piece;
	int capturedPiece = move.capturedPiece;


	board [  toI] = board [fromI];
	board [fromI] = NO_PIECE;

	pieces [piece                ] ^= fromTo;
	pieces [PIECES [playerToMove]] ^= fromTo;
	pieces [ALL_PIECES           ] ^= fromTo;


	if (capturedPiece != NO_PIECE)
	{
		pieces [capturedPiece    ] ^= toU;
		pieces [PIECES [opponent]] ^= toU;
		pieces [ALL_PIECES       ] ^= toU;

		material -= piecesValues [capturedPiece];
	}
}