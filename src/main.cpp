#include "window/window.h"

int main(int argc, char* argv[])
{
	WindowSettings settings{
		"chess",
		800,
		600,
		SDL_WINDOW_RESIZABLE
	};


	Window window{settings};
	return window.Run();
}