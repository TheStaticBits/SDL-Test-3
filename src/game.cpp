#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utility.h"

Game::Game()
	: environment(window),
	  player(window, environment)
{
	
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
	player.update(window);
	
	environment.render(window, player);
	player.render(window);
}