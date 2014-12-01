#include "game.h"
#include "LTexture.h"
#include "Entity.h"

int main(int argc, char* args[]) {
	// Peli
	Game peli;

	// FPS
	float FPS = 0;

	// Peli p‰‰ll‰ / ei
	bool quit = false;

	// Eventit
	SDL_Event event;

	// Renderer
	SDL_Renderer* renderer;

	// Tekstuuri
	LTexture tekstuuri;

	// Entiteetti
	Entity siemen(8, 8, 6, 14);
	int y = 10;

	// Alustetaan SDL
	if (!peli.init()) {
		printf("SDL Init failed!");
		return -1;
	}

	renderer = peli.getRenderer();
	tekstuuri.setRenderer(renderer);

	// SNES RESO!
	SDL_RenderSetLogicalSize(renderer, 256, 240);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	// Annetaan siemenelle siemenen tekstuuri :3
	tekstuuri.loadFromFile("siemen.png");
	siemen.setTexture(&tekstuuri);

	// Main loop
	while(!quit) {
		FPS = peli.calcFPS();

		printf("FPS: %f\n", FPS);

		// Event handling
		while(SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		// Puhistaa ruudun
		peli.clearScreen();

		// Piirret‰‰n asiat
		siemen.render(10, y);

		// P‰ivitet‰‰n ruutu
		peli.updateScreen();
		y++;

		// Rajotetaan FPS
		peli.capFrameRate(60);

	} // (Main loop)

	// Lopetetaan ohjelma
	return 0;
}