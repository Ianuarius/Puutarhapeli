#include "game.h"

int main(int argc, char* args[]) {

	Game peli;

	if (!peli.init()) {
		printf("SDL Init failed!");
		return -1;
	}



	return 0;
}