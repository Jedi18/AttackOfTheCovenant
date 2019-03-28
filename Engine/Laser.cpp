#include "Laser.h"

Laser::Laser(Vec2 & pos_in, Vec2 & vel_in, Color c_in)
	:
	pos(pos_in),
	vel(vel_in),
	rect(pos_in.x, pos_in.x + width, pos_in.y, pos_in.y + height),
	c(c_in)
{
}

void Laser::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect2(rect, c);
	}
}

void Laser::Update(const float dt)
{
	if (!destroyed)
	{
		pos += vel * dt;
		rect.Move(pos);
		CollisionBoundary();
	}
}

void Laser::CollisionBoundary()
{
	rect.CollisionBoundary(pos, vel);

	if (rect.lastCollision != Rect2::LastCollision::No)
	{
		destroyed = true;
	}
}

Rect2 & Laser::GetRect()
{
	return rect;
}

void Laser::Destroy()
{
	destroyed = true;
}
