#include <Windows.h>
#include "Search.h"
#include "Pieces.h"
#include "Transposition table.h"
using namespace std;


int Alphabeta (bool player, bool opponent, uint64_t enpassant, int fiftyMoves, int ply, int depth, int alpha, int beta, bool nullMove)
{
	// time limit
	if (GetAsyncKeyState (VK_SPACE) & 0x8000)
	{
		stopSearch = true;
		return 0;
	}


	// game actual path
	actualPath [ply] = TrspTab::PositionCode (player);


	uint64_t trspTabIndex     = actualPath [ply] & (TrspTab::SIZE - 1ULL);
	bool     thisIsPv         = beta - alpha > 1;
	int      positionRepeated = PositionRepeated (ply, fiftyMoves);


	// position repetition
	if (positionRepeated == 2)
	{
		pvLength [ply] = ply;
		return 0;
	}


	// position from transposition table
	if (!thisIsPv  &&  !positionRepeated)
		if (int value = TrspTab::KnownPosition (trspTabIndex, actualPath [ply], ply, depth, alpha, beta); value != TrspTab::NO_ENTRY)
			return value;
		

	// moves generation
	uint64_t pinnedPieces [64]; fill (pinnedPieces, pinnedPieces + 64, FULL_UINT);

	uint64_t attackedSquares = 0;
	uint64_t    checkSquares = FULL_UINT;

	int movesCount = 0;
	int oldAlpha   = alpha;

	bool check       = false;
	bool doubleCheck = false;

	Move moves [250];

	AttackedSquares (player, opponent, attackedSquares, check, doubleCheck, checkSquares);
	PinnedPieces    (player, opponent, pinnedPieces   , check, doubleCheck, checkSquares);

	GenerateMoves (player, opponent, enpassant, doubleCheck, checkSquares, pinnedPieces, attackedSquares, moves, movesCount);

	
	// checkmate, stalemate
	if (int value = GameEnd (ply, check, movesCount, fiftyMoves); value != NO_END)
	{
		pvLength [ply] = ply;
		return value;
	}


	// search leaf
	if (depth == 0)
	{
		pvLength [ply] = ply;
		return Quiescence (player, opponent, enpassant, ply, alpha, beta);
	}


	// nullmove
	if (!thisIsPv  &&  nullMove  &&  depth >= 3  &&  !check  &&  endgameRate [player])
	{
		int value = -Alphabeta (opponent, player, 0, 0, ply + 1, depth / 3, -beta, 1 - beta, false);

		if (value >= beta)
			return beta;
	}


	// moves ordering
	OrderMoves (ply, depth, moves, movesCount, trspTabIndex);


	// principal variation search
	{
		// make move
		Move     &move            = moves [0];
		bool      resetFiftyMoves = false;
		uint64_t  nextEnpassant;

		MakeMove (player, opponent, nextEnpassant, resetFiftyMoves, move);
		

		// next ply
		int nextDepth      = check           ? depth : depth      - 1;
		int nextFiftyMoves = resetFiftyMoves ? 0     : fiftyMoves + 1;
		int value;

		value = -Alphabeta (opponent, player, nextEnpassant, nextFiftyMoves, ply + 1, nextDepth, -beta, -alpha, true);


		// unmake move
		UnmakeMove (player, opponent, move);


		//alphabeta
		if (value >= beta)
		{
			TrspTab::Entry (trspTabIndex, actualPath [ply], value, TrspTab::CUT_NODE, ply, depth, move.fromI, move.toI, move.type);

			KillerMovesEntry (ply, move);
			return beta;
		}

		if (value > alpha)
		{
			PrincVarEntry (ply, move);
			alpha = value;
		}
	}


	// search
	for (int moveNum = 1; moveNum < movesCount; moveNum ++)
	{
		// time limit
		if (stopSearch)
			return 0;


		// make move
		Move     &move            = moves [moveNum];
		bool      resetFiftyMoves = false;
		uint64_t  nextEnpassant;

		MakeMove (player, opponent, nextEnpassant, resetFiftyMoves, move);
		

		// next ply
		int nextDepth      = check           ? depth : depth      - 1;
		int nextFiftyMoves = resetFiftyMoves ? 0     : fiftyMoves + 1;
		int value;

		// null window
		value = -Alphabeta (opponent, player, nextEnpassant, nextFiftyMoves, ply + 1, nextDepth, -alpha - 1, -alpha, true);

		// full window
		if (value > alpha  &&  value < beta)
			value = -Alphabeta (opponent, player, nextEnpassant, nextFiftyMoves, ply + 1, nextDepth, -beta, -alpha, true);		


		// unmake window
		UnmakeMove (player, opponent, move);


		// alphabeta
		if (value >= beta)
		{
			TrspTab::Entry (trspTabIndex, actualPath [ply], value, TrspTab::CUT_NODE, ply, depth, move.fromI, move.toI, move.type);

			KillerMovesEntry (ply, move);
			return beta;
		}

		if (value > alpha)
		{
			PrincVarEntry (ply, move);
			alpha = value;
		}
	}


	// transposition table entry
	if (alpha != oldAlpha)
	{
		TrspTab::Entry (trspTabIndex, actualPath [ply], alpha, TrspTab::PV_NODE, ply, depth, princVar [0] [ply] [FROM], princVar [0] [ply] [TO], princVar [0] [ply] [TYPE]);
	}
	else
	{
		TrspTab::Entry (trspTabIndex, actualPath [ply], alpha, TrspTab::ALL_NODE, ply, depth, -1, -1, -1);
	}

	
	// return
	return alpha;
}