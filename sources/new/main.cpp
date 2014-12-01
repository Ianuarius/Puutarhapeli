/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <stdio.h>
#include "SDL.h"
#include "Window.h"
#include "Piece.h"
#include "Borad.h"
#include "Game.h"

int main( int argc, char* args[] )
{
	if (!SDL::init()) {
		printf("SDL initialization failed!");
		return -1;
	}

	Window window(800, 600, "Peli");
	SDL_Event event;
	bool quit = false;

	Piece pieces;
	Board board(&pieces, window.getHeight());
	Game game(&window, &board, &pieces);

	while(!quit) {
		while(SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		// Clear screen
		window.clear();

		game.DrawScene();

		// Refresh screen and cap framerate
		window.refresh();
		window.capFramerate(60);
	}

	SDL::exit();

	return 0;
}