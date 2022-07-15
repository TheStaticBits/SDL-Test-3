#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#include "rect.h"

namespace util
{
	inline void log(const std::string msg)
	{
		SDL_Log("%s", msg.c_str());
		
//#ifdef _DEBUG
//		// Add to log file potentially
//#endif
	}

	inline void logInfo(const std::string msg)
	{
		log("[INFO]: " + msg);
	}
	
	inline void logError(const std::string msg)
	{
		log("[ERROR]: " + msg + " (" + SDL_GetError() + ")");
	}

	inline Vect<uint32_t> getSize(SDL_Texture* texture)
	{
		Vect<int> result(0, 0);
		SDL_QueryTexture(texture, NULL, NULL, &result.x, &result.y);
		return result.cast<uint32_t>();
	}
}