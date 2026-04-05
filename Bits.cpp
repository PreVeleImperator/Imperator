#include <iostream>
#include "Bits.h"
using namespace std;

namespace Bits
{
	void Display (uint64_t bits)
	{
		for (auto i = 0; i < 64; i ++)
		{
			if (bits & (1ULL << i))
				cout << "O ";
			else
				cout << "+ ";

			if (i % 8 == 7)
				cout << "\n";
		}

		cout << "\n";
	}
}