#pragma once

#include "objects.h"
#include <SDL3/SDL_render.h>
#include <array>

#define CELL_SIZE 50

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

private:
	SDL_Renderer* m_renderer = nullptr;

	TextureArray textures{};
};

SDL_Texture* GetTextureFromPiece(TextureArray& textures, ChessPiece& piece);