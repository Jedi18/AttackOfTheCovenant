#pragma once

#include "Vec2.h"
#include "Rect2.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Weapon.h"
#include <vector>
#include "Asteroid.h"
#include "Mouse.h"

class Ship
{
public:
	enum class WeaponType
	{
		LaserProj,
		TurretProj
	};
	//Position is stored in terms of screen coordinates of top left corner
public:
	Ship(Vec2& pos_in, Vec2& vel_in);
	void Draw(Graphics& gfx) const;
	void Update(const Keyboard& kbd, const Mouse& mouse, const float dt, std::vector<Weapon> &weapons, int& nWeapons);
	void CollisionBoundary();
	void AsteroidCollision(std::vector<Asteroid>& asteroidList, int& nAsteroids);
	void ShootWeapon(std::vector<Weapon> &weapons, int& nWeapons, WeaponType type,const Vec2& shootDir);
private:
	Vec2 pos;
	Vec2 vel;
	float speed;
	Rect2 rect;
	static constexpr int width = 50;
	static constexpr int height = 50;
	static constexpr float weaponSpeed = 300.0f;
	// To allow a small time gap between lasers being shot
	static constexpr float shootTimeGap = 0.25f;
	float shootTimer = shootTimeGap-0.01f;
	float turrentShootTimer = shootTimeGap - 0.01f;

	bool destroyed = false;
};