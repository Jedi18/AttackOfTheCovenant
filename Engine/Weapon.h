#pragma once

#include "Graphics.h"

class Weapon
{
public:
	enum class WeaponType
	{
		None,
		LaserProj,
		TurretProj
	};
public:
	Weapon() = default;
	Weapon(Vec2& pos_in, Vec2& vel_in, Color c_in, Rect2& rect);
	void Draw(Graphics& gfx) const;
	void Update(const float dt);
	void CollisionBoundary();
	void Destroy();
	void Revive(Vec2& pos, Vec2& vel);
	Rect2& GetRect();
	bool IsReadyForRevival(const WeaponType& type);
	bool IsDestroyed();
protected:
	Vec2 pos;
	Vec2 vel;
	Color c = Colors::Red;
	Rect2 rect;
	bool destroyed = false;
	bool toBeRespawned = false;
	WeaponType myType = WeaponType::None;
};