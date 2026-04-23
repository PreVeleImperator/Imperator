#include <string>
#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Bits.h"
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
	timeStart = GetTickCount64 ();
	timeStop  = false;

	for (int depth = 1; depth < MAX_PLY; depth ++)
	{
		int value = BestMove (depth);

		if (timeStop)
			return;

		cout << depth << " | " << GetTickCount64 () - timeStart << " | " << Value (value) << " | ";

		for (int ply = 0; ply < pvLength [0]; ply ++)
			cout << Coordinates (princVar [0] [ply] [FROM]) << Coordinates (princVar [0] [ply] [TO]) << " ";

		cout << "\n";
	}
}