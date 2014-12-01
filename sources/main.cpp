/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <stdio.h>
#include "SDL.h"
#include "Window.h"
#include "Piece.h"
#include "Board.h"
#include "Game.h"

int main(int argc, char* args[])
{
	// SDL init
	if (!SDL::init()) {
		printf("SDL initialization failed!");
		return -1;
	}

	// Window related
	Window window(800, 600, "Puutarhapeli");
	SDL_Event event;
	bool quit = false;

	// Game related
	Piece piece;
	Board board(&piece, &window);
	Game game(&window, &board);

	while(!quit) {
		while(SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		// Clear screen
		window.clear();

		game.drawScene();

		// Refresh screen and cap framerate
		window.refresh();
		window.capFramerate(60);
	}

	SDL::exit();

	return 0;
}