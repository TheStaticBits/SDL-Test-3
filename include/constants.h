#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace C
{
	constexpr std::string_view WIN_TITLE = "SDL Test 3!!";
	constexpr SDL_Color bgColor = { 25, 174, 255, 255 };
	constexpr bool VSYNC = true;
	constexpr bool LOG_FPS = true;

	// FP stands for File Path
	constexpr std::string_view WALL_FP = "res/wall.png";
	constexpr std::string_view PLAYER_FP = "res/player.png";

	// Player speeds
	constexpr float P_NORM_SPEED = 2.5f;
	constexpr float P_SPEADUP_SPEED = 5.0f;

	// Play area variables
	constexpr uint32_t minHeight = 16 * 14; // Minimum pixel height 
	constexpr uint32_t widthGap = 16 * 7; // Gap between walls
}