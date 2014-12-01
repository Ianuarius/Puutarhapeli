#ifndef __GAME_H_DEFINED__
#define __GAME_H_DEFINED__

#include "Window.h"
#include "Borad.h"
#include "Piece.h"
#include "Color.h"

class Game
{
	public:
		Game(Window* window, Board* board, Piece* pieces);

		void DrawScene();
		void CreateNewPiece();

		int posX, posY;
		int piece, rotation;

	private:
		int mScreenHeight;
		int nextPosX, nextPosY;
		int nextPiece, nextRotation;

		Window* mWindow;
		Board* mBoard;
		Piece* mPieces;

		void InitGame();
		void DrawPiece(int X, int Y, int rotation);
		void DrawBoard();
};

#endif //__GAME_H_DEFINED__