#pragma once

#include <SDL3/SDL.h>
#include "../ui/ui.h"
#include "../game/game.h"

struct WindowSettings {
	const char* title;
	int width;
	int height;
	SDL_WindowFlags window_flags;
};

class Window
{
public:
	Window(WindowSettings& settings);
	~Window();

	int Run();

private:
	WindowSettings settings;

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