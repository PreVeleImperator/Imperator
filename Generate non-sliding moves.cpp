#include "Pieces moves.h"
#include "Bits.h";

void GenerateNonSlidingMoves (const int directions [], const uint64_t borders [], const int directionsCount)
{
	for (int square = 0; square < 64; square ++)
	{
		uint64_t moves = 0;
		
		for (int dir = 0; dir < directionsCount; dir ++)
			if ((1ULL << square) & ~borders [dir])
				moves |= 1ULL << (square + directions [dir]);

		cout << "0x" << hex << moves << ", ";
		
		if (square % 8 == 7)
			cout << "\n";
	}
}