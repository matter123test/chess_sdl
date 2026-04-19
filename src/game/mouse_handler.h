#pragma 

#include "game.h"

namespace MouseHandler {
	void Handle(TextureArray& textures, ChessBoard& board, int cell_size);
	void Render(SDL_Renderer* renderer, int cell_size);
}