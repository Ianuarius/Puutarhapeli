#include "game.h"

Game::Game() {
	gWindow = NULL;
	gRenderer = NULL;

	countedFrames = 0;
	currentFrameTime = SDL_GetTicks();

	fpsTimer.start();
}

Game::~Game() {
	//Free loaded images
	//gPlayerTexture.free();
	//gCrosshair.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Game::init() {
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Tasohyppelypeli", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;

				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

SDL_Renderer* Game::getRenderer() {
	return gRenderer;
}

void Game::updateScreen() {
	SDL_RenderPresent(gRenderer);
	++countedFrames;
}

void Game::clearScreen() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

float Game::getFrametime() {
	lastFrameTime = currentFrameTime;
	currentFrameTime = SDL_GetTicks();
	
	return (currentFrameTime - lastFrameTime) / 1000.0f;
}

float Game::calcFPS() {
	capTimer.start();

	float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000) {
		avgFPS = 0;
	}

	return avgFPS;
}

void Game::capFrameRate(int framerate) {
	int frameTicks = capTimer.getTicks();
	int ticksPerFrame = 1000 / framerate;

	// If frame finished early, cap framerate
	if (frameTicks < ticksPerFrame) {
		SDL_Delay(ticksPerFrame - frameTicks);
	}
}