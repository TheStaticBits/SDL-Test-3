#pragma once

#include <nlohmann/json.hpp>

#include "window.h"
#include "environment.h"
#include "player.h"

class Game
{
public:
	Game();
	~Game();
	
	static const bool init();
	
	void start();
	void iteration();

private:
	Window window;

	nlohmann::json gData;

	Player player;
	Environment environment;
};