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
#include "Texture.h"
#include "Sprite.h"

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
	Board board(&window);
	Game game(&window, &board);
	Piece* currentPiece = game.getCurrentPiece();
	board.setCurrentPiece(currentPiece);

	// Pate!
	Texture pate;
	window.loadTexture(&pate, "pate-framet.png");
	Sprite throwAnimation(&window, &pate, pate.getWidth()/3, pate.getHeight(), 3, 6);

	game.spawnVirus(5, 4);

	while(!quit) {
		Piece* currentPiece = game.getCurrentPiece();
		int rotation = currentPiece->rotation;
		int x = 0;
		Uint32 waitTicks = 1000;

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
						waitTicks = 5;
						break;

					case SDLK_SPACE:
						rotation = (rotation + 1) % 4;
						break;

					default:
						break;
				}
			}
		}

		if (board.isPossibleMovement(currentPiece->x + x, currentPiece->y, rotation)) {
			currentPiece->x += x;
			currentPiece->rotation = rotation;
		}

		if (gameTimer.getTicks() > waitTicks) {
			if (board.isPossibleMovement(currentPiece->x, currentPiece->y+1, currentPiece->rotation)) {
				currentPiece->y++;
			} else {
				board.storePiece();

				if (board.isGameOver()) {
					exit(0);
				}

				board.deletePossibleLines();

				throwAnimation.play(false, 1);

				game.createNewPiece();
				board.setCurrentPiece(game.getCurrentPiece());
			}
			
			gameTimer.start();
		}

		// Clear screen
		window.clear();

		game.drawScene();

		throwAnimation.render(150, 10);

		// Refresh screen and cap framerate
		window.refresh();
		window.capFramerate(60);
	}

	SDL::exit();

	return 0;
}