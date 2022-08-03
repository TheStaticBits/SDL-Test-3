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
	Player(Window& window);
	~Player();

	void update(Window& window, Environment& env);
	void render(Window& window);

	void resize(Window& window, Environment& env);

	inline const int64_t getOffset() const { return offset; }
	inline Texture& getTex() { return tex; }

private:
	Texture tex;
	float speed;
	
	int64_t offset;
	float fOffset;
};