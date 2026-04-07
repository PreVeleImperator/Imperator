#pragma warning (disable : 6001)

#include <fstream>
#include "Pieces.h"
#include "Pieces moves.h"
#include "Bits.h"

void PiecesMoves::GenerateSlidingMoves (const int directions [], const uint64_t borders [], const uint64_t combinations [], const int combinationsCounts [], const int offsets [], const int shifts [], 
									    const uint64_t magics [], const int combinationsCount, string fileName, string arrayName)
{
	auto moves = new uint64_t [combinationsCount];
	fill (moves, moves + combinationsCount, 0);

	for (int squareI = 0; squareI < 64; squareI ++)
	{
		for (int comb = 0; comb < combinationsCounts [squareI]; comb ++)
		{
			uint64_t combination = combinations [offsets [squareI] + comb];
			uint64_t index       = (combination * magics [squareI]) >> shifts [squareI];

			for (int dir = 0; dir < 4; dir ++)
			{
				uint64_t squareU = 1ULL << squareI;

				if (squareU & borders [dir])
					continue;

				for (int move = 1; move < 8; move ++)
				{
					squareU = 1ULL << (squareI + directions [dir] * move);
					moves [offsets [squareI] + index] |= squareU;

					if (squareU & borders [dir]  ||  squareU & combination)
						break;
				}
			}
		}
	}


	ofstream o (fileName);

	o << "const uint64_t " << arrayName << " [] = {" << "\n    ";

	for (int move = 0; move < combinationsCount; move ++)
	{
		o << "0x" << hex << moves [move] << ", ";

		if (move % 5 == 4  &&  move != combinationsCount - 1)
			o << "\n" << "    ";
	}

	o << "\n};";

	delete [] moves;
}


uint64_t PiecesMoves::Rook (int square)
{
	int offset = rookOffsets [square];

	uint64_t occupancy = pieces [ALL_PIECES] & rookCombinations [offset];
	uint64_t magic     = rookMagics [square];
	uint64_t index     = (occupancy * magic) >> rookShifts [square];

	return rook [offset + index];
}

uint64_t PiecesMoves::Rook (int square, uint64_t occupancyException)
{
	int offset = rookOffsets [square];

	uint64_t occupancy = (pieces [ALL_PIECES] & ~occupancyException) & rookCombinations [offset];
	uint64_t magic     = rookMagics [square];
	uint64_t index     = (occupancy * magic) >> rookShifts [square];

	return rook [offset + index];
}


uint64_t PiecesMoves::Bishop (int square)
{
	int offset = bishopOffsets [square];

	uint64_t occupancy = pieces [ALL_PIECES] & bishopCombinations [offset];
	uint64_t magic = bishopMagics [square];
	uint64_t index = (occupancy * magic) >> bishopShifts [square];

	return bishop [offset + index];
}

uint64_t PiecesMoves::Bishop (int square, uint64_t occupancyException)
{
	int offset = bishopOffsets [square];

	uint64_t occupancy = (pieces [ALL_PIECES] & ~occupancyException) & bishopCombinations [offset];
	uint64_t magic = bishopMagics [square];
	uint64_t index = (occupancy * magic) >> bishopShifts [square];

	return bishop [offset + index];
}