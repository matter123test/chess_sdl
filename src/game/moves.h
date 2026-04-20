#pragma once

#include "objects.h"
#include <vector>

struct Move {
	int x;
	int y;
};

std::vector<Move> GetMovesForPiece(const ChessPiece& piece);