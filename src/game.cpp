#include "game.h"

#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <nlohmann/json.hpp>

#include "utility.h"
#include "constants.h"

Game::Game()
	: gData(nlohmann::json::parse(std::ifstream(std::string(Consts::DATA_FP)))), // Load JSON from DATA_FP string_view
	  player(window), environment(window, player, gData)
{
	player.resize(window, environment);
	srand(static_cast<unsigned int>(time(NULL))); // Set seed for random events
}

Game::~Game()
{
	util::logInfo("Quitting SDL");
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

const bool Game::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) { util::logError("SDL failed to initialize"); return false; }
	if (!IMG_Init(IMG_INIT_PNG)) { util::logError("SDL_image failed to initialize"); return false; }
	if (TTF_Init() == -1) { util::logError("SDL_ttf failed to initialize"); return false; }
	
	return true; // Success!
}

void Game::start()
{
	while (!window.closed()) iteration();
}

void Game::iteration()
{
	window.update();
	player.update(window, environment);
	environment.update(window, player, gData);

	if (window.getResized())
	{
		// Resize environment
		environment.determineScale(window);
		player.resize(window, environment);
	}
	
	environment.render(window, player);
	player.render(window);
}