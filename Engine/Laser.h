#pragma once

#include "Graphics.h"

class Laser
{
public:
	Laser() = default;
	Laser(Vec2& pos_in, Vec2& vel_in, Color c_in);
	void Draw(Graphics& gfx) const;
	void Update(const float dt);
	void CollisionBoundary();
	Rect2& GetRect();
	void Destroy();
private:
	static int constexpr width = 4;
	static int constexpr height = 16;
	Vec2 pos;
	Vec2 vel;
	Rect2 rect;
	Color c = Colors::Red;
	bool destroyed = false;
};