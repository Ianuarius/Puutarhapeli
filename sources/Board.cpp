#include "Board.h"

Board::Board(Piece *pieces, Window *window) {
	mPieces = pieces;

	mWindow = window;

	init();
}

void Board::init() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			board[i][j] = POS_FREE;
		}
	}
}

int Board::getXPos(int position) {
	return BOARD_X + (BLOCK_SIZE * position);
}

int Board::getYPos(int position) {
	return BOARD_Y + (BLOCK_SIZE * position);
}

bool Board::isFreeBlock(int x, int y) {
	if (board[x][y] == POS_FREE) {
		return true;
	} else {
		return false;
	}
}

bool Board::isGameOver() {
	for (int x = 0; x < BOARD_WIDTH; x++) {
		if (board[x][0] == POS_FILLED) {
			return true;
		}
	}

	return false;
}