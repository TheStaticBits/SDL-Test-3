#include "spritesheet.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.h"
#include "window.h"
#include "rect.h"

Spritesheet::Spritesheet(Window& window, const std::string path, const Vect<float> framePSize)
	: tex(window, path),
	  frameSize{ static_cast<uint32_t>(framePSize.x * tex.getRect().w),
	   		     static_cast<uint32_t>(framePSize.y * tex.getRect().h) }
{

}

Spritesheet::Spritesheet()
{
	
}

Spritesheet::~Spritesheet()
{
	
}

void Spritesheet::setScale(const uint32_t scale)
{
	tex.setScale(scale);
}

void Spritesheet::setPos(const Vect<int64_t> pos)
{
	tex.getRect().x = static_cast<float>(pos.x);
	tex.getRect().y = static_cast<float>(pos.y);
}

void Spritesheet::render(Window& window, const uint32_t frameX, const uint32_t frameY)
{
	window.render(tex, Rect<uint32_t>{frameX * frameSize.x, frameY * frameSize.y, frameSize.x, frameSize.y});
}