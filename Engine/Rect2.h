#pragma once

#include "Vec2.h"

class Rect2
{
public:
	Rect2(float left_in, float right_in, float top_in, float bottom_in);
	void Move(const Vec2& disp);
public:
	float left;
	float right;
	float top;
	float bottom;
};