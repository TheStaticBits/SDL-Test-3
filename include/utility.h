#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#include "rect.h"
#include "constants.h"

namespace util
{
	inline void log(const std::string msg)
	{
		SDL_Log("%s", msg.c_str());
		
//#ifdef _DEBUG
//		// Add to log file potentially
//#endif
	}

	inline void logInfo(const std::string msg, const bool verbose = false)
	{
		if (verbose && Consts::LOG_VERBOSE || !verbose)
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

	inline const int64_t abs(int64_t num)
	{
		if (num < 0) num *= -1;
		return num;
	}
}