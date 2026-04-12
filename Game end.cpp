#include "Search.h"

int GameEnd (int ply, bool check, int movesCount)
{
	return movesCount ?
		NO_END : check ?
			CHECKMATE + ply : STALEMATE;			
}