#pragma once

#include "objects.h"
#include <SDL3/SDL.h>
#include <array>

inline const std::array<const char*, 12> TEXTURES_PATHS = {
	"res/king.png",
	"res/queen.png",
	"res/rook.png",
	"res/bishop.png",
	"res/knight.png",
	"res/pawn.png",

	"res/b_king.png",
	"res/b_queen.png",
	"res/b_rook.png",
	"res/b_bishop.png",
	"res/b_knight.png",
	"res/b_pawn.png"
};