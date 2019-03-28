#pragma once

#include "Vec2.h"
#include "Rect2.h"
#include "Graphics.h"
#include "Keyboard.h"

class Ship
{
public:
	Ship(Vec2& pos_in, Vec2& vel_in, float size, Color c);
	void Draw(Graphics& gfx) const;
	void Update(const Keyboard& kbd, float dt);
private:
	Vec2 pos;
	Vec2 vel;
	float speed;
	Rect2 rect;
	Color c;
};