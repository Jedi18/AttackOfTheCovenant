#include "Ship.h"

Ship::Ship(Vec2 & pos_in, Vec2 & vel_in, float size, Color c)
	:
	pos(pos_in),
	vel(vel_in),
	rect(pos_in.x, pos_in.x + size, pos_in.y, pos_in.y + size),
	speed(vel.GetLength())
{
}

void Ship::Draw(Graphics& gfx) const
{
	gfx.DrawRect2(rect, c);
}

void Ship::Update(const Keyboard & kbd, float dt)
{
	Vec2 direction = vel.GetNormalized();

	if (kbd.KeyIsPressed(VK_UP))
	{
		direction += {0.0f, -1.0f};
	}

	if (kbd.KeyIsPressed(VK_DOWN))
	{
		direction += {0.0f, 1.0f};
	}

	if (kbd.KeyIsPressed(VK_LEFT))
	{
		direction += {-1.0f, 0.0f};
	}

	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		direction += {1.0f, 0.0f};
	}

	vel = direction.GetNormalized() * speed;

	pos += vel * dt;
	rect.Move(pos);
}
