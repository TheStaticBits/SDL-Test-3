#include "environment.h"

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "constants.h"
#include "player.h"

Environment::Environment(Window& window)
	: wall(window, std::string(Consts::WALL_FP)), scale(1)
{
	determineScale(window);
	wall.setScale(scale);
}

Environment::~Environment()
{
	
}

void Environment::render(Window& window, Player& player)
{
	// Left wall
	renderWall(window, player, (window.getSize().x - Consts::TUNNEL_WIDTH * scale) / 2 - static_cast<uint32_t>(wall.getRect().w));
	renderWall(window, player, (window.getSize().x + Consts::TUNNEL_WIDTH * scale) / 2, true);
}

void Environment::determineScale(Window& window)
{
	for (;; scale++)
	{
		Rect<float>& wallSize = wall.getRect();
		
		// If entire tunnel or height does not fit with the scale being tested
		if ((2 * wallSize.w + Consts::TUNNEL_WIDTH) * scale > window.getSize().x || 
			(Consts::MIN_HEIGHT * scale) > window.getSize().y)
		{
			scale--;
			break; // Found the largest scale that fits on screen
		}
	}

	util::log("Set scale to " + std::to_string(scale));
}

void Environment::renderWall(Window& window, Player& player, const uint32_t x, const bool flip)
{
	Rect<int64_t> wallRect = wall.getRect().cast<int64_t>();
	
	const uint32_t yOffset = player.getOffset() % static_cast<int64_t>(wall.getRect().w);
	
	for (int32_t y = static_cast<int32_t>(yOffset) - static_cast<int32_t>(wallRect.h); 
		 y < static_cast<int32_t>(window.getSize().y); 
		 y += static_cast<int32_t>(wallRect.h))
	{
		wall.getRect().x = static_cast<float>(x);
		wall.getRect().y = static_cast<float>(y);
		if (flip) window.render(wall, SDL_FLIP_HORIZONTAL);
		else window.render(wall);
	}
}