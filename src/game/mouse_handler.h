#pragma 

#include "game.h"

namespace MouseHandler {
	void Handle(TextureArray& textures, ChessBoard& board, int &cell_size);
	void Render(SDL_Renderer* renderer, int &cell_size, const bool &show_moves, ChessBoard& board, int* color_c);
	void RenderSelectedPiece(SDL_Renderer* renderer, int& cell_size);
}