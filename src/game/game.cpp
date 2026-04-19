#include "game.h"
#include "textures.h"
#include "fen.h"
#include "mouse_handler.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>

void DrawPiece(SDL_Renderer* renderer, TextureArray& textures, ChessPiece& piece, int x, int y) {
	const SDL_FRect dest = { (float)x * CELL_SIZE, (float)y * CELL_SIZE, CELL_SIZE, CELL_SIZE };

	int index = static_cast<int>(piece) - 1;
	SDL_RenderTexture(renderer, textures[index], NULL, &dest);
}

void Game::RenderBoard() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {

			// Draw board texture
			if ((x + y) % 2 == 0) {
				const SDL_FRect rec = { (float)x * CELL_SIZE, (float)y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
				SDL_SetRenderDrawColor(m_renderer, color_a[0], color_a[1], color_a[2], 255);
				SDL_RenderFillRect(m_renderer, &rec);
			}
			else {
				const SDL_FRect rec = { (float)x * CELL_SIZE, (float)y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
				SDL_SetRenderDrawColor(m_renderer, color_b[0], color_b[1], color_b[2], 255);
				SDL_RenderFillRect(m_renderer, &rec);
			}

			// Draw piece texture
			if (board[y][x] != ChessPiece::EMPTY) {
				DrawPiece(m_renderer, textures, board[y][x], x, y);
			}
		}
	}
}

Game::Game(SDL_Renderer* renderer) : m_renderer(renderer)
{
	Init();
}

Game::~Game()
{
	UnloadTextures();
}

void Game::Init()
{
	FENToBoard(STARTING_POS_STR, board);
}

void Game::Update()
{
	MouseHandler::Handle(textures, board);
}

void Game::Render()
{
	RenderBoard();

	MouseHandler::Render(m_renderer);
}

void Game::LoadTextures()
{
	for (size_t i = 0; i < TEXTURES_PATHS.size(); i++) {
		SDL_Texture* tex = IMG_LoadTexture(m_renderer, TEXTURES_PATHS[i]);

		if (!tex) {
			SDL_Log("Error while loading %s: %s", TEXTURES_PATHS[i], SDL_GetError());
		}
		else {
			SDL_Log("Loaded texture: %s", TEXTURES_PATHS[i]);
			textures[i] = tex;
		}
	}
}

void Game::UnloadTextures()
{
	for (auto& tex : textures) {
		SDL_DestroyTexture(tex);
	}
}
