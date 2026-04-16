#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Pieces moves.h"

int Quiescence (bool player, bool opponent, uint64_t enpassant, int ply, int alfa, int beta)
{
	if (GetTickCount64 () - timeStart >= timeLimit)
	{
		timeStop = true;
		return 0;
	}


	int value = Evaluate (player);

	if (value >= beta)
		return value;

	if (value > alfa)
		alfa = value;


}