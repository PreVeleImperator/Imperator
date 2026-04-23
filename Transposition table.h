#pragma once
#include <iostream>
#include "Search.h"

namespace TrspTab
{
	struct alignas (64) Table
	{
		uint64_t code = 0;

		int    fromI;
		int      toI;
		int moveType;

		int depth;
		int value;
		int nodeType;
	};


	enum {PV_NODE, ALL_NODE, CUT_NODE};

	constexpr int NO_ENTRY = NO_MOVE;

	const size_t SIZE = 16'777'216; // 2^24, 1ULL * 1024 * 1024 * 1024 / sizeof (Table);

	constexpr uint64_t toMove [2] = {0xa2c2a42038d4ec3d, 0x5fc25d0738e7b0f};

	constexpr uint64_t enpassant [8] = {
		0x625e7bff938e701e, 0x1ba4ddc6fe2b5726, 0xdf0a2482ac9254cf, 0x3939eda866ababe8, 0xb59d922db3f2da81, 0x80472ee13a970c2a, 0xf609a9d5b1a9b93c, 0x8cc9636b9188002e
	};

	extern const uint64_t board [64] [13];


	Table *table = new Table [SIZE];


	void GenerateHashCodes ();
	void Entry (uint64_t index, uint64_t code, int value, int nodeType, int depth, int fromI, int toI, int moveType);

	uint64_t PositionCode  (bool player);
	int      KnownPosition (uint64_t index, uint64_t code, int depth, int alfa, int beta);
}