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

private:
	SDL_Renderer* m_renderer = nullptr;

	ChessBoard board{};
	TextureArray textures{};
};

SDL_Texture* GetTextureFromPiece(TextureArray& textures, ChessPiece& piece);