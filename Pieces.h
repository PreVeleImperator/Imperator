#pragma once
#include <iostream>
using namespace std;


constexpr int PAWN   [] = { 0,  1};
constexpr int ROOK   [] = { 2,  3};
constexpr int KNIGHT [] = { 4,  5};
constexpr int BISHOP [] = { 6,  7};
constexpr int QUEEN  [] = { 8,  9};
constexpr int KING   [] = {10, 11};
constexpr int PIECES [] = {12, 13};

constexpr int piecesValues [] = {100, -100, 500, -500, 300, -300, 300, -300, 900, -900, 0, 0};

constexpr int NO_PIECE   = -1;
constexpr int ALL_PIECES = 14;

constexpr int WHITE = 0;
constexpr int BLACK = 1;

constexpr uint64_t FULL_UINT = 0xFFFF'FFFF'FFFF'FFFF;

constexpr char piecesChars [] = {'P', 'p', 'R', 'r', 'N', 'n', 'B', 'b', 'Q', 'q', 'K', 'k'};


int board [64];

uint64_t pieces [15];


void Fen          (string fen);
void DisplayBoard (bool toMove, int enpassant, int fiftyMoves);