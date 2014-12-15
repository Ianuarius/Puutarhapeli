#ifndef __GAME_H_DEFINED__
#define __GAME_H_DEFINED__

#include "Window.h"
#include "Board.h"
#include "Piece.h"
#include "Color.h"
#include "Texture.h"
#include <time.h>

class Game {
	public:
		Game(Window* window, Board* board);

		void drawScene();
		void createNewPiece();
		Piece* getCurrentPiece();

	private:
		void drawBoard();
		void drawPiece(Piece *piece);

		int randomNumber();

		Window* mWindow;
		Board* mBoard;
		Piece currentPiece, nextPiece;

		Texture background;
		SDL_Rect backgroundRect;
};

#endif //__GAME_H_DEFINED__