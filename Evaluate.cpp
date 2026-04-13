#include "Search.h"
#include "Pieces.h"

int Evaluate (bool player)
{
	return player ? -material : material;
}