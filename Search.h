#pragma once
#include <array>
#include "Move struct.h"
using namespace std;


enum {MOVE, PAWN_MOVE, PAWN_DOUBLE_MOVE, FIRST_K_ROOK_MOVE, FIRST_Q_ROOK_MOVE, FIRST_KING_MOVE, Q_CASTLING, K_CASTLING, Q_PROMOTION, N_PROMOTION, R_PROMOTION, B_PROMOTION};
enum {FROM, TO, TYPE};
enum {PREVALUE_PV, PREVALUE_HASH, PREVALUE_PROMOTION, PREVALUE_WINNING, PREVALUE_EQUAL = 11, PREVALUE_KILLER1, PREVALUE_KILLER2, PREVALUE_LOSING = 14, PREVALUE_QUIET = 18};

constexpr array <array <int, 5>, 6> capturePreValues = CapturePreValues ();

constexpr int NO_MOVE   = -10'000'000;
constexpr int CHECKMATE =  -1'000'000;
constexpr int STALEMATE =           0;
constexpr int NO_END    =           1;

constexpr int MAX_PLY         = 20;
constexpr int PREVALUES_COUNT = 19;

constexpr int materialChanges [] = {0, 0, 400, -400, 200, -200, 200, -200, 800, -800, 0, 0};


bool playerToMoveAtStart;
bool     opponentAtStart;

bool timeStop;

bool  kingMoved [2];
bool qRookMoved [2];
bool kRookMoved [2];

uint64_t enpassantAtStart;
uint64_t timeStart;
uint64_t timeLimit = 10000;

int fiftyMovesAtStart;
int material;

int pv       [MAX_PLY] [MAX_PLY] [3];
int pvLength [MAX_PLY];


constexpr array <array <int, 5>, 6> CapturePreValues ();

void GenerateMoves (bool player, bool opponent, uint64_t enpassant, bool doubleCheck, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move moves [], 
					int &movesCount);

void AttackedSquares (bool player, bool opponent, uint64_t &attackedSquares, bool &check, bool &doubleCheck, uint64_t &checkSquares);
void PinnedPieces    (bool player, bool opponent, uint64_t pinnedPieces [] , bool &check, bool &doubleCheck, uint64_t &checkSquares);

void   MakeMove (bool player, bool opponent, Move &move);
void UnmakeMove (bool player, bool opponent, Move &move);

void Search ();

void PvEntry (int ply, int fromI, int toI, int type);

int Evaluate (bool player);

int BestMove (int depth);

int Alfabeta (bool player, bool opponent, uint64_t enpassant, int ply, int depth, int alfa, int beta);

int GameEnd (int ply, bool check, int movesCount);