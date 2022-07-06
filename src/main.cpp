#include <iostream>
#include <SDL2/SDL.h>

#include "game.h"

int main(int argc, char* args[])
{
    if (!Game::init()) return -1;
	
	Game game;
	game.start();
	
    return 0;
}