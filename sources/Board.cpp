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
	if (board[y][x] == POS_FREE) {
		return true;
	} else {
		return false;
	}
}

int Board::getPiece(int x, int y) {
	return board[y][x];
}

bool Board::isGameOver() {
	for (int x = 0; x < BOARD_WIDTH; x++) {
		if (board[1][x] != POS_FREE) {
			return board[1][x];
		}
	}

	return false;
}

bool Board::isPossibleMovement(int x, int y, int rotation) {
	for (int i1 = x, i2 = 0; i1 < x + PIECE_SIZE; i1++, i2++) {
		for (int j1 = y, j2 = 0; j1 < y + PIECE_SIZE; j1++, j2++) {

			// Check if the piece is outside the limits of the board
			if (i1 < 0 					|| 
				i1 > BOARD_WIDTH  - 1	||
				j1 > BOARD_HEIGHT - 1)
			{
				if (mPieces->getBlock(rotation, j2, i2) != 0) { 
					return false;
				}
			}

			if (j1 >= 0) {
				if (mPieces->getBlock(rotation, j2, i2) !=0 
					&& !isFreeBlock(i1, j1)) {
						return false;
				}
			}

		}
	}

	return true;
}

void Board::storePiece(int x, int y, int rotation) {
	for (int i1 = x, i2 = 0; i1 < x + PIECE_SIZE; i1++, i2++) {
		for (int j1 = y, j2 = 0; j1 < y + PIECE_SIZE; j1++, j2++) {
			if (mPieces->getBlock(rotation, j2, i2) != 0) {
				board[j1][i1] = mPieces->getBlock(rotation, j2, i2);
			}
		}
	}
}

void Board::deletePossibleLines() {

}