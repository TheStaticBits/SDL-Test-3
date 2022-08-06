#include "window.h"

#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utility.h"
#include "constants.h"
#include "texture.h"
#include "rect.h"

Window::Window()
	: window(NULL), renderer(NULL), 
	  deltaTime(0.0f), lastTime(0),
	  fpsCounter(0), fps(0),
	  swipeUp(false), swipeDown(false),
	  resized(false), quit(false)
{
	SDL_DisplayMode display;
	if (SDL_GetCurrentDisplayMode(0, &display) != 0)
		util::logError("SDL_GetCurrentDisplayMode failed");
	
	size = { static_cast<uint32_t>(display.w), static_cast<uint32_t>(display.h) };

#ifndef WIN32 // MOBILE, only portrait mode
	SDL_SetHint(SDL_HINT_ORIENTATIONS, "Portrait");
#endif

	util::logInfo("Setup window");
	window = SDL_CreateWindow(std::string(Consts::WIN_TITLE).c_str(), 
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  display.w, display.h, 
//#ifdef WIN32
							  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED );
//#else
//							  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_BORDERLESS );
//#endif
	if (window == NULL)
		util::logError("Create Window failed");

	SDL_SetWindowMinimumSize(window, Consts::TUNNEL_WIDTH + 32, Consts::MIN_HEIGHT);
	
	// Setup renderer
	util::logInfo("Setup renderer");
	uint32_t rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
	if (Consts::VSYNC == true) rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_SetRenderDrawColor(renderer, Consts::bgColor.r, Consts::bgColor.g, Consts::bgColor.b, Consts::bgColor.a);
}

Window::~Window()
{
	util::logInfo("Destroying textures");
	for (SDL_Texture*& tex : textures)
		SDL_DestroyTexture(tex);

	util::logInfo("Destroying window");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

SDL_Texture* Window::loadTex(const std::string path)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == NULL)
		util::logError("Load texture at path " + path + " failed");
	
	textures.emplace_back(texture);
		
	return texture;
}

SDL_Texture* Window::createEmptyTex(const uint32_t width, const uint32_t height)
{
	SDL_Texture* texture = NULL;
	texture = SDL_CreateTexture(renderer,
								SDL_PIXELFORMAT_RGBA8888,
								SDL_TEXTUREACCESS_TARGET,
								width, height);
	if (texture == NULL)
		util::logError("Failed to create empty texture");

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	
	textures.emplace_back(texture);

	return texture;
}

void Window::update()
{
	// Present to the screen and clear
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	
	// Update events and deltaTime
	handleEvents();
	updateDeltaTime();
}

void Window::render(Texture& tex)
{
	if (SDL_RenderCopy(renderer, tex.getTex(), NULL, &(tex.getRect().getSDLRect())) != 0)
	{
		util::logError("Failed to render texture at rect " + tex.getRect().str());
		
		// Rendering black square to signify broken texture
		drawRect(tex.getRect(), { 0, 0, 0, 255 });
	}
}

// Maybe not the best use of overloaded functions?
void Window::render(Texture& tex, Rect<uint32_t> src)
{
	if (SDL_RenderCopy(renderer, tex.getTex(), &(src.getSDLRect()), &(tex.getRect().getSDLRect())) != 0)
	{
		util::logError("Failed to render texture with source at rect " + tex.getRect().str());
		drawRect(tex.getRect(), { 0, 0, 0, 255 });
	}
}

void Window::render(Texture& tex, const double angle)
{
	if (SDL_RenderCopyEx(renderer, tex.getTex(), NULL, &(tex.getRect().getSDLRect()), angle, NULL, SDL_FLIP_NONE) != 0)
	{
		util::logError("Failed to render texture with SDL_RenderCopyEx at rect " + tex.getRect().str());
		drawRect(tex.getRect(), { 0, 0, 0, 255 });
	}
}

void Window::render(Texture& tex, const SDL_RendererFlip flip)
{
	if (SDL_RenderCopyEx(renderer, tex.getTex(), NULL, &(tex.getRect().getSDLRect()), 0, NULL, flip) != 0)
	{
		util::logError("Failed to render texture with SDL_RenderCopyEx at rect " + tex.getRect().str());
		drawRect(tex.getRect(), { 0, 0, 0, 255 });
	}
}

void Window::drawRect(Rect<float>& rect, const SDL_Color& color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	
	if (SDL_RenderFillRect(renderer, &rect.getSDLRect()) != 0)
		util::logError("Failed to fill rect " + rect.str());

	SDL_SetRenderDrawColor(renderer, Consts::bgColor.r, Consts::bgColor.g, Consts::bgColor.b, Consts::bgColor.a);
}

const bool Window::isTexValid(Texture& tex)
{
	// See if texture is in textures list
	return std::find(textures.begin(), textures.end(), tex.getTex()) != textures.end();
}

void Window::closeTex(Texture& tex)
{
	SDL_DestroyTexture(tex.getTex());
	textures.erase(std::remove(textures.begin(), textures.end(), tex.getTex()), textures.end());
}

void Window::handleEvents()
{
	resized = false;
	updateMousePos();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			quit = true; break;

		case SDL_WINDOWEVENT:
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				resize(e.window.data1, e.window.data2);
				break;

			case SDL_WINDOWEVENT_MAXIMIZED:
				break;
			}

			break;

		case SDL_RENDER_TARGETS_RESET:
			break; // Add here if needed
		
#ifdef WIN32
		// Inputs
		case SDL_MOUSEBUTTONDOWN:
			swipeOrigin = touchPos;
			touchHeld = true;
			break;
		case SDL_MOUSEBUTTONUP:
			touchHeld = false;
			resetInputs();
			break;
#else	
		// Fingers 
		case SDL_FINGERDOWN:
			util::logInfo("fingerdown");
			touchPos = getTouchVect(e);
			swipeOrigin = touchPos;
			swipeOrigin.print();
			touchHeld = true;
			break;
		
		case SDL_FINGERMOTION:
			touchPos = getTouchVect(e);
			testSwipe();
			break;
		
		case SDL_FINGERUP:
			util::logInfo("fingerup");
			touchPos = getTouchVect(e);
			resetInputs();
			break;
#endif
		}
	}
}

void Window::updateDeltaTime()
{
	// Update deltaTime
	uint32_t currentTime = SDL_GetTicks();

	if ((lastTime % 1000) > (currentTime % 1000)) // Every second this happens once
	{
		fps = fpsCounter;
		fpsCounter = 0;

		if (Consts::LOG_FPS) util::logInfo(std::to_string(fps) + " FPS");
	}
	
	deltaTime = static_cast<float>(currentTime - lastTime) / 1000;
	lastTime = currentTime;
	fpsCounter++;
}

void Window::resize(int32_t width, int32_t height)
{
	resized = true;
	size = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
	SDL_SetWindowSize(window, width, height);
}

Vect<uint32_t> Window::getTouchVect(SDL_Event& e)
{
	return Vect<float>{ e.tfinger.x * static_cast<float>(size.x), e.tfinger.y * static_cast<float>(size.y) }.cast<uint32_t>();
}

void Window::updateMousePos()
{
	Vect<int> getPos;
	SDL_GetMouseState(&getPos.x, &getPos.y);
	touchPos = getPos.cast<uint32_t>();
	
	if (touchHeld) testSwipe();
}

void Window::testSwipe()
{
	const int64_t yMove = abs(static_cast<int64_t>(touchPos.y) - static_cast<int64_t>(swipeOrigin.y));

	// Test if swipe is long enough
	if (yMove < size.y * Consts::SCREEN_SWIPE_PERCENT) { swipeUp = false; swipeDown = false; return; }

	const int64_t xMove = abs(static_cast<int64_t>(touchPos.x) - static_cast<int64_t>(swipeOrigin.x));
	if (xMove > yMove) { swipeUp = false; swipeDown = false; return; } // Make sure player didn't swipe horizontally

	// Activate swipe
	swipeUp = (touchPos.y < swipeOrigin.y);
	swipeDown = !swipeUp;
}

void Window::resetInputs()
{
	touchHeld = false;
	swipeUp = false;
	swipeDown = false;
}