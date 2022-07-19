#include "texture.h"

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "rect.h"
#include "window.h"
#include "utility.h"

Texture::Texture(Window& window, const std::string path, const Vect<float> pos, const uint32_t scale)
	: tex(window.loadTex(path)), rect(pos, getTexSize(scale))
{
	
}

Texture::~Texture()
{
	
}

void Texture::setScale(const uint32_t scale)
{
	const Vect<uint32_t> size = util::getSize(tex);
	rect.w = static_cast<float>(size.x * scale);
	rect.h = static_cast<float>(size.y * scale);
}