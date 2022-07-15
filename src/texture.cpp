#include "texture.h"

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "rect.h"
#include "window.h"
#include "utility.h"

Texture::Texture(Window& window, const std::string path, const Vect<float> pos, const uint32_t scale)
	: tex(window.loadTex(path)), rect(pos, getTexSize()), scale(scale)
{
	
}

Texture::~Texture()
{
	
}