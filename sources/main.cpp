// Class dependencies
#include "game.h"
#include "LTexture.h"
#include "Sprite.h"
#include "Player.h"

// Renderer
SDL_Renderer* gRenderer = NULL;

// Crosshair texture
LTexture gCrosshair;

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	gCrosshair.setRenderer(gRenderer);

	//Load dot texture
	if (!gCrosshair.loadFromFile("crosshair.png"))
	{
		printf("Failed to load crosshair texture!\n");
		success = false;
	}
	return success;
}

int main(int argc, char* args[]) {
	Game game;

	if (!game.init()) {
		printf("Failed to initialize!\n");
		return 1;
	}

	//Event handler
	SDL_Event e;

	// Set renderer and load media
	gRenderer = game.getRenderer();
	loadMedia();

	Player player(gRenderer);

	// Trap cursor
	SDL_SetRelativeMouseMode(SDL_TRUE);	

	// Debugging random vars
	bool quit = false;
	int x, y;
	float fps = 0.0f;

	while (!quit) {
		fps = game.calcFPS();
		float frameTime = game.getFrametime();
		bool keyDown = false;

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		// Quit on ESC
		if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
			quit = true;
		}

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		if (currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_LEFT]) {
			keyDown = true;
			player.move(-5);
		} else if (currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_RIGHT]) {
			keyDown = true;
			player.move(5);
		}

		if (currentKeyStates[SDL_SCANCODE_SPACE]) {
			player.jump();
		}

		//Clear screen
		game.clearScreen();

		player.setFrametime(frameTime);
		player.updatePosition(keyDown);

		// Set crosshair
		SDL_GetMouseState(&x, &y);
		gCrosshair.render(x-16, y-16);

		player.render();

		// Update screen and cap framerate
		game.updateScreen();
		game.capFrameRate(120);
	}

	return 0;
}