#include "Game.h"

Game::Game(Window* window, Board* board, Piece* pieces):
	mWindow(window),
	mBoard(board),
	mPieces(pieces)
{
	mScreenHeight = mWindow->getHeight();
	InitGame();
}

void Game::InitGame() {
	// First piece
	piece = 1;
	rotation = 0;
	posX = (BOARD_WIDTH / 2) + mPieces->getXInitialPosition(rotation);
	posY = mPieces->getYInitialPosition(rotation);

	// Next piece
	nextPiece = 1;
	nextRotation = 0;
	nextPosX = (BOARD_WIDTH + 5);
	nextPosY = 5;
}

void Game::CreateNewPiece() {
	piece = nextPiece;
	rotation = nextRotation;
	posX = (BOARD_WIDTH / 2) + mPieces->getXInitialPosition(rotation);
	posY = mPieces->getYInitialPosition(rotation);

	// Next piece
	nextPiece = 1;
	nextRotation = 0;
}

void Game::DrawPiece(int X, int Y, int rotation) {
	// Color of the block
	std::string color = "black";

	int pixelsX = mBoard->GetXPosInPixels(X);
	int pixelsY = mBoard->GetYPosInPixels(Y);

	for (int i = 0; i < PIECE_BLOCKS; i++) {
		for (int j = 0; j < PIECE_BLOCKS; j++) {
			switch (mPieces->getBlockType(rotation, X, Y))
			{
			case 1:
				color = "green";
				break;

			case 2:
				color = "blue";
				break;
			}

			if (mPieces->getBlockType(rotation, j, i) != 0) {
				mWindow->drawRect(pixelsX + i * BLOCK_SIZE,
								  pixelsY + j * BLOCK_SIZE,
								  (pixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
								  (pixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
								  Color(color));
			}
		}
	}
}

void Game::DrawBoard() {
	// Calculate board limits in pixels
	int x1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int x2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int y =  mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	// Rectangles that delimits the board
	mWindow->drawRect(x1 - BOARD_LINE_WIDTH, y, BOARD_LINE_WIDTH, mScreenHeight -1, Color("blue"));
	mWindow->drawRect(x2, y, BOARD_LINE_WIDTH, mScreenHeight -1, Color("blue"));
	//mWindow->drawRect(x2, y, x2 + BOARD_LINE_WIDTH, mScreenHeight -1, Color("blue"));

	// Draw blocks that are already stored in the board
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (!mBoard->IsFreeBlock(i, j)) {
				mWindow->drawRect(x1 + i * BLOCK_SIZE,
								  y + j * BLOCK_SIZE,
								  (x1 + i * BLOCK_SIZE) + BLOCK_SIZE -1,
								  (y + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
								  Color("red"));
			}
		}
	}
}

void Game::DrawScene() {
	// Draw board
	DrawBoard();

	// Draw current piece
	//DrawPiece(posX, posY, rotation);
	
	// Show next piece at the side
	//DrawPiece(nextPosX, nextPosY, nextRotation);
}