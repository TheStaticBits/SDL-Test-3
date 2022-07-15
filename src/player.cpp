#include "player.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "constants.h"
#include "environment.h"

Player::Player(Window& window, Environment& env)
	: tex(window, std::string(C::PLAYER_FP)), speed(C::P_NORM_SPEED), offset(0)
{
	// Center player
	tex.setScale(env.getScale());
	tex.getRectRef().x = (window.getSize().x - tex.getRectRef().w) / 2;
	// Set player at 3 quarters of the way down the screen
	tex.getRectRef().y = (window.getSize().y * (3 / 4)) - (tex.getRectRef().h / 2);
}

Player::~Player()
{
	
}

void Player::update(Window& window)
{
	
}

void Player::render(Window& window)
{
	window.render(tex);
}