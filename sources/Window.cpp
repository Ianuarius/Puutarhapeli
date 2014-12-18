#include "Window.h"

Window::Window(int width, int height, std::string title):
	window(nullptr),
	surface(nullptr),
	renderer(nullptr),
	width(width),
	height(height),
	originalWidth(width),
	originalHeight(height),
	isFullscreen(false),
	title(title),
	frameCount(0)
{
	// Calling resize for the first time CREATES a window.
	// Storing it on window-variable
	resize(width, height, title);

	if (!this->window || !this->renderer) {
		printf("Unable to create window or renderer!");
	}

	frameTicks.start();
	framerateTimer.start();

	clear();
	refresh();

	SDL_Delay(10);
}

Window::~Window() {
	destroy();
}

void Window::destroy() {
	if (renderer)	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

void Window::resize(int width, int height, std::string title) {
	destroy();

	SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_FULLSCREEN_DESKTOP,
								&window, &renderer);

	if (!window || !renderer) {
		printf("Unable to create window or renderer!");
		return;
	}

	// Nearest neighbour rendering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_RenderSetLogicalSize(this->renderer, 256, 240);
	

	surface = SDL_GetWindowSurface(window);

	if (!surface) {
		printf("Unable to get surface!");
		return;
	}

	// Set title
	setTitle(title);

	this->width = width;
	this->height = height;
}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

void Window::setTitle(std::string title) {
	if (window) {
		SDL_SetWindowTitle(this->window, title.c_str());
	}
}

void Window::refresh()
{
	SDL_RenderPresent(renderer);
	++frameCount;
}

void Window::clear() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
}

bool Window::toggleFullscreen() {
	// WIP
	return true;
}

int Window::getFramerate() {
	int framerate = frameCount / (framerateTimer.getTicks() / 1000.f);

	if (framerate > 2000000) {
		return 0;
	}

	return framerate;
}

void Window::capFramerate(int framerate) {
	Uint32 ticks = frameTicks.getTicks();

	if (ticks < (1000 / framerate)) {
		SDL_Delay((1000 / framerate) - ticks);
	}

	frameTicks.start();
}

int Window::getDelta() {
	return frameTicks.getTicks();
}

void Window::drawRect(int X, int Y, int W, int H, Color color) {
	SDL_Rect fillRect = { X, Y, W, H };
	SDL_SetRenderDrawColor(renderer, color.r(), color.g(), color.b(), color.a());
	SDL_RenderFillRect(renderer, &fillRect );
}

void Window::loadTexture(Texture *sourceTexture, std::string path) {
	sourceTexture->setRenderer(renderer);
	sourceTexture->loadFromFile(path);
}

void Window::render(Texture *sourceTexture, SDL_Rect *destRect, int x, int y) {
	sourceTexture->setRenderer(renderer);
	sourceTexture->render(x, y, destRect, 0, NULL, SDL_FLIP_NONE);
}