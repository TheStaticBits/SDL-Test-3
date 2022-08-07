#include "environment.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "constants.h"
#include "player.h"
#include "obstacle.h"
#include "utility.h"

Environment::Environment(Window& window, Player& player, const nlohmann::json& gData)
	: wall(window, std::string(Consts::WALL_FP)), scale(1), canSpawn(true)
{
	util::logInfo("Loading obstacles from " + std::string(Consts::OBSTACLE_FP));
	Obstacle::load(window);
	determineScale(window);
	resetWallPos(window);
	
	addObstacle(window, player, gData);
}

Environment::~Environment()
{
	
}

void Environment::update(Window& window, Player& player, const nlohmann::json& gData)
{
	if (obstacles.size() > 0 && obstacles[0].shouldSpawnNew(window, player))
	{
		if (canSpawn)
		{
			addObstacle(window, player, gData);
			canSpawn = false;
		}

		if (obstacles[0].isOffScreen(window, player))
		{
			util::logInfo("Obstacle removed", true);
			obstacles.erase(obstacles.begin());
			canSpawn = true;
		}
	}

	// Update obstacles
	for (Obstacle& obstacle : obstacles)
		obstacle.update(window, player);
}

void Environment::render(Window& window, Player& player)
{
	// Obstacles
	for (Obstacle& obstacle : obstacles)
		obstacle.render(window, player);
	
	// Wall sides fill
	window.drawRect(leftFill, Consts::bgColor);
	window.drawRect(rightFill, Consts::bgColor);

	// Wall Images
	renderWall(window, player, wallLeftX - wall.getRect().w);
	renderWall(window, player, wallRightX, true);
}

void Environment::determineScale(Window& window)
{
	for (scale = 1; ; scale++)
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

	if (scale == 0)
		util::logError("Screen size not supported. Screen size is: " + window.getSize().str());

	util::logInfo("Set scale to " + std::to_string(scale));

	wall.setScale(scale);
}

void Environment::resize(Window& window, Player& player)
{
	for (Obstacle& obstacle : obstacles)
		obstacle.resize(window, player, scale);

	resetWallPos(window);
}

void Environment::resetWallPos(Window& window)
{
	// Wall X positions
	wallLeftX = static_cast<float>((window.getSize().x - Consts::TUNNEL_WIDTH * scale) / 2);
	wallRightX = static_cast<float>((window.getSize().x + Consts::TUNNEL_WIDTH * scale) / 2);

	// Wall sides
	leftFill = { 0.0f, 0.0f, wallLeftX, static_cast<float>(window.getSize().y) };
	rightFill = { wallRightX, 0.0f, static_cast<float>(window.getSize().x) - wallRightX, static_cast<float>(window.getSize().y) };
}

void Environment::addObstacle(Window& window, Player& player, const nlohmann::json& gData)
{
	util::logInfo("Adding obstacle", true);
	const nlohmann::json obstacleData = gData[std::string(Consts::OBSTACLE_DP)];
	obstacles.push_back(Obstacle(window, player, obstacleData[rand() % obstacleData.size()], scale));
}

void Environment::renderWall(Window& window, Player& player, const float x, const bool flip)
{
	Rect<int64_t> wallRect = wall.getRect().cast<int64_t>();
	
	const uint32_t yOffset = player.getOffset() % static_cast<int64_t>(wall.getRect().w);
	
	for (int32_t y = static_cast<int32_t>(yOffset) - static_cast<int32_t>(wallRect.h); 
		 y < static_cast<int32_t>(window.getSize().y); 
		 y += static_cast<int32_t>(wallRect.h))
	{
		wall.getRect().x = x;
		wall.getRect().y = static_cast<float>(y);
		if (flip) window.render(wall, SDL_FLIP_HORIZONTAL);
		else window.render(wall);
	}
}