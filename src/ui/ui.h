#pragma once

#include <SDL3/SDL_render.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <imgui.h>
#include "../game/fen.h"

class UI
{
public:
	UI() {};
	UI(SDL_Window* window, SDL_Renderer* renderer);
	~UI() {};

	void Update(SDL_Event* event);
	void Build(ChessBoard& board);
	void Render();

	void HandleColors(int(&color_a)[3], int(&color_b)[3]);
	void HandelCellSize(int& cell_size);

private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_renderer = NULL;

	char input_FEN_str[128] = "";
	std::string output_FEN_str = "";

	float color_a[3] = { 1.0f, 1.0f, 1.0f };
	float color_b[3] = { 0.478431f, 0.337255f, 0.196078f };

	int cell_size = 50;
};