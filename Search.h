#pragma once
#include "Move struct.h"
using namespace std;


enum {MOVE, PAWN_MOVE, DOUBLE_PAWN_MOVE, FIRST_K_ROOK_MOVE, FIRST_Q_ROOK_MOVE, FIRST_KING_MOVE, Q_CASTLING, K_CASTLING, Q_PROMOTION, N_PROMOTION, R_PROMOTION, B_PROMOTION};
enum {FROM, TO, TYPE};

constexpr int NO_MOVE   = -10'000'000;
constexpr int CHECKMATE =  -1'000'000;
constexpr int STALEMATE =           0;
constexpr int NO_END    =           1;

constexpr int MAX_PLY = 100;

constexpr int promotionMaterialChanges [] = {0, 0, 400, -400, 200, -200, 200, -200, 800, -800, 0, 0};
constexpr int       endgameRateChanges [] = {0, 0,   1,    1,   1,    1,   1,    1,   1,    1, 0, 0};

bool playerAtStart;
bool     opponentAtStart;

bool timeStop;
					
bool  kingMoved [2];
bool qRookMoved [2];
bool kRookMoved [2];

uint64_t enpassantAtStart;
uint64_t timeStart;
uint64_t timeLimit = 60'000;

int fiftyMovesAtStart;
int material;
int endgameRate [2];

int princVar [MAX_PLY] [MAX_PLY] [3];
int pvLength           [MAX_PLY];
int killerMoves        [MAX_PLY] [2] [3];


void GeneratePreValues           ();
void GenerateQuiescencePreValues ();

void OrderMoves           (int ply, int depth, Move moves [], int movesCount, uint64_t trspTabIndex, uint64_t trspTabCode);
void OrderQuiescenceMoves (int ply, int depth, Move moves [], int movesCount);

void GenerateMoves (bool player, bool opponent, uint64_t enpassant, bool doubleCheck, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares, Move moves [], 
					int &movesCount);

void GenerateQuiescenceMoves (bool player, bool opponent, uint64_t enpassant, uint64_t pinnedPieces [], uint64_t attackedSquares, Move moves [], int &movesCount);

void GenerateQuiescenceInCheckMoves (bool player, bool opponent, uint64_t enpassant, bool doubleCheck, uint64_t checkSquares, uint64_t pinnedPieces [], uint64_t attackedSquares,
									 Move moves [], int &movesCount);

void AttackedSquares (bool player, bool opponent, uint64_t &attackedSquares, bool &check, bool &doubleCheck, uint64_t &checkSquares);
void PinnedPieces    (bool player, bool opponent, uint64_t pinnedPieces [] , bool &check, bool &doubleCheck, uint64_t &checkSquares);

void   MakeMove (bool player, bool opponent, uint64_t &enpassant, bool &resetFiftyMoves, Move &move);
void UnmakeMove (bool player, bool opponent,                                             Move &move);

void   MakeQuiescenceMove (bool player, bool opponent, uint64_t &enpassant, Move &move);
void UnmakeQuiescenceMove (bool player, bool opponent,                      Move &move);

void Search ();

void PrincipalVariationEntry (int ply, Move &move);
void        KillerMovesEntry (int ply, Move &move);

int Evaluate (bool player);

int BestMove (int depth);

int Alfabeta   (bool player, bool opponent, uint64_t enpassant, int fiftyMoves, int ply, int depth, int alfa, int beta, bool nullMove);
int Quiescence (bool player, bool opponent, uint64_t enpassant,                 int ply,            int alfa, int beta               );

int GameEnd (int ply, bool check, int movesCount);