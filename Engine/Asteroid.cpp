#include "Asteroid.h"
#include "SpriteCodex.h"

Asteroid::Asteroid(Vec2 & pos_in, Vec2 & vel_in, int asteroid_no_in)
	:
	pos(pos_in),
	vel(vel_in),
	asteroid_no(asteroid_no_in),
	rect(pos_in.x, pos_in.x + width[asteroid_no_in], pos_in.y, pos_in.y + height[asteroid_no_in])
{
}

void Asteroid::Update(const float dt)
{
	pos += vel * dt;

	rect.Move(pos);

	CollisionBoundary();
}

void Asteroid::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		SpriteCodex::DrawAsteroid0(pos, gfx);
	}
}

void Asteroid::CollisionBoundary()
{
	if (!destroyed)
	{
		rect.CollisionBoundary(pos, vel);

		if (rect.lastCollision == Rect2::LastCollision::Bottom)
		{
			destroyed = true;
		}
	}
}

void Asteroid::LaserCollision(Laser laserList[], int nLasers)
{
	if (!destroyed)
	{
		for (int i = 0; i < nLasers; i++)
		{
			if (rect.IsOverlappingWith(laserList[i].GetRect()))
			{
				destroyed = true;
				laserList[i].Destroy();
				return;
			}
		}
	}
}
