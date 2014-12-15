#include "Game.h"

Game::Game(Window* window, Board* board) {
	// Seed random
	srand(time(0));

	this->mWindow = window;
	this->mBoard = board;

	// Taustakuva
	background.setRenderer(mWindow->renderer);
	background.loadFromFile("tausta1.png");
	backgroundRect.w = 256;
	backgroundRect.h = 240;
	backgroundRect.x = 0;
	backgroundRect.y = 0;

	//Create initial piece
	currentPiece = Piece(randomNumber(), randomNumber());
	currentPiece.x = (BOARD_WIDTH / 2) - (PIECE_SIZE / 2);
	currentPiece.y = 0;
	currentPiece.rotation = 0;

	//Create next piece
	nextPiece = Piece(randomNumber(), randomNumber());
	nextPiece.x = BOARD_WIDTH + 5;
	nextPiece.y = 0;
	nextPiece.rotation = 0;
}

void Game::drawScene() {
	mWindow->render(&background, &backgroundRect, 0, 0);

	// Draws board
	drawBoard();

	// Draws current piece
	drawPiece(&currentPiece);

	// Draws next piece
	drawPiece(&nextPiece);
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

				case 3: 
					drawColor = Color("yellow");
					break;

				case 4:
					drawColor = Color("magenta");
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
	currentPiece = nextPiece;
	currentPiece.x = (BOARD_WIDTH / 2) - (PIECE_SIZE / 2);
	currentPiece.y = 0;
	currentPiece.rotation = 0;

	//Create new next piece
	nextPiece = Piece(randomNumber(), randomNumber());
	nextPiece.x = BOARD_WIDTH + 5;
	nextPiece.y = 0;
}

void Game::drawPiece(Piece *piece) {
	Color drawColor;

	int x = piece->x;
	int y = piece->y;
	int rotation = piece->rotation;

	int xPos = mBoard->getXPos(x);
	int yPos = mBoard->getYPos(y);

	for (int i = 0; i < PIECE_SIZE; i++) {
		for(int j = 0; j < PIECE_SIZE; j++) {

			switch(piece->getBlock(rotation, i, j)) {
			case 1: 
				drawColor = Color("green");
				break;

			case 2:
				drawColor = Color("blue");
				break;

			case 3: 
				drawColor = Color("yellow");
				break;

			case 4:
				drawColor = Color("magenta");
				break;

			default:
				drawColor = Color("white");
				break;
			}

			if (piece->getBlock(rotation, i, j) != 0) {
				mWindow->drawRect(xPos + (BLOCK_SIZE * j), yPos + (BLOCK_SIZE * i),
								  BLOCK_SIZE, BLOCK_SIZE, drawColor);
			}
		}
	}
}

Piece* Game::getCurrentPiece() {
	return &currentPiece;
}

int Game::randomNumber() {
	return rand() % 4 + 1;
}