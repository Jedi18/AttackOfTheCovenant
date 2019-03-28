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

void Ship::Update(const Keyboard & kbd,const float dt, std::vector<Laser> &lasers, int& nLasers)
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

	// Shoot the laser
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		if (shootTimer > shootTimeGap)
		{
			ShootLaser(lasers, nLasers);
			shootTimer = 0;
		}
		else 
		{
			shootTimer += dt;
		}
	}

	rect.Move(pos);
	CollisionBoundary();
}

void Ship::CollisionBoundary()
{
	rect.CollisionBoundary(pos, vel);
}

void Ship::ShootLaser(std::vector<Laser> &lasers, int& nLasers)
{
	lasers.push_back(Laser(Vec2(rect.left + width/2, rect.top), Vec2(0, -300), laserColor));
	nLasers++;
}
