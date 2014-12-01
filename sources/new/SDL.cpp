#include "SDL.h"

bool SDL::init() {
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	/*
	Initialize AUDIO and TFF
	*/

	return success;
}

void SDL::exit() {
	SDL_Quit();
}