#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "Rect2.h"
#include <random>

class SpriteCodex
{
public:
	static void DrawShip(const Vec2& topLeft, Graphics& gfx);
	static void DrawAsteroid0(const Vec2& topLeft, Graphics& gfx);
	static void DrawAsteroid0Spawn(const Vec2& topLeft, Graphics& gfx);
	static void DrawAsteroid1(const Vec2& topLeft, Graphics& gfx);
	static void DrawStars(Graphics& gfx, int x, int y);
};