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
	Texture(Window& window, const std::string path, const Vect<float> pos, const uint32_t scale = 1);
	~Texture();
	
	inline SDL_Texture* getTex() { return tex; }
	inline const Rect<float> getRect() { return rect; }
	inline Rect<float>& getRectRef() { return rect; }

	inline Vect<float> getTexSize() { return util::getSize(tex).cast<float>(); }

private:
	SDL_Texture* tex;
	Rect<float> rect; // Including size and position
	
	const uint32_t scale;
};