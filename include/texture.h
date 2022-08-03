#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "rect.h"
#include "utility.h"
class Window;

class Texture
{
public:
	Texture(Window& window, const std::string path, const Vect<float> pos = { 0, 0 }, const uint32_t scale = 1);
	Texture();
	~Texture();

	void setScale(const uint32_t newScale);
	
	inline SDL_Texture* getTex()  { return tex;  }
	inline Rect<float>& getRect() { return rect; }

	inline Vect<float> getTexSize(const uint32_t scale) const { return (util::getSize(tex) * scale).cast<float>(); }

private:
	SDL_Texture* tex;
	Rect<float> rect; // Including size and position
};