#pragma once

#include <iostream>
#include <SDL2/SDL.h>

// Two-member vector
template <typename T>
struct Vect
{
	T x, y;

	Vect() : x(0), y(0) { }
	Vect(T x, T y) : x(x), y(y) { }

	// WARNING: BOILERPLATE AHEAD
	Vect& operator=(const Vect& other) { x = other.x; y = other.y; return *this; }

	Vect& operator+(const T n) { x += n; y += n; return *this; }
	Vect& operator-(const T n) { x -= n; y -= n; return *this; }
	Vect& operator*(const T n) { x *= n; y *= n; return *this; }
	Vect& operator/(const T n) { x /= n; y /= n; return *this; }

	Vect& operator+(const Vect& other) { x += other.x; y += other.y; return *this; }
	Vect& operator-(const Vect& other) { x -= other.x; y -= other.y; return *this; }
	Vect& operator*(const Vect& other) { x *= other.x; y *= other.y; return *this; }
	Vect& operator/(const Vect& other) { x /= other.x; y /= other.y; return *this; }

	Vect& operator+=(const T n) { x += n; y += n; return *this; }
	Vect& operator-=(const T n) { x -= n; y -= n; return *this; }
	Vect& operator*=(const T n) { x *= n; y *= n; return *this; }
	Vect& operator/=(const T n) { x /= n; y /= n; return *this; }

	Vect& operator+=(const Vect& other) { x += other.x; y += other.y; return *this; }
	Vect& operator-=(const Vect& other) { x -= other.x; y -= other.y; return *this; }
	Vect& operator*=(const Vect& other) { x *= other.x; y *= other.y; return *this; }
	Vect& operator/=(const Vect& other) { x /= other.x; y /= other.y; return *this; }

	const bool operator==(const Vect& other) { return x == other.x && y == other.y; }
	const bool operator!=(const Vect& other) { return x != other.x || y != other.y; }
	const bool operator<(const Vect& other)  { return x < other.x&& y < other.y;    }
	const bool operator>(const Vect& other)  { return x > other.x && y > other.y;   }
	const bool operator<=(const Vect& other) { return x <= other.x && y <= other.y; }
	const bool operator>=(const Vect& other) { return x >= other.x && y >= other.y; }

	void print() { SDL_Log(("Vect: (" + std::to_string(x) + ", " + std::to_string(y) + ")").c_str()); }
	
	template<typename U>
	Vect<U> cast() { return Vect<U>{ static_cast<U>(x), static_cast<U>(y) }; }
};

// A wrapper around the SDL Rect object
template <typename T>
struct Rect
{
	T x, y;
	T w, h;
	SDL_Rect sdlRect; // only updated when accessed

	Rect() : x(0), y(0), w(0), h(0) { }
	Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) { }
	Rect(const Vect<T> pos, const Vect<T> size) : x(pos.x), y(pos.y), w(size.x), h(size.y) { }
	
	Rect(T first, T second, const bool isSize = false)
		: x(0), y(0), w(0), h(0)
	{
		if (isSize) { x = first; y = second; }
		else        { w = first; h = second; }
	};

	// moar boilerplate
	inline Rect& operator=(const Rect& other) { x = other.x; y = other.y; w = other.w; h = other.h; return *this; }
	
	inline Rect& operator+(const T n) { x += n; y += n; w += n; h += n; return *this; }
	inline Rect& operator-(const T n) { x -= n; y -= n; w -= n; h -= n; return *this; }
	inline Rect& operator*(const T n) { x *= n; y *= n; w *= n; h *= n; return *this; }
	inline Rect& operator/(const T n) { x /= n; y /= n; w /= n; h /= n; return *this; }

	inline Rect& operator+(const Rect& other) { x += other.x; y += other.y; w += other.w; h += other.h; return *this; }
	inline Rect& operator-(const Rect& other) { x -= other.x; y -= other.y; w -= other.w; h -= other.h; return *this; }
	inline Rect& operator*(const Rect& other) { x *= other.x; y *= other.y; w *= other.w; h *= other.h; return *this; }
	inline Rect& operator/(const Rect& other) { x /= other.x; y /= other.y; w /= other.w; h /= other.h; return *this; }
	
	inline Rect& operator+=(const T n) { x += n; y += n; w += n; h += n; return *this; }
	inline Rect& operator-=(const T n) { x -= n; y -= n; w -= n; h -= n; return *this; }
	inline Rect& operator*=(const T n) { x *= n; y *= n; w *= n; h *= n; return *this; }
	inline Rect& operator/=(const T n) { x /= n; y /= n; w /= n; h /= n; return *this; }

	inline Rect& operator+=(const Rect& other) { x += other.x; y += other.y; w += other.w; h += other.h; return *this; }
	inline Rect& operator-=(const Rect& other) { x -= other.x; y -= other.y; w -= other.w; h -= other.h; return *this; }
	inline Rect& operator*=(const Rect& other) { x *= other.x; y *= other.y; w *= other.w; h *= other.h; return *this; }
	inline Rect& operator/=(const Rect& other) { x /= other.x; y /= other.y; w /= other.w; h /= other.h; return *this; }
	
	inline const bool operator==(const Rect& other) { return x == other.x && y == other.y && w == other.w && h == other.h; }
	inline const bool operator!=(const Rect& other) { return x != other.x || y != other.y || w != other.w || h != other.h; }
	inline const bool operator<(const Rect& other)  { return x < other.x && y < other.y && w < other.w && h < other.h;     }
	inline const bool operator>(const Rect& other)  { return x > other.x && y > other.y && w > other.w && h > other.h;     }
	inline const bool operator<=(const Rect& other) { return x <= other.x && y <= other.y && w <= other.w && h <= other.h; }
	inline const bool operator>=(const Rect& other) { return x >= other.x && y >= other.y && w >= other.w && h >= other.h; }

	inline const std::string str() { return "(" + std::to_string(x) + ", " + 
												  std::to_string(y) + ", " +
												  std::to_string(w) + ", " +
												  std::to_string(h) + ")"; }

	inline void print() { SDL_Log(("Rect: " + str()).c_str()); }
	
	inline SDL_Rect& getSDLRect() 
	{ 
		sdlRect = { static_cast<int>(x), static_cast<int>(y), 
				    static_cast<int>(w), static_cast<int>(h) };
		return sdlRect;
	}
	
	inline void changePos(Vect<T> newPos)   { x = newPos.x; y = newPos.y; }
	inline void changeSize(Vect<T> newSize) { w = newSize.x; h = newSize.y; }
};