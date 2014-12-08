#include "Game.h"

Game::Game(Window* window, Board* board) {
	this->mWindow = window;
	this->mBoard = board;

	//TODO: Create initial piece
	//TODO: Create next piece
}

void Game::drawScene() {
	// Draws board
	drawBoard();
	// drawPiece();
}

void Game::drawBoard() {
	mWindow->drawRect(10, 10, 10, 10, Color("red"));
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			mWindow->drawRect(BOARD_X + j * BLOCK_SIZE,
							  BOARD_Y + i * BLOCK_SIZE,
							  BLOCK_SIZE,
							  BLOCK_SIZE,
							  Color("red"));
		}
	}
}

void Game::createNewPiece() {
	//TODO: Set next piece to current piece
	//TODO: Create new next piece
}