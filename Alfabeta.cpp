#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Moves.h"
#include "Transposition table.h"

int Alfabeta (bool player, bool opponent, uint64_t enpassant, int fiftyMoves, int ply, int depth, int alfa, int beta, bool nullMove)
{
	if (GetTickCount64 () - timeStart >= timeLimit)
	{
		timeStop = true;
		return 0;
	}


	uint64_t pinnedPieces [64];

	uint64_t attackedSquares = 0;
	uint64_t    checkSquares = FULL_UINT;

	uint64_t trspTabCode  = TrspTab::PositionCode (playerAtStart);
	uint64_t trspTabIndex = trspTabCode & (TrspTab::SIZE - 1);

	int movesCount = 0;
	int alfaInput  = alfa;

	bool check       = false;
	bool doubleCheck = false;

	Move moves [250];

	fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);


	AttackedSquares (player, opponent, attackedSquares, check, doubleCheck, checkSquares);
	PinnedPieces    (player, opponent, pinnedPieces   , check, doubleCheck, checkSquares);

	GenerateMoves (player, opponent, enpassant, doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);
	OrderMoves    (ply   , depth   , moves    , movesCount , trspTabIndex, trspTabCode);


	// transposition table
	if (int value = TrspTab::KnownPosition (trspTabIndex, trspTabCode, depth, alfa, beta); value != TrspTab::NO_ENTRY)
		return value;

	// nullmoves
	if (nullMove  &&  depth >= 4  &&  !check  &&  endgameRate [player])
	{
		int value = -Alfabeta (opponent, player, 0, 0, ply + 1, depth / 3, -beta, 1 - beta, false);

		if (value >= beta)
			return beta;
	}

	// game end
	if (int value = GameEnd (ply, check, movesCount); value != NO_END)
	{
		pvLength [ply] = ply;
		return value;
	}

	// search end
	if (depth <= 0)
	{
		pvLength [ply] = ply;
		return Quiescence (player, opponent, enpassant, ply, alfa, beta);
	}


	for (int i = 0; i < movesCount; i ++)
	{
		if (timeStop)
			return 0;

		Move     &move            = moves [i];
		bool      resetFiftyMoves = false;
		uint64_t  nextEnpassant;

		MakeMove (player, opponent, nextEnpassant, resetFiftyMoves, move);
		
		int nextDepth      = check           ? depth : depth      - 1;
		int nextFiftyMoves = resetFiftyMoves ? 0     : fiftyMoves + 1;

		int value = -Alfabeta (opponent, player, nextEnpassant, nextFiftyMoves, ply + 1, nextDepth, -beta, -alfa, true);

		UnmakeMove (player, opponent, move);

		if (value >= beta)
		{
			TrspTab::Entry (trspTabIndex, trspTabCode, value, TrspTab::CUT_NODE, depth, move.fromI, move.toI, move.type);

			KillerMovesEntry (ply, move);
			return beta;
		}

		if (value > alfa)
		{
			PrincipalVariationEntry (ply, move);
			alfa = value;
		}
	}


	return alfa;
}