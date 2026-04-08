#pragma once
#include "Move struct.h"


enum {MOVE, PAWN_MOVE, DOUBLE_PAWN_MOVE, Q_CASTLING, K_CASTLING, Q_PROMOTION, N_PROMOTION, R_PROMOTION, B_PROMOTION};

constexpr int K_SIDE [] = {0, 1};
constexpr int Q_SIDE [] = {2, 3};

constexpr int MAX_HL = 20;


bool playerToMoveAtStart;
bool castlings [4];

uint64_t enpassantAtStart;

int fiftyMovesAtStart;
int material;


void GenerateMoves (bool playerToMove, uint64_t enpassant, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, int &movesCount, Move moves []);

void AttackedSquares (bool playerToMove, uint64_t &attackedSquares, bool &check, bool &doubleCheck, uint64_t &checkSquares);
void PinnedPieces    (bool playerToMove, uint64_t pinnedPieces []);