#pragma once

#include "Vec2.h"
#include "Rect2.h"
#include "Graphics.h"
#include "Keyboard.h"

class Ship
{
	//Position is stored in terms of screen coordinates of top left corner
public:
	Ship(Vec2& pos_in, Vec2& vel_in);
	void Draw(Graphics& gfx) const;
	void Update(const Keyboard& kbd,const float dt);
	void CollisionBoundary();
private:
	Vec2 pos;
	Vec2 vel;
	float speed;
	Rect2 rect;
	static constexpr int width = 50;
	static constexpr int height = 50;
};