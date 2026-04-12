#pragma once
#include "Move struct.h"


enum {MOVE, PAWN_MOVE, PAWN_DOUBLE_MOVE, FIRST_K_ROOK_MOVE, FIRST_Q_ROOK_MOVE, FIRST_KING_MOVE, Q_CASTLING, K_CASTLING, Q_PROMOTION, N_PROMOTION, R_PROMOTION, B_PROMOTION};

constexpr int MAX_HL = 20;

constexpr int CHECKMATE = -100'000;
constexpr int STALEMATE =        0;
constexpr int NO_END    =        1;

constexpr int MAX_DEPTH = 20;

constexpr int NO_MOVE = -1'000'000;


bool playerToMoveAtStart;

bool  kingMoved [2];
bool qRookMoved [2];
bool kRookMoved [2];

uint64_t enpassantAtStart;

int fiftyMovesAtStart;
int material;


void GenerateMoves (bool playerToMove, uint64_t enpassant, bool doubleCheck, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move moves [], int &movesCount);

void AttackedSquares (bool playerToMove, uint64_t &attackedSquares, bool &check, bool &doubleCheck, uint64_t &checkSquares);
void PinnedPieces    (bool playerToMove, uint64_t pinnedPieces [], bool doubleCheck);

int GameEnd (int ply, bool check, int movesCount);

void   MakeMove (bool playerToMove, Move &move);
void UnmakeMove (bool playerToMove, Move &move);

int PositionValue (bool playerToMove);

void BestMove (Move &bestMove, int &value, int depth);

int Alfabeta (bool playerToMove, int ply, int depth, int alfa, int beta);