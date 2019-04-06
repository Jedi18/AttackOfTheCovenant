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
	if (destroyed)
	{
		return;
	}

	pos += vel * dt;

	rect.Move(pos);

	CollisionBoundary();
}

void Asteroid::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		SpriteCodex::DrawAsteroid(asteroid_no, pos, gfx);
	}
}

void Asteroid::CollisionBoundary()
{
	if (!destroyed)
	{
		if (!enteredPlayingGround)
		{
			if (pos.y >= 0)
			{
				disableCollisionBoundary = false;
				enteredPlayingGround = true;
			}
		}
		if (!disableCollisionBoundary)
		{
			rect.CollisionBoundary(pos, vel);
		}

		if (rect.lastCollision == Rect2::LastCollision::Bottom)
		{
			destroyed = true;
		}
	}
}

void Asteroid::WeaponCollision(std::vector<Weapon> &weapons, int& nWeapons)
{
	if (!destroyed)
	{
		for (int i = 0; i < nWeapons; i++)
		{
			if (rect.IsOverlappingWith(weapons[i].GetRect()))
			{
				destroyed = true;
				weapons[i].Destroy();
				return;
			}
		}
	}
}

bool Asteroid::IsDestroyed() const
{
	return destroyed;
}

const Rect2 & Asteroid::GetRect() const
{
	return rect;
}

void Asteroid::Destroy()
{
	destroyed = true;
}
