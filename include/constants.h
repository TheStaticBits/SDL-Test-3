#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace Consts // Constants
{
	constexpr std::string_view WIN_TITLE = "SDL Test 3!!";
	constexpr SDL_Color bgColor = { 0, 25, 174, 255 };
	constexpr bool VSYNC = true;
	constexpr bool LOG_FPS = true;

	// FP stands for File Path
	constexpr std::string_view WALL_FP = "res/wall.png";
	constexpr std::string_view PLAYER_FP = "res/player.png";

	// Player speeds and controls
	constexpr float P_NORM_SPEED = 40.0f;
	constexpr float P_SPEEDUP_SPEED = 60.0f;
	constexpr float P_SLOWDOWN_SPEED = 20.0f;
	constexpr float SCREEN_SWIPE_PERCENT = 0.05f; // Percent of screen player needs to swipe to register

	// Play area/Environment variables
	constexpr uint32_t MIN_HEIGHT = 16 * 14; // Minimum pixel height 
	constexpr uint32_t TUNNEL_WIDTH= 16 * 7; // Gap between walls
}