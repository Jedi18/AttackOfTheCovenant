#pragma once

#include "Vec2.h"
#include "Rect2.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Weapon.h"
#include <vector>
#include "Asteroid.h"
#include "Mouse.h"
#include "Sound.h"

class Ship
{
public:
	// Can't store this in powerups as it includes ship
	enum class PowerUpType
	{
		SpeedUp,
		FasterShoot,
		Invincibility,
		None
	};
public:
	Ship(Vec2& pos_in, Vec2& vel_in);	//Position is stored in terms of screen coordinates of top left corner
	void Draw(Graphics& gfx) const;
	void Update(const Keyboard& kbd, const Mouse& mouse, const float dt, std::vector<Weapon> &weapons, int& nWeapons);
	void CollisionBoundary();
	void AsteroidCollision(std::vector<Asteroid>& asteroidList, int& nAsteroids);
	void ShootWeapon(std::vector<Weapon> &weapons, int& nWeapons, Weapon::WeaponType type,const Vec2& shootDir);
	void ShootRecycled(std::vector<Weapon> &weapons, int& nWeapons, Weapon::WeaponType type, const Vec2& shootDir);
	Rect2& GetRect();
	void UsePowerup(PowerUpType power, float value, float duration);
	void DisablePowerUp();
private:
	Vec2 pos;
	Vec2 vel;
	float speed;

	// storing values for reuse after powerup time duration is used up
	float originalSpeed;
	static constexpr float originalWeaponSpeed = 300.0f;
	// To allow a small time gap between lasers being shot
	static constexpr float originalShootTimeGap = 0.25f;

	float powerUpTimeLeft = 0.0f;
	bool powerUpEnabled = false;
	PowerUpType powerUpInUse = PowerUpType::None;

	Rect2 rect;
	static constexpr int width = 50;
	static constexpr int height = 50;
	static constexpr int maxWeaponCount = 30;
	int weaponCount = 0;

	float weaponSpeed = originalWeaponSpeed;
	float shootTimeGap = originalShootTimeGap;

	//originalShootTimeGap -0.01f -> so that there's no time gap when first shooting
	float shootTimer = originalShootTimeGap -0.01f;
	float turrentShootTimer = originalWeaponSpeed - 0.01f;
	bool destroyed = false;
	Sound laserSound1;
	Sound laserSound2;
};