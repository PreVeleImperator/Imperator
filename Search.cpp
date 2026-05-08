#include <string>
#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Bits.h"
#include "Transposition table.h"
using namespace std;

static string Value (int value)
{
	string v;
	value = playerAtStart ? -value : value;

	if (value >= -CHECKMATE - MAX_PLY)
	{
		v = "#" + to_string (-CHECKMATE - value);
	}
	else if (value <= CHECKMATE + MAX_PLY)
	{
		v = "#-" + to_string (-CHECKMATE + value);
	}
	else
	{
		v = to_string (value);
	}

	return v;
}

void Search ()
{
	timeStart  = GetTickCount64 ();
	stopSearch = false;

	actualPath [0] = actualHashCode = TrspTab::PositionCode (playerAtStart);

	for (int depth = 1; depth < MAX_PLY; depth ++)
	{
		int value = BestMove (depth);

		if (stopSearch)
			return;

		cout << depth << " | " << GetTickCount64 () - timeStart << " | " << Value (value) << " | ";

		for (int ply = 0; ply < pvLength [0]; ply ++)
			cout << Coordinates (princVar [0] [ply] [FROM]) << Coordinates (princVar [0] [ply] [TO]) << " ";

		cout << "\n";
	}
}