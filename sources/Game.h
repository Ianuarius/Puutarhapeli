#ifndef __GAME_H_DEFINED__
#define __GAME_H_DEFINED__

#include "Window.h"
#include "Board.h"

class Game {
	public:
		Game(Window* window, Board* board);

		void drawScene();
		void createNewPiece();

	private:
		void drawBoard();
		void drawPiece(int x, int y, int rotation);

		Window* mWindow;
		Board* mBoard;
};

#endif //__GAME_H_DEFINED__