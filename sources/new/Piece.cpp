#include "Piece.h"

char mPiece[4 /* Rotation */][3 /* Vertical blocks */][3 /* Horizontal blocks */] = 
{
	// 0 degree rotation
	{
		{0, 0, 0},
		{0, 1, 2},
		{0, 0, 0}
	},
	// 90 degree rotation
	{
		{0, 0, 0},
		{0, 1, 0},
		{0, 2, 0}
	},
	// 180 degree rotation
	{
		{0, 0, 0},
		{2, 1, 0},
		{0, 0, 0}
	},
	// 270 degree rotation
	{
		{0, 2, 0},
		{0, 1, 0},
		{0, 0, 0}
	},
};

int Piece::getBlockType(int rotation, int x, int y) {
	return mPiece[rotation][x][y];
}

int Piece::getXInitialPosition(int rotation) {
	return 0;
}
int Piece::getYInitialPosition(int rotation) {
	return 0;
}