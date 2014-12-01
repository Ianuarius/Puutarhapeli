#include "Piece.h"

char cPiece[4 /* Rotation */][2 /* Vertical */][2 /* Horizontal */] = 
{
	{ 
		{0, 0},
		{1, 2}
	},
	{ 
		{1, 0},
		{2, 0}
	},
	{ 
		{2, 1},
		{0, 0}
	},
	{ 
		{0, 2},
		{0, 1}
	},
};

int Piece::getBlock(int rotation, int x, int y) {
	return cPiece[rotation][x][y];
}