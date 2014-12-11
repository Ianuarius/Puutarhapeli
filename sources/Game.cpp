#include "Game.h"

Game::Game(Window* window, Board* board) {
	this->mWindow = window;
	this->mBoard = board;


	//Create initial piece
	pieceX = (BOARD_WIDTH / 2) - (PIECE_SIZE / 2);
	pieceY = 0;
	rotation = 0;

	//TODO: Create next piece
	nextPieceX = BOARD_WIDTH + 5;
	nextPieceY = 0;
}

void Game::drawScene() {
	// Draws board
	drawBoard();

	// Draws current piece
	drawPiece(pieceX, pieceY, rotation);

	// Draws next piece
	drawPiece(nextPieceX, nextPieceY, 0);
}

void Game::drawBoard() {
	Color drawColor;

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
				switch(mBoard->getBlock(j, i)) {
				case 1:
					drawColor = Color("green");
					break;

				case 2:
					drawColor = Color("blue");
					break;

				default:
					drawColor = Color("red");
					break;
				}

				mWindow->drawRect(BOARD_X + j * BLOCK_SIZE,
								  BOARD_Y + i * BLOCK_SIZE,
								  BLOCK_SIZE,
								  BLOCK_SIZE,
								  drawColor);
		}
	}
}

void Game::createNewPiece() {
	//Set next piece to current piece
	pieceX = (BOARD_WIDTH / 2) - (PIECE_SIZE / 2);
	pieceY = 0;
	rotation = 0;

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