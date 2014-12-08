#ifndef __BOARD_H_DEFINED__
#define __BOARD_H_DEFINED__

#include "Window.h"
#include "Piece.h"

#define BLOCK_SIZE 8		// Block WIDTH and HEIGHT in pixels!

#define BOARD_WIDTH 12		// Board WIDTH in BLOCKS!
#define BOARD_HEIGHT 20		// Board HEIGHT in BLOCKS!
#define BOARD_X 10			// Board X position in PIXELS
#define BOARD_Y 10			// Board Y position in PIXELS

#define PIECE_SIZE 2		

class Board
{
	public:
		Board(Piece *pieces, Window *window);

		int getXPos(int position);	// Returns 'cell' X location in PIXELS
		int getYPos(int position);  // Returns 'cell' Y location in PIXELS

		void storePiece(int x, int y, int rotation);
		bool isFreeBlock(int x, int y);
		bool isPossibleMovement(int x, int y, int rotation);
		bool isGameOver();

		void deletePossibleLines();

	private:
		void init();
		void deleteLine(int y);

		enum { POS_FREE, POS_FILLED };
		int board[BOARD_HEIGHT][BOARD_WIDTH];
		Piece *mPieces;
		Window *mWindow;
};

#endif //__BOARD_H_DEFINED__ 