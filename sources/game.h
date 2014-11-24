#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

// Dependencies
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "LTimer.h"

// Game class
class Game {
	public:
		// Constants
		static const int SCREEN_WIDTH = 1280;
		static const int SCREEN_HEIGHT = 720;

		// Constructor - Initialize variables
		Game();

		// Destructor - Deallocate memory
		~Game();

		// Initializes SDL and the game
		bool init();

		// Get SDL_Renderer object
		SDL_Renderer* getRenderer();

		// Clears screen
		void clearScreen();

		// Updates screen
		void updateScreen();

		// Caps framerate - you MUST use calcFPS() before capping framerate
		void capFrameRate(int framerate);

		// Get last frametime
		float getFrametime();

		// Calculates FPS
		float calcFPS();

	private:
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;

		int countedFrames;
		Uint32 lastFrameTime, currentFrameTime;
		LTimer fpsTimer, capTimer;
};

#endif __GAME_H_INCLUDED__