#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window;
class Player;
#include "texture.h"
#include "obstacle.h"

class Environment
{
public:
	Environment(Window& window, Player& player, const nlohmann::json& gData);
	~Environment();

	void update(Window& window, Player& player, const nlohmann::json& gData);
	void render(Window& window, Player& player);
	
	void determineScale(Window& window);
	void resize(Window& window, Player& player);
	
	void addObstacle(Window& window, Player& player, const nlohmann::json& gData);

	inline const uint32_t getScale() { return scale; }

private:
	void renderWall(Window& window, Player& player, const uint32_t x, const bool flip = false);
	
	Texture wall;
	uint32_t scale;
	std::vector<Obstacle> obstacles;

	bool canSpawn;
};