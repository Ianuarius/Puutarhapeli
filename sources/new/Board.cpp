#include "Borad.h"

Board::Board(Piece *pieces, int pScreenHeight) {
	// Get screen width
	mScreenHeight = pScreenHeight;
	
	// Get the pointer to the pieces class
	pieces = pieces;

	// Initialize the board blocks with free positions
	InitBoard();
}

//Fills grid with empty blocks.
void Board::InitBoard() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			mBoard[i][j] = POS_FREE;
		}
	}
}

// Saves piece position
void Board::StorePiece(int X, int Y, int rotation) {
	for (int i1 = X, i2 = 0; i1 < X + PIECE_BLOCKS; i1++, i2++) {
		for (int j1 = Y, j2 = 0; j1 < Y + PIECE_BLOCKS; j1++, j2++) {
			if (pieces->getBlockType(rotation, j2, i2)) {
				// Store only the blocks of the piece that are not empty
				mBoard[i1][j1] = POS_FILLED;
			}
		}
	}
}

bool Board::IsGameOver() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (mBoard[i][0] == POS_FILLED) {
			return true;
		}
	}

	return false;
}

// Delete a line of board by moving all above lines down
void Board::DeleteLine(int Y) {
	for (int i = Y; i > 0; i--) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			mBoard[i][j] = mBoard[i][j-1];
		}
	}
}

void Board::DeletePossibleLines() {
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		int i = 0;

		while (i < BOARD_WIDTH) {
			if (mBoard[i][j] != POS_FILLED) {
				break;
			}

			i++;
		}

		if (i == BOARD_WIDTH) {
			DeleteLine(j);
		}
	}
}

bool Board::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation)
{
	// Checks collision with pieces already stored in the board or the board limits
	// This is just to check the 5x5 blocks of a piece with the appropiate area in the board
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{	
			// Check if the piece is outside the limits of the board
			if (	i1 < 0 			|| 
				i1 > BOARD_WIDTH  - 1	||
				j1 > BOARD_HEIGHT - 1)
			{
				if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
					return 0;		
			}

			// Check if the piece have collisioned with a block already stored in the map
			if (j1 >= 0)	
			{
				if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock (i1, j1))	)
					return false;
			}
		}
	}

	// No collision
	return true;
}

bool Board::IsFreeBlock(int X, int Y) {
	if (mBoard[X][Y] == POS_FREE) {
		return true;
	}

	return false;
}

int Board::GetXPosInPixels(int pos) {
	return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pos * BLOCK_SIZE));
}

int Board::GetYPosInPixels(int pos) {
	return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pos * BLOCK_SIZE));
}