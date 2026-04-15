#pragma warning (disable : 4146)

#include <iostream>
#include <string>
#include <bit>
#include "Pieces.h"
#include "Search.h"
#include "Bits.h"
#include "Pieces moves.h"
#include "Xoshiro256.h"
using namespace std;

int main ()
{
	Xoshiro256Seed (0x123456789ABCDEF);

	while (true)
	{
		string fen;
		cout << "FEN: ";
		getline (cin, fen);

		system ("cls");
		Fen (fen);
		DisplayBoard (playerToMoveAtStart, enpassantAtStart, fiftyMovesAtStart);

		Search ();
		cout << "\n";
	}

	return 0;
}