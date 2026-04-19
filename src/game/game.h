#pragma once

#include "objects.h"
#include <SDL3/SDL_render.h>
#include <array>

class Game
{
public:
	Game() {};
	Game(SDL_Renderer* renderer);
	~Game();

	void Init();

	void Update();
	void Render();
	void RenderBoard();

	void LoadTextures();
	void UnloadTextures();

	ChessBoard board{};
	int color_a[3];
	int color_b[3];

	int cell_size = 50;

private:
	SDL_Renderer* m_renderer = nullptr;

	TextureArray textures{};
};

SDL_Texture* GetTextureFromPiece(TextureArray& textures, ChessPiece& piece);