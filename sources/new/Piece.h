#ifndef __PIECE_H_DEFINED__
#define __PIECE_H_DEFINED__

class Piece {
	public:
		int getBlockType(int rotation, int X, int Y);
		int getXInitialPosition(int rotation);
		int getYInitialPosition(int rotation);
};

#endif // __PIECE_H_DEFINED__