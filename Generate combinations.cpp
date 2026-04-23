#pragma warning (disable : 4146)


#include <fstream>
#include "Moves.h"
#include "Bits.h"
using namespace std;


static void Recursion (uint64_t occupancy, uint64_t combination, uint64_t combinations [], int &writtenCombsCount)
{
	if (!occupancy)
	{
		combinations [writtenCombsCount ++] = combination;
		return;
	}

	uint64_t bit  = occupancy & -occupancy;
	uint64_t rest = occupancy & (occupancy - 1);

	Recursion (rest, combination ^ bit, combinations, writtenCombsCount);
	Recursion (rest, combination      , combinations, writtenCombsCount);
}

void GenerateCombinations (const int directions [], const uint64_t borders [], const int combinationsCount, string fileName, string arrayName)
{
	auto combinations      = new uint64_t [combinationsCount];
	int  writtenCombsCount = 0;

	for (int squareI = 0; squareI < 64; squareI ++)
	{
		uint64_t occupancy = 0;

		for (int direction = 0; direction < 4; direction ++)
		{
			uint64_t squareU = 1ULL << squareI;
			
			if (squareU & borders [direction])
				continue;

			for (int shift = 1; shift < 8; shift ++)
			{
				squareU = 1ULL << (squareI + directions [direction] * shift);

				if (squareU & borders [direction])
					break;

				occupancy |= squareU;
			}
		}

		Bits::Display (occupancy);
		cin.get ();

		Recursion (occupancy, 0, combinations, writtenCombsCount);
	}


	ofstream o (fileName);

	o << "const uint64_t " << arrayName << " [] = {" << "\n    ";

	for (int comb = 0; comb < combinationsCount; comb ++)
	{
		o << "0x" << hex << combinations [comb] << ", ";

		if (comb % 5 == 4  &&  comb != combinationsCount - 1)
			o << "\n" << "    ";
	}

	o << "\n};";

	delete [] combinations;
}