#pragma once
#include <iostream>
#include "Search.h"

namespace TrspTab
{
	struct Table
	{
		uint64_t hashCode;

		int8_t    fromI;
		int8_t      toI;
		int8_t moveType;

		int8_t depth = -1;
		int8_t nodeType;

		int16_t value;
	};


	enum {PV_NODE, ALL_NODE, CUT_NODE};

	constexpr int NO_ENTRY = NO_MOVE;

	constexpr size_t SIZE = 1ULL << 24;

	constexpr uint64_t toMove [2] = {0xa2c2a42038d4ec3d, 0x5fc25d0738e7b0f};

	constexpr uint64_t kCastling [2] = {0x625e7bff938e701e, 0x1ba4ddc6fe2b5726};
	constexpr uint64_t qCastling [2] = {0xdf0a2482ac9254cf, 0x3939eda866ababe8};

	constexpr uint64_t enpassant [8] = {
		0xb59d922db3f2da81, 0x80472ee13a970c2a, 0xf609a9d5b1a9b93c, 0x8cc9636b9188002e, 0xf5eb31c838d22963, 0xf88dd57849668d67, 0xbd97a58361616ee0, 0xc8e856d092aeb1ba
	};

	extern const uint64_t board [64] [12];


	Table *table = new Table [SIZE];


	void GenerateHashCodes ();
	void Entry (uint64_t index, uint64_t hashCode, int value, int nodeType, int ply, int depth, int fromI, int toI, int moveType);

	uint64_t PositionCode  (bool player);
	int      KnownPosition (uint64_t index, uint64_t hashCode, int ply, int depth, int alfa, int beta);
}