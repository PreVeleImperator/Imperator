#include <unordered_map>
#include "Pieces.h"
#include "Search.h"


static void ToMove (string &fen)
{
	toMoveAtStart = (fen [0] == 'w') ? WHITE : BLACK;
	fen.erase (0, 2);
}

static void Board (string &fen)
{
	fill (board , board  + 64, NO_PIECE);

	int squareI = 0;

	for (int ch = 0; true; ch ++)
	{
		uint64_t squareU = (1ULL << squareI);

		switch (fen [ch])
		{
			case 'P': board [squareI ++] = PAWN   [WHITE]; break;
			case 'R': board [squareI ++] = ROOK   [WHITE]; break;
			case 'N': board [squareI ++] = KNIGHT [WHITE]; break;
			case 'B': board [squareI ++] = BISHOP [WHITE]; break;
			case 'Q': board [squareI ++] = QUEEN  [WHITE]; break;
			case 'K': board [squareI ++] = KING   [WHITE]; break;

			case 'p': board [squareI ++] = PAWN   [BLACK]; break;
			case 'r': board [squareI ++] = ROOK   [BLACK]; break;
			case 'n': board [squareI ++] = KNIGHT [BLACK]; break;
			case 'b': board [squareI ++] = BISHOP [BLACK]; break;
			case 'q': board [squareI ++] = QUEEN  [BLACK]; break;
			case 'k': board [squareI ++] = KING   [BLACK]; break;

			case '1': squareI += 1; break;
			case '2': squareI += 2; break;
			case '3': squareI += 3; break;
			case '4': squareI += 4; break;
			case '5': squareI += 5; break;
			case '6': squareI += 6; break;
			case '7': squareI += 7; break;
			case '8': squareI += 8; break;
		}

		if (squareI == 64)
		{
			fen.erase (0, ch + 2);
			return;
		}
	}
}

static void Castlings (string &fen)
{
	fill (castlings, castlings + 4, false);

	if (fen [0] == '-')
	{
		fen.erase (0, 2);
		return;
	}

	for (auto i = 0; i <= 4; i ++)
		switch (fen [i])
		{
			case 'K': castlings [K_SIDE [WHITE]] = true; break;
			case 'Q': castlings [Q_SIDE [WHITE]] = true; break;

			case 'k': castlings [K_SIDE [BLACK]] = true; break;
			case 'q': castlings [Q_SIDE [BLACK]] = true; break;

			case ' ': fen.erase (0, i + 1); return;
		}
}

static void Enpassant (string &fen)
{
	if (fen [0] == '-')
	{
		enpassantAtStart = 0;
		fen.erase (0, 2);
		return;
	}

	enpassantAtStart = (fen [0] - 'a') + (7 - (fen [1] - '1')) * 8;
	fen.erase (0, 3);
}

static void FiftyMoves (string &fen)
{
	fiftyMovesAtStart = (fen [0] - '0');

	if (fen [1] != ' ')
	{
		fiftyMovesAtStart = (10 * fiftyMovesAtStart) + (fen [1] - '0');
		fen.erase (0, 3);
	}
	else
		fen.erase (0, 2);
}

static void PiecesPositions ()
{
	fill (pieces, pieces + 15, 0);

	for (int squareI = 0; squareI < 64; squareI ++)
	{
		int piece = board [squareI];

		if (piece != NO_PIECE)
		{
			uint64_t squareU = 1ULL << piece;

			pieces [piece             ] |= squareU;
			pieces [PIECES [piece % 2]] |= squareU;
			pieces [ALL_PIECES        ] |= squareU;
		}
	}
}

static void Material ()
{
	material = 0;

	for (int squareI = 0; squareI < 64; squareI ++)
	{
		int piece = board [squareI];

		if (piece != NO_PIECE)
			material += piecesValues [piece];
	}
}

void Fen (string fen)
{
	Board      (fen);
	ToMove     (fen);
	Castlings  (fen);
	Enpassant  (fen);
	FiftyMoves (fen);

	PiecesPositions ();
	Material        ();
}