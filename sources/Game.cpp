#include "Game.h"

Game::Game(Window* window, Board* board) {
	this->mWindow = window;
	this->mBoard = board;
	pieceX = (BOARD_WIDTH / 2) - (PIECE_SIZE / 2);
	pieceY = 0;
	rotation = 0;

	//TODO: Create initial piece
	//TODO: Create next piece
}

void Game::drawScene() {
	// Draws board
	drawBoard();
	drawPiece(pieceX, pieceY, rotation);
}

void Game::drawBoard() {
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

void Game::drawPiece(int x, int y, int rotation) {
	Color drawColor;

	int xPos = mBoard->getXPos(x);
	int yPos = mBoard->getYPos(y);

	for (int i = 0; i < PIECE_SIZE; i++) {
		for(int j = 0; j < PIECE_SIZE; j++) {

			switch(mPiece.getBlock(rotation, i, j)) {
			case 1: 
				drawColor = Color("green");
				break;

			case 2:
				drawColor = Color("blue");
				break;

			default:
				drawColor = Color("white");
				break;
			}

			if (mPiece.getBlock(rotation, i, j) != 0) {
				mWindow->drawRect(xPos + (BLOCK_SIZE * j), yPos + (BLOCK_SIZE * i),
								  BLOCK_SIZE, BLOCK_SIZE, drawColor);
			}
		}
	}
}