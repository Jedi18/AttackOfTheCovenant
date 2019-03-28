#include "Ship.h"
#include "SpriteCodex.h"

Ship::Ship(Vec2 & pos_in, Vec2 & vel_in)
	:
	pos(pos_in),
	vel(vel_in),
	rect(pos_in.x, pos_in.x + width, pos_in.y, pos_in.y + height),
	speed(vel.GetLength())
{
}

void Ship::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawShip(pos, gfx);
}

void Ship::Update(const Keyboard & kbd,const float dt)
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

void Ship::CollisionBoundary()
{
	float left = pos.x;
	float right = pos.x + width;
	float top = pos.y;
	float down = pos.y + height;

	if (left < 0)
	{
		pos.x = 0;
		vel.x = 0;
	}

	if (right >= Graphics::ScreenWidth)
	{
		pos.x = Graphics::ScreenWidth - 1 - width;
		vel.x = 0;
	}

	if (top < 0)
	{
		pos.y = 0;
		vel.y = 0;
	}

	if (down >= Graphics::ScreenHeight)
	{
		pos.y = Graphics::ScreenHeight - 1 - height;
		vel.y = 0;
	}
}
