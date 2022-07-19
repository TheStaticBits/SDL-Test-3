#pragma once

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

	Environment environment;
	Player player;
};