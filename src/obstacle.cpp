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
	: data(data), pOffset(-player.getOffset()), height(0) // Means that the obstacle will be at y = 0 when created
{
	float fScale = static_cast<float>(scale);
	// Finding height of obstacle
	for (uint32_t i = 0; i < data.size(); i++)
	{
		// Read from JSON file data about each object
		walls[i] = Rect<float>{ window.getSize().x / 2 + data[i]["x"].get<float>() * fScale,
								data[i]["y"].get<float>() * fScale,
								data[i]["w"].get<float>() * static_cast<float>(tex.getSize().x) * fScale,
								data[i]["h"].get<float>() * static_cast<float>(tex.getSize().y) * fScale };

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
	tex.getSize().print();
}

void Obstacle::render(Window& window, Player& player)
{
	for (auto& wall : walls)
	{
		Rect<float> renderAt = wall.second;
		renderAt.y += pOffset + player.getOffset();
		
		// Temporary, replace with rendering from spritesheet later
		window.drawRect(renderAt, { 255, 0, 0, 255 });
	}
}

const bool Obstacle::shouldSpawnNew(Window& window, Player& player, const uint32_t scale)
{
	return pOffset + player.getOffset() - height >= Consts::OBSTACLE_GAP * scale;
}

const bool Obstacle::isOffScreen(Window& window, Player& player)
{
	return pOffset + player.getOffset() - height >= window.getSize().y;
}