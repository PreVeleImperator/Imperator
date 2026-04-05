#pragma once


constexpr int K_SIDE [] = {0, 1};
constexpr int Q_SIDE [] = {2, 3};

constexpr int MAX_HL = 20;


bool toMoveAtStart;
bool castlings [4];

int enpassantAtStart;
int fiftyMovesAtStart;
int material;