#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "rect.h"
class Texture;

class Window
{
public:
	Window();
	~Window();

	void update();

	SDL_Texture* loadTex(const std::string path);
	SDL_Texture* createEmptyTex(const uint32_t width, const uint32_t height);

	// Rendering functions
	void render(Texture& tex);
	void render(Texture& tex, const SDL_Rect src); // With source rect
	void render(Texture& tex, const double angle); // Angle
	void render(Texture& tex, const SDL_RendererFlip flip); // Render flip
	void drawRect(Rect<float>& rect, const SDL_Color& color);

	// Getters!
	inline const float getDeltaTime() const { return deltaTime; }
	inline const bool closed() const { return quit; }

	Vect<uint32_t>& getSize() { return size; }

	inline const bool getTouchHeld() const { return touchHeld; }
	inline Vect<uint32_t>& getTouchPos() { return touchPos; }
	
private:
	void handleEvents();
	void updateDeltaTime();

	void resize(int32_t width, int32_t height);

	void updateTouchPos(SDL_Event& e);
	void updateMousePos();

	SDL_Window* window;
	SDL_Renderer* renderer;
	
	Vect<uint32_t> size;
	
	std::vector<SDL_Texture*> textures;

	float deltaTime;
	uint32_t lastTime;
	uint32_t fpsCounter;
	uint32_t fps;

	bool touchHeld;
	Vect<uint32_t> touchPos; 

	bool quit;
};