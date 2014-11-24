#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include <SDL.h>

class Entity {
	public:
		Entity(float x = 0.0, float y = 0.0, float w = 0, float h = 0);

		~Entity();

		// Updates objects internal states
		virtual void update(float frameTime) = 0;

		virtual void render(float cameraX, float cameraY) = 0;

		// Checks collision
		bool collidedWith(Entity *other);

		float getX();
		float getY();
		int getWidth();
		int getHeight();

		// Object hitbox
		SDL_Rect* hitbox;
};

#endif __ENTITY_H_INCLUDED__