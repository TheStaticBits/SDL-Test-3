#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window;
class Player;
#include "texture.h"

class Environment
{
public:
	Environment(Window& window);
	~Environment();

	void render(Window& window, Player& player);
	void determineScale(Window& window);

	inline const uint32_t getScale() { return scale; }

private:
	void renderWall(Window& window, Player& player, const uint32_t x, const bool flip = false);
	
	Texture wall;
	uint32_t scale;
};