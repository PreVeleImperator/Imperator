#include "Search.h"

static enum {P, R, N, B, Q, K};

constexpr array <array <int, 5>, 6> CapturePreValues ()
{
	array <array <int, 5>, 6> preValues {};

	// winning capture
	preValues [K] [Q] = PREVALUE_WINNING + 0;
	preValues [K] [R] = PREVALUE_WINNING + 3;
	preValues [K] [N] = PREVALUE_WINNING + 5;
	preValues [K] [B] = PREVALUE_WINNING + 5;
	preValues [K] [P] = PREVALUE_WINNING + 7;

	preValues [P] [Q] = PREVALUE_WINNING + 1;
	preValues [P] [R] = PREVALUE_WINNING + 4;
	preValues [P] [N] = PREVALUE_WINNING + 6;
	preValues [P] [B] = PREVALUE_WINNING + 6;

	preValues [N] [Q] = PREVALUE_WINNING + 2;
	preValues [N] [R] = PREVALUE_WINNING + 6;

	preValues [B] [Q] = PREVALUE_WINNING + 2;
	preValues [B] [R] = PREVALUE_WINNING + 6;

	preValues [R] [Q] = PREVALUE_WINNING + 4;


	// equal capture
	preValues [P] [P] = PREVALUE_EQUAL;
	preValues [R] [R] = PREVALUE_EQUAL;
	preValues [N] [N] = PREVALUE_EQUAL;
	preValues [B] [B] = PREVALUE_EQUAL;
	preValues [Q] [Q] = PREVALUE_EQUAL;


	// losing capture
	preValues [N] [P] = PREVALUE_LOSING + 0;

	preValues [B] [P] = PREVALUE_LOSING + 0;

	preValues [R] [N] = PREVALUE_LOSING + 0;
	preValues [R] [B] = PREVALUE_LOSING + 0;
	preValues [R] [P] = PREVALUE_LOSING + 1;

	preValues [Q] [R] = PREVALUE_LOSING + 1;
	preValues [Q] [N] = PREVALUE_LOSING + 2;
	preValues [Q] [B] = PREVALUE_LOSING + 2;
	preValues [Q] [P] = PREVALUE_LOSING + 3;


	return preValues;
}