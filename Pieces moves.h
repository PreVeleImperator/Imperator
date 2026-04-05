#pragma once
#include <iostream>
using namespace std;

namespace PiecesMoves
{
	constexpr uint64_t   rookBorders [] = {0x8080808080808080, 0xFF00000000000000, 0x0101010101010101, 0x00000000000000FF};
	constexpr uint64_t bishopBorders [] = {0xFF80808080808080, 0xFF01010101010101, 0x01010101010101FF, 0x80808080808080FF};

	constexpr uint64_t knightBorders [] = {0xFFFF808080808080, 0xFFFF010101010101, 0xFFC0C0C0C0C0C0C0, 0xFF03030303030303, 
										   0x010101010101FFFF, 0x808080808080FFFF, 0x03030303030303FF, 0xC0C0C0C0C0C0C0FF};

	constexpr uint64_t kingBorders [] = {0x8080808080808080, 0xFF00000000000000, 0x0101010101010101, 0x00000000000000FF,
										 0xFF80808080808080, 0xFF01010101010101, 0x01010101010101FF, 0x80808080808080FF};

	constexpr int pawnCaptDirections [2] [2] {-9, -7, 9, 7};

	constexpr int knightDirections [] {17, 15, 10,  6, -17, -15, -10, -6};
	constexpr int   kingDirections [] { 1,  8, -1, -8,   9,   7,  -9, -7};

	constexpr int   rookDirections [] {1, 8, -1, -8};
	constexpr int bishopDirections [] {9, 7, -9, -7};

	constexpr int   rookCombinationsCount = 102'400;
	constexpr int bishopCombinationsCount =   5'248;
	

	alignas (64) extern const uint64_t   rookCombinations [  rookCombinationsCount];
	alignas (64) extern const uint64_t bishopCombinations [bishopCombinationsCount];

	alignas (64) extern const uint64_t   rook [  rookCombinationsCount];
	alignas (64) extern const uint64_t bishop [bishopCombinationsCount];


	/*constexpr uint64_t rookMagics [] = {
	};*/

	/*constexpr uint64_t bishopMagics [] = {
	};*/


	constexpr int rookCombinationsCounts [] = {
		4096, 2048, 2048, 2048, 2048, 2048, 2048, 4096,
		2048, 1024, 1024, 1024, 1024, 1024, 1024, 2048,
		2048, 1024, 1024, 1024, 1024, 1024, 1024, 2048,
		2048, 1024, 1024, 1024, 1024, 1024, 1024, 2048,
		2048, 1024, 1024, 1024, 1024, 1024, 1024, 2048,
		2048, 1024, 1024, 1024, 1024, 1024, 1024, 2048,
		2048, 1024, 1024, 1024, 1024, 1024, 1024, 2048,
		4096, 2048, 2048, 2048, 2048, 2048, 2048, 4096
	};

	constexpr int bishopCombinationsCounts [] = {
		64,  32,   32,   32,   32,   32,  32,  64,
		32,  32,   32,   32,   32,   32,  32,  32,
		32,  32,  128,  128,  128,  128,  32,  32,
		32,  32,  128,  512,  512,  128,  32,  32,
		32,  32,  128,  512,  512,  128,  32,  32,
		32,  32,  128,  128,  128,  128,  32,  32,
		32,  32,   32,   32,   32,   32,  32,  32,
		64,  32,   32,   32,   32,   32,  32,  64
	};


	constexpr int rookShifts [] = {
		52, 53, 53, 53, 53, 53, 53, 52,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		52, 53, 53, 53, 53, 53, 53, 52
	};

	constexpr int bishopShifts [] = {
		58, 59, 59, 59, 59, 59, 59, 58,
		59, 59, 59, 59, 59, 59, 59, 59,
		59, 59, 57, 57, 57, 57, 59, 59,
		59, 59, 57, 55, 55, 57, 59, 59,
		59, 59, 57, 55, 55, 57, 59, 59,
		59, 59, 57, 57, 57, 57, 59, 59,
		59, 59, 59, 59, 59, 59, 59, 59,
		58, 59, 59, 59, 59, 59, 59, 58
	};


	constexpr int rookOffsets [] = {
			0,  4096,  6144,  8192, 10240, 12288, 14336, 16384,
		20480, 22528, 23552, 24576, 25600, 26624, 27648, 28672,
		30720, 32768, 33792, 34816, 35840, 36864, 37888, 38912,
		40960, 43008, 44032, 45056, 46080, 47104, 48128, 49152,
		51200, 53248, 54272, 55296, 56320, 57344, 58368, 59392,
		61440, 63488, 64512, 65536, 66560, 67584, 68608, 69632,
		71680, 73728, 74752, 75776, 76800, 77824, 78848, 79872,
		81920, 86016, 88064, 90112, 92160, 94208, 96256, 98304
	};

	constexpr int bishopOffsets [] = {
		   0,   64,   96,  128,  160,  192,  224,  256,
		 320,  352,  384,  416,  448,  480,  512,  544,
		 576,  608,  736,  864,  992, 1120, 1248, 1280,
		1312, 1344, 1472, 1600, 1728, 1856, 1984, 2016,
		2048, 2080, 2208, 2336, 2464, 2592, 2720, 2752,
		2784, 2816, 2944, 3072, 3200, 3328, 3456, 3488,
		3520, 3552, 3584, 3616, 3648, 3680, 3712, 3744,
		3776, 3840, 3872, 3904, 3936, 3968, 4000, 4032
	};


	/*constexpr uint64_t pawn     [64];
	constexpr uint64_t pawnCapt [64];
	constexpr uint64_t knight   [64];
	constexpr uint64_t king     [64];*/


	void GenerateCombinations (const int      directions   [], const uint64_t borders [], const int combinationsCount    , string    fileName, string arrayName);
	void GenerateMagics       (const uint64_t combinations [], const int      shifts  [], const int combinationsCounts [], const int offsets []);
}