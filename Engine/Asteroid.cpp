#include "Asteroid.h"
#include "SpriteCodex.h"
#include <assert.h>

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
			Destroy();
		}
	}
}

void Asteroid::WeaponCollision(std::vector<Weapon> &weapons, int& nWeapons)
{
	if (!destroyed)
	{
		for (int i = 0; i < nWeapons; i++)
		{
			// Check if weapon is not disabled and only then check for overlapping
			if (!weapons[i].IsDestroyed())
			{
				if (rect.IsOverlappingWith(weapons[i].GetRect()))
				{
					rect.lastCollision = Rect2::LastCollision::Weapon;
					Destroy();
					weapons[i].Destroy();
					return;
				}
			}
		}
	}
}

bool Asteroid::IsDestroyed() const
{
	return destroyed;
}

Rect2 & Asteroid::GetRect()
{
	return rect;
}

void Asteroid::Destroy()
{
	assert(rect.lastCollision != Rect2::LastCollision::No);

	if (rect.lastCollision == Rect2::LastCollision::Player)
	{
		destroyed = true;
	}
	else
	{
		toBeRelocated = true;
	}
}

void Asteroid::SetPositionAndVelocity(Vec2 pos_in, Vec2 vel_in)
{
	pos = pos_in;
	vel = vel_in;
}

void Asteroid::SetRespawnConditions()
{
	disableCollisionBoundary = true;
	enteredPlayingGround = false;
}
