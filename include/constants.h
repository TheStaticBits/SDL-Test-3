#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace Consts // Constants
{
	// Debugging
	constexpr bool LOG_VERBOSE = true;
	constexpr bool LOG_FPS = true;

	constexpr std::string_view WIN_TITLE = "SDL Test 3!!";
	constexpr SDL_Color bgColor = { 0, 25, 174, 255 };
	constexpr bool VSYNC = true;

	// FP stands for File Path
	constexpr std::string_view WALL_FP = "res/wall.png";
	constexpr std::string_view PLAYER_FP = "res/player.png";
	constexpr std::string_view OBSTACLE_FP = "res/obstacle.png";

	constexpr std::string_view DATA_FP = "res/data.json";

	// Player speeds and controls and more
	constexpr float P_NORM_SPEED = 40.0f;
	constexpr float P_SPEEDUP_SPEED = 60.0f;
	constexpr float P_SLOWDOWN_SPEED = 20.0f;
	constexpr float SCREEN_SWIPE_PERCENT = 0.02f; // Percent of screen player needs to swipe to register
	constexpr float P_POS_PERCENT = 0.75f;

	// Play area/environment variables
	constexpr uint32_t MIN_HEIGHT = 16 * 14;  // Minimum pixel height 
	constexpr uint32_t TUNNEL_WIDTH = 16 * 7; // Gap between walls
	constexpr uint32_t OBSTACLE_GAP = 16 * 8; // Gap between obstacles spawning (needs to be at least half of MIN_HEIGHT)

	// data.json layout strings, DP stands for Data Path
	constexpr std::string_view OBSTACLE_DP = "obstacles";
}