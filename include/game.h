#pragma once

#include "window.h"

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
};