#include "Pieces.h"
#include "Search.h"
#include "Coordinates.h"
using namespace std;


static void DisplayFen (bool toMove, int enpassant, int fiftyMoves)
{
	// board
	{
		for (int row = 0; row < 8; row ++)
		{
			int emptySquares = 0;

			for (int column = 0; column < 8; column ++)
			{
				int square = (row * 8 + column);

				if (board [square] == NO_PIECE)
				{
					emptySquares ++;
				}
				else
				{
					if (emptySquares)
					{
						cout << emptySquares;
						emptySquares = 0;
					}

					cout << piecesChars [board [square]];
				}
			}
			
			if (emptySquares)
				cout << emptySquares;

			if (row != 7)
				cout << "/";
		}

		cout << " ";
	}

	// to move
	{
		if (toMove == WHITE) {cout << "w ";}
		if (toMove == BLACK) {cout << "b ";}
	}

	// castlings
	{
		bool noCastling = true;

		if (castlings [K_SIDE [WHITE]]) {cout << "K"; noCastling = false;}
		if (castlings [Q_SIDE [WHITE]]) {cout << "Q"; noCastling = false;}
		if (castlings [K_SIDE [BLACK]]) {cout << "k"; noCastling = false;}
		if (castlings [Q_SIDE [BLACK]]) {cout << "q"; noCastling = false;}
	
		if (noCastling) {cout << "- ";}
		else            {cout << " " ;}
	}

	// enpassant
	{
		if (enpassant)
		{
			cout << Coordinates (enpassant) << " ";
		}
		else
		{
			cout << "- ";
		}
	}

	// fifty moves
	{
		cout << fiftyMoves << " 1";
	}

	cout << "\n";
}

void DisplayBoard (bool toMove, int enpassant, int fiftyMoves)
{
	DisplayFen (toMove, enpassant, fiftyMoves);
	cout << material << "\n";

	for (int i = 0; i < 64; i ++)
	{
		if (board [i] == -1)
		{
			cout << "+ ";
		}
		else
		{
			cout << piecesChars [board [i]] << " ";
		}

		if (i % 8 == 7)
			cout << "\n";
	}

	cout << "\n";
}