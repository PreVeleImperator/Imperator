#include "Search.h"


enum {P, R, N, B, Q, K};
enum {PROMOTION, WINNING_CAPTURE, EQUAL_CAPTURE = 9, LOSING_CAPTURE};


void GenerateQuiescencePreValues ()
{
	int preValues [6] [5] {};

	// winning capture
	preValues [K] [Q] = WINNING_CAPTURE + 0;
	preValues [K] [R] = WINNING_CAPTURE + 3;
	preValues [K] [N] = WINNING_CAPTURE + 5;
	preValues [K] [B] = WINNING_CAPTURE + 5;
	preValues [K] [P] = WINNING_CAPTURE + 7;

	preValues [P] [Q] = WINNING_CAPTURE + 1;
	preValues [P] [R] = WINNING_CAPTURE + 4;
	preValues [P] [N] = WINNING_CAPTURE + 6;
	preValues [P] [B] = WINNING_CAPTURE + 6;

	preValues [N] [Q] = WINNING_CAPTURE + 2;
	preValues [N] [R] = WINNING_CAPTURE + 6;

	preValues [B] [Q] = WINNING_CAPTURE + 2;
	preValues [B] [R] = WINNING_CAPTURE + 6;

	preValues [R] [Q] = WINNING_CAPTURE + 4;


	// equal capture
	preValues [P] [P] = EQUAL_CAPTURE;
	preValues [R] [R] = EQUAL_CAPTURE;
	preValues [N] [N] = EQUAL_CAPTURE;
	preValues [N] [B] = EQUAL_CAPTURE;
	preValues [B] [B] = EQUAL_CAPTURE;
	preValues [B] [N] = EQUAL_CAPTURE;
	preValues [Q] [Q] = EQUAL_CAPTURE;


	// losing capture
	preValues [N] [P] = LOSING_CAPTURE + 0;

	preValues [B] [P] = LOSING_CAPTURE + 0;

	preValues [R] [N] = LOSING_CAPTURE + 0;
	preValues [R] [B] = LOSING_CAPTURE + 0;
	preValues [R] [P] = LOSING_CAPTURE + 1;

	preValues [Q] [R] = LOSING_CAPTURE + 1;
	preValues [Q] [N] = LOSING_CAPTURE + 2;
	preValues [Q] [B] = LOSING_CAPTURE + 2;
	preValues [Q] [P] = LOSING_CAPTURE + 3;


	for (int a = 0; a < 6; a ++)
	{
		for (int b = 0; b < 5; b ++)
			cout << preValues [a] [b] << ", ";

		cout << "\n";
	}
}