#pragma once

#include "Vec2.h"

class Rect2
{
public:
	enum class LastCollision
	{
		No,
		Top,
		Bottom,
		Left,
		Right
	};
public:
	Rect2(float left_in, float right_in, float top_in, float bottom_in);
	void Move(const Vec2& disp);
	void CollisionBoundary(Vec2& pos, Vec2& vel);
public:
	float left;
	float right;
	float top;
	float bottom;
	LastCollision lastCollision = LastCollision::No;
};