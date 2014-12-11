/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <stdio.h>
#include "SDL.h"
#include "Window.h"
#include "Piece.h"
#include "Board.h"
#include "Game.h"
#include "Timer.h"

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
	Timer gameTimer;
	gameTimer.start();

	// Game related
	Piece piece;
	Board board(&piece, &window);
	Game game(&window, &board);

	while(!quit) {
		int x = 0;
		int rotation = game.rotation;
		int waitTicks = 1000;

		while(SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
					case SDLK_LEFT:
						x--;
						break;

					case SDLK_RIGHT:
						x++;
						break;

					case SDLK_DOWN:
						waitTicks = 50;
						break;

					case SDLK_SPACE:
						rotation = (rotation + 1) % 4;
						break;

					default:
						break;
				}
			}
		}

		if (board.isPossibleMovement(game.pieceX + x, game.pieceY, rotation)) {
			game.pieceX += x;
			game.rotation = rotation;
		}

		if (gameTimer.getTicks() > waitTicks) {
			if (board.isPossibleMovement(game.pieceX, game.pieceY+1, game.rotation)) {
				game.pieceY++;
			} else {
				board.storePiece(game.pieceX, game.pieceY, game.rotation);

				if (board.isGameOver()) {
					exit(0);
				}

				game.createNewPiece();
			}
			
			gameTimer.start();
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