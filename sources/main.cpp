/*
 *		Garden of Hell
 */

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

	// Hide cursor
	SDL_ShowCursor(SDL_DISABLE);

	// Window related
	Window window(800, 600, "Puutarhapeli");
	SDL_Event event;
	bool quit = false;
	Timer gameTimer;
	gameTimer.start();

	// Fonts
	Texture levelText, levelTextShadow;
	SDL_Color white = {255, 255, 255};
	SDL_Color black = {0, 0, 0};

	levelText.setRenderer(window.renderer);
	levelTextShadow.setRenderer(window.renderer);

	// Game related
	Board board(&window);
	Game game(&window, &board);
	Piece* currentPiece = game.getCurrentPiece();
	board.setCurrentPiece(currentPiece);

	int virusCount = 10;
	int level = 10;

	// SPLOSOON
	Texture explo;
	window.loadTexture(&explo, "explosion3.png");
	
	Sprite explosionAnim(&window, &explo, explo.getWidth()/5, explo.getHeight(), 5, 6);
	explosionAnim.play(0, 1);


	// Pate!
	Texture pate;
	window.loadTexture(&pate, "pate-framet.png");
	Sprite throwAnimation(&window, &pate, pate.getWidth()/3, pate.getHeight(), 3, 6);

	game.spawnVirus(virusCount, level);

	while(!quit) {
		Piece* currentPiece = game.getCurrentPiece();
		int rotation = currentPiece->rotation;
		int x = 0;
		Uint32 waitTicks = 750;

		levelText.printText("Level 1", 18, white);
		levelTextShadow.printText("Level 1", 18, black);

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

					case SDLK_ESCAPE:
						exit(0);
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

				if (!game.virusExists()) {
					board.init();
					virusCount++;
					level++;
					game.spawnVirus(virusCount, level/2);
				}

				throwAnimation.play(false, 1);

				game.createNewPiece();
				board.setCurrentPiece(game.getCurrentPiece());
			}
			
			gameTimer.start();
		}

		// Clear screen
		window.clear();

		game.drawScene();

		// Print level text
		levelTextShadow.render(66, 41);
		levelText.render(65, 40);

		explosionAnim.render(100, 100);
		
		throwAnimation.render(222, 81);

		// Refresh screen and cap framerate
		window.refresh();
		window.capFramerate(120);
	}

	SDL::exit();

	return 0;
}