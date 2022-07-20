#include "player.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "constants.h"
#include "environment.h"

Player::Player(Window& window, Environment& env)
	: tex(window, std::string(Consts::PLAYER_FP)), speed(Consts::P_NORM_SPEED), offset(0), fOffset(0)
{
	// Center player
	tex.setScale(env.getScale());
	tex.getRect().x = (window.getSize().x - tex.getRect().w) / 2;
	// Set player at 3 quarters of the way down the screen
	tex.getRect().y = (static_cast<float>(window.getSize().y) * 0.75f) - (tex.getRect().h / 2);
}

Player::~Player()
{
	
}

void Player::update(Window& window, Environment& env)
{
	if (window.getSwipeUp())
		speed = Consts::P_SPEEDUP_SPEED;
	else if (window.getSwipeDown())
		speed = Consts::P_SLOWDOWN_SPEED;
	else
		speed = Consts::P_NORM_SPEED;

	fOffset += window.getDeltaTime() * speed * env.getScale();
	offset = static_cast<int64_t>(fOffset);
}

void Player::render(Window& window)
{
	window.render(tex);
}