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