#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window;
#include "texture.h"
#include "rect.h"

class Spritesheet
{
public:
	Spritesheet(Window& window, const std::string path, const Vect<float> framePSize);
	Spritesheet();
	~Spritesheet();

	void setScale(const uint32_t scale);
	void setPos(const Vect<int64_t> pos);

	Texture& getTexture() { return tex; }
	Vect<uint32_t>& getSize() { return frameSize; }

	void render(Window& window, const uint32_t frameX = 0, const uint32_t frameY = 0);

private:
	Texture tex;
	Vect<uint32_t> frameSize;
};