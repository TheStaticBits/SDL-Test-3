#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window;
class Environment;
#include "texture.h"

class Player
{
public:
	Player(Window& window, Environment& env);
	~Player();

	void update(Window& window);
	void render(Window& window);

private:
	Texture tex;
	float speed;
	
	int64_t offset;
};