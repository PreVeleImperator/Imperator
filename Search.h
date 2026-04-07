#pragma once
	
namespace Search
{
	constexpr int K_SIDE [] = {0, 1};
	constexpr int Q_SIDE [] = {2, 3};

	constexpr int MAX_HL = 20;


	bool toMoveAtStart;
	bool castlings [4];

	uint64_t enpassantAtStart;

	int fiftyMovesAtStart;
	int material;


	void GenerateMoves (bool toMove, uint64_t enpassant, bool &check, bool &doubleCheck);
}