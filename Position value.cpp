#include "Search.h"
#include "Pieces.h"

int PositionValue (bool playerToMove)
{
	return playerToMove ? -material : material;
}