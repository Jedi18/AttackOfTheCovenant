#include "Rect2.h"
#include "Graphics.h"

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

void Rect2::CollisionBoundary(Vec2& pos, Vec2& vel)
{
	float width = right - left;
	float height = bottom - top;

	if (left < 0)
	{
		pos.x = 0;
		vel.x = 0;
		lastCollision = LastCollision::Left;
	}

	if (right >= Graphics::ScreenWidth)
	{
		pos.x = Graphics::ScreenWidth - 1 - width;
		vel.x = 0;
		lastCollision = LastCollision::Right;
	}

	if (top < 0)
	{
		pos.y = 0;
		vel.y = 0;
		lastCollision = LastCollision::Top;
	}

	if (bottom >= Graphics::ScreenHeight)
	{
		pos.y = Graphics::ScreenHeight - 1 - height;
		vel.y = 0;
		lastCollision = LastCollision::Bottom;
	}
}

bool Rect2::IsOverlappingWith(const Rect2 & rect) const
{
	if (rect.left <= right && rect.right >= left && rect.top <= bottom && rect.bottom >= top)
	{
		return true;
	}
	else {
		return false;
	}
}
