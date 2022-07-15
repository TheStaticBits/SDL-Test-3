#include "environment.h"

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "constants.h"
#include "player.h"

Environment::Environment(Window& window)
	: wall(window, std::string(C::WALL_FP))
{
	determineScale(window);
	wall.setScale(scale);
}

Environment::~Environment()
{
	
}

void Environment::render(Window& window, Player& player)
{
	
}

void Environment::determineScale(Window& window)
{
	scale = 1;
}