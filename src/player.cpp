#include "player.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window.h"
#include "constants.h"
#include "environment.h"

Player::Player(Window& window)
	: tex(window, std::string(Consts::PLAYER_FP)), speed(Consts::P_NORM_SPEED), offset(0), fOffset(0.0f)
{
	
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

void Player::resize(Window& window, Environment& env)
{
	// Center player
	tex.setScale(env.getScale());
	tex.getRect().x = (window.getSize().x - tex.getRect().w) / 2;
	// Set player position on screen
	tex.getRect().y = (static_cast<float>(window.getSize().y) * Consts::P_POS_PERCENT) - (tex.getRect().h / 2);
}