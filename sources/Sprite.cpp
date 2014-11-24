#include "Sprite.h"

Sprite::Sprite() {
	frameCount = 0;
	currentFrame = 0;
	frameRate = 0;
	currentFrameTime = 0;

	width = 0;
	height = 0;
}

Sprite::~Sprite() {
	gSpriteSheet.free();
}

void Sprite::create(std::string path, int width, int height, int frames) {
	if (!gSpriteSheet.loadFromFile(path)) {
		printf("Failed to load sprite %s\n", path);
	} else {
		for (int i = 0; i <= frames-1; i++) {
			SDL_Rect tmpSpriteClip;
			tmpSpriteClip.w = width;
			tmpSpriteClip.h = height;

			tmpSpriteClip.x = i * width;
			tmpSpriteClip.y = 0;

			gSpriteClips.push_back(tmpSpriteClip);
		}

		frameCount = gSpriteClips.size();
	}
}

void Sprite::addFrame(int x, int y, int width, int height) {
	SDL_Rect tmpSpriteClip;

	tmpSpriteClip.w = width;
	tmpSpriteClip.h = height;
	tmpSpriteClip.x = x;
	tmpSpriteClip.y = y;

	gSpriteClips.push_back(tmpSpriteClip);

	frameCount = gSpriteClips.size();
}

void Sprite::setRenderer(SDL_Renderer* Renderer) {
	gSpriteSheet.setRenderer(Renderer);
}

void Sprite::setFramerate(int fps) {
	frameRate = fps;
}

void Sprite::render(int xPos, int yPos, float tFrameTime)  {
	currentFrameTime += tFrameTime;
	

	SDL_Rect* currentClip = &gSpriteClips[currentFrame];
	gSpriteSheet.render(xPos, yPos, currentClip);

	if (currentFrameTime >= 1.0f / frameRate) {
		++currentFrame;
		currentFrameTime = 0;

		if (currentFrame >= frameCount) {
			currentFrame = 0;
		}
	}
}