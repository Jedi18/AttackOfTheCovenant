#pragma once

#include "Vec2.h"
#include "Rect2.h"
#include "Graphics.h"

class Ship
{
public:
	void Draw(Graphics& gfx);
private:
	Vec2 pos;
	Vec2 vel;
	Rect2 rect;
};