#ifndef __BOARD_H_DEFINED__
#define __BOARD_H_DEFINED__

#include "Piece.h"

#define BOARD_LINE_WIDTH 1          // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 4                // Width and Height of each block of a piece
#define BOARD_POSITION 215          // Center position of the board from the left of the screen
#define BOARD_WIDTH 75              // Board width in blocks
#define BOARD_HEIGHT 120            // Board height in blocks
#define MIN_VERTICAL_MARGIN 20      // Minimum vertical margin for the board limit     
#define MIN_HORIZONTAL_MARGIN 20    // Minimum horizontal margin for the board limit
#define PIECE_BLOCKS 3              // Number of horizontal and vertical blocks of a matrix piece

class Board {
	public:
		Board                       (Piece *pieces, int pScreenHeight);

		int GetXPosInPixels         (int pos);
		int GetYPosInPixels         (int pos);
		bool IsFreeBlock            (int X, int Y);
		bool IsPossibleMovement     (int X, int Y, int rotation);
		void StorePiece             (int X, int Y, int rotation);
		void DeletePossibleLines    ();
		bool IsGameOver             ();

	private:
		enum { POS_FREE, POS_FILLED };          // POS_FREE = free position of the board; POS_FILLED = filled position of the board
		int mBoard [BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces
		Piece *pieces;
		int mScreenHeight;

		void InitBoard();
		void DeleteLine (int Y);
};

#endif //__BOARD_H_DEFINED__