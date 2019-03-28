#include "Ship.h"
#include "SpriteCodex.h"

Ship::Ship(Vec2 & pos_in, Vec2 & vel_in, float size, Color c)
	:
	pos(pos_in),
	vel(vel_in),
	rect(pos_in.x, pos_in.x + size, pos_in.y, pos_in.y + size),
	speed(vel.GetLength()),
	c(c)
{
}

void Ship::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawShip(pos, gfx);
}

void Ship::Update(const Keyboard & kbd, float dt)
{
	Vec2 direction = { 0.0f, 0.0f };

	if (kbd.KeyIsPressed(VK_UP) || kbd.KeyIsPressed(0x57))
	{
		direction += {0.0f, -1.0f};
	}

	if (kbd.KeyIsPressed(VK_DOWN) || kbd.KeyIsPressed(0x53))
	{
		direction += {0.0f, 1.0f};
	}

	if (kbd.KeyIsPressed(VK_LEFT) || kbd.KeyIsPressed(0x41))
	{
		direction += {-1.0f, 0.0f};
	}

	if (kbd.KeyIsPressed(VK_RIGHT) || kbd.KeyIsPressed(0x44))
	{
		direction += {1.0f, 0.0f};
	}

	vel = direction.GetNormalized() * speed;

	pos += vel * dt;
	rect.Move(pos);
}
