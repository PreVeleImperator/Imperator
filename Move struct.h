#pragma once
#include <iostream>

struct Move
{
	uint64_t fromU;
	uint64_t toU;

	int fromI;
	int toI;

	int type;
	int piece;
	int capturedPiece;
};