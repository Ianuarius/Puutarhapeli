#ifndef __BOARD_H_DEFINED__
#define __BOARD_H_DEFINED__

#include "Window.h"
#include "Piece.h"

#define BLOCK_SIZE 8		// Block WIDTH and HEIGHT in pixels!

#define BOARD_WIDTH 10		// Board WIDTH in BLOCKS!
#define BOARD_HEIGHT 15		// Board HEIGHT in BLOCKS!
#define BOARD_X 10			// Board X position in PIXELS
#define BOARD_Y 10			// Board Y position in PIXELS

class Board
{
	public:
		Board(Piece *pieces, Window *window);

	private:
		void init();

		enum { POS_FREE, POS_FILLED };
		int board[BOARD_HEIGHT][BOARD_WIDTH];
		Piece *mPieces;
		Window *mWindow;
};

#endif //__BOARD_H_DEFINED__