#pragma once

#include "game.h"
#include "objects.h"
#include <string>

#define STARTING_POS_STR "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"

void FENToBoard(const std::string& FEN_string, ChessBoard& board);
std::string BoardToFEN(ChessBoard& board);

void ClearBoard(ChessBoard& board);
void ResetBoard(ChessBoard& board);