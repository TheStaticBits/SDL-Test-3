#include "obstacle.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "constants.h"
#include "player.h"

Spritesheet Obstacle::tex = Spritesheet(); // overriden when calling Obstacle::load

Obstacle::Obstacle(Window& window, Player& player, const nlohmann::json& data, const uint32_t scale)
	: data(data), pOffset(-player.getOffset()), // Means that the obstacle will be at y = 0 when created
	  height(0), distFromPlayer(0), scale(scale) 
{
	const nlohmann::json wallData = data["walls"];

	// Finding height of obstacle
	for (uint32_t i = 0; i < wallData.size(); i++)
	{
		// Read from JSON file data about each object
		walls[i] = Rect<float>{ wallData[i]["x"].get<float>(), wallData[i]["y"].get<float>(),
								wallData[i]["w"].get<float>() * static_cast<float>(tex.getSize().x),
								wallData[i]["h"].get<float>() * static_cast<float>(tex.getSize().y) };

		// Direction object sticks out from the center Y position
		int64_t stickOut = abs(static_cast<int64_t>(walls[i].y));
		if (stickOut > height) height = stickOut;
	}
}

Obstacle::~Obstacle()
{

}

void Obstacle::load(Window& window)
{
	tex = Spritesheet(window, std::string(Consts::OBSTACLE_FP), { 0.33f, 0.33f });
}

void Obstacle::render(Window& window, Player& player)
{
	for (auto& wall : walls)
	{
		Rect<float> renderAt = wall.second * static_cast<float>(scale);
		renderAt.x += window.getSize().x / 2;
		renderAt.y += pOffset + player.getOffset();
		
		// Temporary, replace with rendering from spritesheet later
		window.drawRect(renderAt, { 255, 0, 0, 255 });
	}
}

void Obstacle::update(Player& player)
{
	distFromPlayer = static_cast<int64_t>(player.getTex().getRect().y) - (pOffset + player.getOffset()); // Used during resizing
}

const bool Obstacle::shouldSpawnNew(Window& window, Player& player)
{
	return (pOffset + player.getOffset()) - (height * static_cast<float>(scale)) >= (Consts::OBSTACLE_GAP * scale);
}

const bool Obstacle::isOffScreen(Window& window, Player& player)
{
	return (pOffset + player.getOffset()) - (height * static_cast<float>(scale)) >= window.getSize().y;
}

void Obstacle::resize(Window& window, Player& player, const uint32_t newScale)
{
	// New distance between the player and the obstacle
	float newDist = static_cast<float>(distFromPlayer) * (static_cast<float>(newScale) / static_cast<float>(scale));

	// Finding the new offset
	pOffset = static_cast<int64_t>(player.getTex().getRect().y - newDist) - player.getOffset();
	
	scale = newScale;
}