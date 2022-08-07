#pragma once

#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window;
class Player;
#include "rect.h"
#include "spritesheet.h"

class Obstacle
{
public:
	Obstacle(Window& window, Player& player, const nlohmann::json& data, const uint32_t scale);
	~Obstacle();

	static void load(Window& window);

	void render(Window& window, Player& player);
	void update(Window& window, Player& player);
	void movement(Window& window);
	
	const bool shouldSpawnNew(Window& window, Player& player);
	const bool isOffScreen(Window& window, Player& player);

	void resize(Window& window, Player& player, const uint32_t newScale);

private:

	static Spritesheet tex;

	nlohmann::json data;
	std::unordered_map<uint32_t, Rect<float>> walls;

	int64_t pOffset; // Offset from player
	int64_t height;
	int64_t distFromPlayer;
	uint32_t scale;

	// Movement variables
	float xOffset; // x offset of obstacle from the center
	int8_t direction; // Either 1 or -1, the direction that the object is moving in.
};