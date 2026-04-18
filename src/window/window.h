#pragma once

#include <SDL3/SDL.h>
#include "../ui/ui.h"
#include "../game/game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class Window
{
public:
	Window();
	~Window();

	int Run();

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Event event;

	bool is_running = true;
	void Update();
	void Render();

	int exit_code{ 0 };
	void Stop(int code);

	UI ui;
	Game game;
};