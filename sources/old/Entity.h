#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"

class Entity {
	public:
		// Object hitbox
		SDL_Rect hitbox;

		Entity(float x = 0.0, float y = 0.0, float w = 0, float h = 0);

		~Entity();

		// Updates objects internal states
		void update(float frameTime);

		void render(float cameraX, float cameraY);

		// Checks collision
		//bool collidedWith(Entity *other);

		float getX();
		float getY();
		int getWidth();
		int getHeight();

		void setTexture(LTexture* t);

	private:
		LTexture* texture;
};

#endif __ENTITY_H_INCLUDED__