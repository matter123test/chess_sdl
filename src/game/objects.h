#pragma once

#include <array>
#include <SDL3/SDL.h>

enum ChessPiece {
	EMPTY,

	W_KING, W_QUEEN, W_ROOK, W_BISHOP, W_KNIGHT, W_PAWN,
	B_KING, B_QUEEN, B_ROOK, B_BISHOP, B_KNIGHT, B_PAWN
};

using ChessBoard = std::array<std::array<ChessPiece, 8>, 8>;
using TextureArray = std::array<SDL_Texture*, 12>;
