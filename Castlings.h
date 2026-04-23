#pragma once
#include <iostream>
#include "Pieces.h"

namespace KCastling
{
	constexpr uint64_t KingFromU [] = {0x1000000000000000, 0x10};
	constexpr uint64_t KingToU   [] = {0x4000000000000000, 0x40};

	constexpr int KingFromI [] = {E1, E8};
	constexpr int KIngToI   [] = {G1, G8};


	constexpr uint64_t RookMoveU [] = {0xa000000000000000, 0xa0};

	constexpr int RookFromI [] = {H1, H8};
	constexpr int RookToI   [] = {F1, F8};


	constexpr uint64_t attackedSquares [] = {0x7000000000000000, 0x70};
	constexpr uint64_t occupiedSquares [] = {0x6000000000000000, 0x60};
}

namespace QCastling
{
	constexpr uint64_t KingFromU [] = {0x1000000000000000, 0x10};
	constexpr uint64_t KingToU   [] = {0x400000000000000 , 0x4 };

	constexpr int KingFromI [] = {E1, E8};
	constexpr int KIngToI   [] = {C1, C8};


	constexpr uint64_t RookMoveU [] = {0x900000000000000, 0x9};

	constexpr int RookFromI [] = {A1, D1};
	constexpr int RookToI   [] = {A1, A8};


	constexpr uint64_t attackedSquares [] = {0x1c00000000000000, 0x1c};
	constexpr uint64_t occupiedSquares [] = {0xe00000000000000 , 0xe };
}