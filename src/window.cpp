#include "window.h"
#include <SDL_image.h>

Window::Window()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		Stop(3);
	}

	auto window_flags = static_cast<SDL_WindowFlags>(
		SDL_WINDOW_RESIZABLE
	);

	window = SDL_CreateWindow("chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, window_flags);
	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		Stop(3);
	}

	auto renderer_flags = static_cast<SDL_RendererFlags>(
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		Stop(3);
	}
}

Window::~Window()
{
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
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		is_running = false;
	}
	else if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) is_running = false;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_Log("X %i Y %i", event.motion.x, event.motion.y);
	}
}

void Window::Render()
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Window::Stop(int code)
{
	exit_code = code;
	is_running = false;
}
