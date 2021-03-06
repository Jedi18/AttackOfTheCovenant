#include "Weapon.h"

Weapon::Weapon(Vec2 & pos_in, Vec2 & vel_in, Color c_in, Rect2& rect)
	:
	pos(pos_in),
	vel(vel_in),
	c(c_in),
	rect(rect)
{
}

void Weapon::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect2(rect, c);
	}
}

void Weapon::Update(const float dt)
{
	if (!destroyed)
	{
		pos += vel * dt;
		rect.Move(pos);
		CollisionBoundary();
	}
}

void Weapon::CollisionBoundary()
{
	if (!destroyed)
	{
		rect.CollisionBoundary(pos, vel);

		if (rect.lastCollision != Rect2::LastCollision::No)
		{
			Destroy();
		}
	}
}

void Weapon::Destroy()
{
	destroyed = true;
	toBeRespawned = true;
}

void Weapon::Revive(Vec2& pos_in , Vec2& vel_in)
{
	pos = pos_in;
	vel = vel_in;
	destroyed = false;
	toBeRespawned = false;

	//fuck forget to reset last collision
	rect.lastCollision = Rect2::LastCollision::No;
}

Rect2 & Weapon::GetRect()
{
	return rect;
}

bool Weapon::IsReadyForRevival(const WeaponType& type)
{
	if (myType == type)
	{
		return toBeRespawned;
	}
	else
	{
		return false;
	}
}

bool Weapon::IsDestroyed()
{
	return destroyed;
}
