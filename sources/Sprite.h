#ifndef __SPRITE_H_INCLUDED__
#define __SPRITE_H_INCLUDED__

#include <vector>
#include "LTexture.h"

class Sprite {
	public:
		// Constructor
		Sprite();

		// Destructor
		~Sprite();

		// Creates sprite from file. Assumes each frame to be same size.
		void create(std::string path, int width, int height, int frames);

		// Used for manually adding frames.
		void addFrame(int x, int y, int width, int height);

		// Gets texture object
		void setRenderer(SDL_Renderer* Renderer);

		// Set sprite framerate
		void setFramerate(int fps);

		// Render sprite
		void Sprite::render(int xPos, int yPos, float frameTime);


	private:
		LTexture gSpriteSheet;
		
		std::vector<SDL_Rect> gSpriteClips;

		int frameCount, currentFrame, width, height;
		float currentFrameTime, frameRate;
};

#endif __SPRITE_H_INCLUDED__