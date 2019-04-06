#pragma once

#include "Graphics.h"

class Weapon
{
public:
	Weapon() = default;
	Weapon(Vec2& pos_in, Vec2& vel_in, Color c_in, Rect2& rect);
	void Draw(Graphics& gfx) const;
	void Update(const float dt);
	void CollisionBoundary();
	void Destroy();
	Rect2& GetRect();
protected:
	Vec2 pos;
	Vec2 vel;
	Color c = Colors::Red;
	Rect2 rect;
	bool destroyed = false;
};