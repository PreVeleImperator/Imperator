#include "Pieces.h"
#include "Search.h"


static void ToMove (string &fen)
{
	  playerAtStart = (fen [0] == 'w') ? WHITE : BLACK;
	opponentAtStart = !playerAtStart;

	fen.erase (0, 2);
}

static void Board (string &fen)
{
	fill (board , board  + 64, NO_PIECE);

	int square = 0;

	for (int ch = 0; true; ch ++)
	{
		switch (fen [ch])
		{
			case 'P': board [square ++] = PAWN   [WHITE]; break;
			case 'R': board [square ++] = ROOK   [WHITE]; break;
			case 'N': board [square ++] = KNIGHT [WHITE]; break;
			case 'B': board [square ++] = BISHOP [WHITE]; break;
			case 'Q': board [square ++] = QUEEN  [WHITE]; break;
			case 'K': board [square ++] = KING   [WHITE]; break;

			case 'p': board [square ++] = PAWN   [BLACK]; break;
			case 'r': board [square ++] = ROOK   [BLACK]; break;
			case 'n': board [square ++] = KNIGHT [BLACK]; break;
			case 'b': board [square ++] = BISHOP [BLACK]; break;
			case 'q': board [square ++] = QUEEN  [BLACK]; break;
			case 'k': board [square ++] = KING   [BLACK]; break;

			case '1': square += 1; break;
			case '2': square += 2; break;
			case '3': square += 3; break;
			case '4': square += 4; break;
			case '5': square += 5; break;
			case '6': square += 6; break;
			case '7': square += 7; break;
			case '8': square += 8; break;
		}

		if (square == 64)
		{
			fen.erase (0, ch + 2);
			return;
		}
	}
}

static void Castlings (string &fen)
{
	kingMoved  [WHITE] = kingMoved  [BLACK] = true;
	kRookMoved [WHITE] = kRookMoved [BLACK] = true;
	qRookMoved [WHITE] = qRookMoved [BLACK] = true;

	if (fen [0] == '-')
	{
		fen.erase (0, 2);
		return;
	}

	for (auto i = 0; i <= 4; i ++)
		switch (fen [i])
		{
			case 'K': kingMoved [WHITE] = kRookMoved [WHITE] = false; break;
			case 'Q': kingMoved [WHITE] = qRookMoved [WHITE] = false; break;

			case 'k': kingMoved [BLACK] = kRookMoved [BLACK] = false; break;
			case 'q': kingMoved [BLACK] = qRookMoved [BLACK] = false; break;

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

	enpassantAtStart = 1ULL << ((fen [0] - 'a') + (7 - (fen [1] - '1')) * 8);
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
			uint64_t squareU = 1ULL << squareI;

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

static void EndgameRate ()
{
	endgameRate [WHITE] = endgameRate [BLACK] = 0;

	for (int squareI = 0; squareI < 64; squareI ++)
	{
		int piece = board [squareI];

		if (piece != NO_PIECE)
			endgameRate [piece % 2] += endgameRateChanges [piece];
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
	EndgameRate     ();
}