#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "Rect2.h"

class Asteroid
{
	// Position is stored in terms of screen coordinates of top left corner
public:
	Asteroid(Vec2& pos, Vec2& vel, int asteroid_no);
	void Draw(Graphics& gfx) const;
private:
	int asteroid_no;
	static constexpr int no_asteroid_types = 2;
	float width[no_asteroid_types] = { 50, 40 };
	float height[no_asteroid_types] = { 50, 55 };
	Vec2 pos;
	Vec2 vel;
	Rect2 rect;
};