#include "Moves.h"
#include "Xoshiro256.h"
#include "Bits.h"
using namespace std;

static bool Validation (uint64_t magic, const uint64_t combinations [], const int combinationsCount, const int shift, const int offset)
{
	auto validations = new bool [combinationsCount];
	fill (validations, validations + combinationsCount, false);

	for (int comb = 0; comb < combinationsCount; comb ++)
	{
		uint64_t index = (combinations [offset + comb] * magic) >> shift;

		if (validations [index])
		{
			delete [] validations;
			return false;
		}

		validations [index] = true;
	}

	delete [] validations;
	return true;
}

void GenerateMagics (const uint64_t combinations [], const int shifts [], const int combinationsCounts [], const int offsets [])
{
	for (int square = 0; square < 64; square ++)
		while (true)
		{
			uint64_t magic = Xoshiro256Next () & Xoshiro256Next () & Xoshiro256Next ();

			if (Validation (magic, combinations, combinationsCounts [square], shifts [square], offsets [square]))
			{
				cout << "0x" << hex << magic << ", ";

				if (square % 8 == 7)
					cout << "\n";

				break;
			}
		}
}