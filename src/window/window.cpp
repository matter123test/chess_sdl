#include "window.h"

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

Window::Window()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		Stop(3);
	}

	auto window_flags = static_cast<SDL_WindowFlags>(
		SDL_WINDOW_RESIZABLE
	);

	window = SDL_CreateWindow("chess", WINDOW_WIDTH, WINDOW_HEIGHT, window_flags);
	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		Stop(3);
	}


	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		Stop(3);
	}

	ui = UI(window, renderer);
	game = Game(renderer);

	game.LoadTextures();
}

Window::~Window()
{
	game.UnloadTextures();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


int Window::Run()
{
	while (is_running) {
		Update();
		Render();
	}

	return exit_code;
}

void Window::Update()
{
	game.Update();

	while (SDL_PollEvent(&event)) {
		ui.Update(&event);

		if (event.type == SDL_EVENT_QUIT) {
			is_running = false;
		}
		else if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_ESCAPE) is_running = false;
		}
	}
}

void Window::Render()
{
	ui.Build(game.board);

	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	game.Render();
	ui.Render();

	SDL_RenderPresent(renderer);
}

void Window::Stop(int code)
{
	exit_code = code;
	is_running = false;
}
