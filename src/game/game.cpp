#include "game.h"
#include "textures.h"
#include "fen.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>

#define COL_WHITE 255, 255, 255, 255
#define COL_BROWN 122, 86,  50,  255

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
				SDL_SetRenderDrawColor(m_renderer, COL_WHITE);
				SDL_RenderFillRect(m_renderer, &rec);
			}
			else {
				const SDL_FRect rec = { (float)x * CELL_SIZE, (float)y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
				SDL_SetRenderDrawColor(m_renderer, COL_BROWN);
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

// Required for dragging and dropping pieces
// TODO: refactor
bool is_piece_being_dragged = false;
SDL_Texture* selected_piece_tex = nullptr;
ChessPiece selected_piece = EMPTY;
float m_x, m_y;
bool left_held = false;

SDL_Texture* GetTextureFromPiece(TextureArray& textures, ChessPiece& piece)
{
	int index = static_cast<int>(piece) - 1;
	return textures[index];
}

inline bool IsInBounds(int x, int y) {
	return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

void Game::Update()
{
	Uint32 buttons = SDL_GetMouseState(&m_x, &m_y);
	left_held = (buttons & SDL_BUTTON_LMASK);

	if (left_held && !is_piece_being_dragged) {
		int board_x = m_x / CELL_SIZE;
		int board_y = m_y / CELL_SIZE;

		if (!IsInBounds(board_x, board_y)) return;

		SDL_Log("Cell pos: %i %i", board_x, board_y);

		selected_piece = board[board_y][board_x];
		if (selected_piece == EMPTY) return;

		// Get piece texture
		selected_piece_tex = GetTextureFromPiece(textures, board[board_y][board_x]);
		is_piece_being_dragged = true;

		// Remove the selected texture piece from the board
		board[board_y][board_x] = EMPTY;
	}
	else if (!left_held && is_piece_being_dragged) {
		int board_x = m_x / CELL_SIZE;
		int board_y = m_y / CELL_SIZE;

		if (!IsInBounds(board_x, board_y)) return;

		// Check the if the selected piece is colliding
		ChessPiece piece = board[board_y][board_x];
		if (piece != EMPTY) return;

		board[board_y][board_x] = selected_piece;

		// Reset selected piece data
		selected_piece_tex = nullptr;
		is_piece_being_dragged = false;
	}
}

void Game::Render()
{
	RenderBoard();

	if (is_piece_being_dragged && selected_piece_tex != nullptr) {
		const SDL_FRect dest = { m_x - CELL_SIZE / 2, m_y - CELL_SIZE / 2, CELL_SIZE, CELL_SIZE };
		SDL_RenderTexture(m_renderer, selected_piece_tex, NULL, &dest);
	}
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
