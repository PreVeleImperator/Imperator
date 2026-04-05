#include <iostream>
#include "Xoshiro256.h"

static uint64_t state [4];

static uint64_t RotateLeft (uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

uint64_t Xoshiro256Next ()
{
	const uint64_t result = RotateLeft (state [1] * 5, 7) * 9;
	const uint64_t t      = state [1] << 17;

	state [2] ^= state [0];
	state [3] ^= state [1];
	state [1] ^= state [2];
	state [0] ^= state [3];

	state [2] ^= t;
	state [3] = RotateLeft (state [3], 45);

	return result;
}


static uint64_t SplitMix64 (uint64_t &seed)
{
	uint64_t z = (seed += 0x9e3779b97f4a7c15ULL);

	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
	z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;

	return z ^ (z >> 31);
}

void Xoshiro256Seed (uint64_t seed)
{
	for (int i = 0; i < 4; i ++)
		state [i] = SplitMix64 (seed);
}