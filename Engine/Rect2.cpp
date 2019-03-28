#include "Rect2.h"

Rect2::Rect2(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

void Rect2::Move(const Vec2 & disp)
{
	float width = right - left;
	float height = bottom - top;

	left = disp.x;
	right = disp.x + width;
	top = disp.y;
	bottom = disp.y + height;
}
