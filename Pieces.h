#pragma once
#include <iostream>
using namespace std;

enum
{
	A8, B8, C8, D8, E8, F8, G8, H8,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A1, B1, C1, D1, E1, F1, G1, H1
};


constexpr int PAWN   [] = { 0,  1};
constexpr int ROOK   [] = { 2,  3};
constexpr int KNIGHT [] = { 4,  5};
constexpr int BISHOP [] = { 6,  7};
constexpr int QUEEN  [] = { 8,  9};
constexpr int KING   [] = {10, 11};
constexpr int PIECES [] = {12, 13};

constexpr int piecesValues     [] = {100, -100, 500, -500, 300, -300, 300, -300, 900, -900, 0, 0};

constexpr int NO_PIECE   = -1;
constexpr int ALL_PIECES = 14;

constexpr int WHITE = 0;
constexpr int BLACK = 1;

constexpr uint64_t FULL_UINT = 0xFFFF'FFFF'FFFF'FFFF;

constexpr char piecesChars [] = {'P', 'p', 'R', 'r', 'N', 'n', 'B', 'b', 'Q', 'q', 'K', 'k'};


int board [64];

uint64_t pieces [15];


void Fen          (string fen);
void DisplayBoard (bool player, uint64_t enpassant, int fiftyMoves);

string Coordinates (int square);