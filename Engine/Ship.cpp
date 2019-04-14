#include "Ship.h"
#include "SpriteCodex.h"
#include "BallProjectile.h"
#include "assert.h"

Ship::Ship(Vec2 & pos_in, Vec2 & vel_in)
	:
	pos(pos_in),
	vel(vel_in),
	rect(pos_in.x, pos_in.x + width, pos_in.y, pos_in.y + height),
	speed(vel.GetLength()),
	originalSpeed(speed),
	laserSound1(L"pewpew.wav"),
	laserSound2(L"pewpew1.wav")
{
}

void Ship::Draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		SpriteCodex::DrawShip(pos, gfx);
	}
}

void Ship::Update(const Keyboard & kbd, const Mouse& mouse,const float dt, std::vector<Weapon> &weapons, int& nWeapons)
{
	if (destroyed)
	{
		return;
	}

	// power up update
	if (powerUpEnabled)
	{
		if (powerUpTimeLeft > 0.0f)
		{
			powerUpTimeLeft -= dt;
		}
		else
		{
			powerUpTimeLeft = 0.0f;
			powerUpEnabled = false;
			DisablePowerUp();
		}
	}

	// player movement
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
			ShootWeapon(weapons, nWeapons, Weapon::WeaponType::LaserProj, Vec2(0,-1));
			shootTimer = 0;
		}
		else 
		{
			shootTimer += dt;
		}
	}

	// Shoot turret laser
	if (mouse.LeftIsPressed())
	{
		if (turrentShootTimer > shootTimeGap)
		{
			Vec2 direction = (Vec2((float)mouse.GetPosX(), (float)mouse.GetPosY()) - pos).GetNormalized();

			ShootWeapon(weapons, nWeapons, Weapon::WeaponType::TurretProj, direction);
			turrentShootTimer = 0;
		}
		else
		{
			turrentShootTimer += dt;
		}
	}

	rect.Move(pos);
	CollisionBoundary();
}

void Ship::CollisionBoundary()
{
	rect.CollisionBoundary(pos, vel);
}

void Ship::AsteroidCollision(std::vector<Asteroid>& asteroidList, int& nAsteroids)
{
	if (!destroyed)
	{
		for (int i = 0; i < nAsteroids; i++)
		{
			if (!asteroidList[i].IsDestroyed())
			{
				if (rect.IsOverlappingWith(asteroidList[i].GetRect()))
				{
					if (!invincible)
					{
						destroyed = true;
					}
					asteroidList[i].GetRect().lastCollision = Rect2::LastCollision::Player;
					asteroidList[i].Destroy();
					break;
				}
			}
		}
	}
}

void Ship::ShootWeapon(std::vector<Weapon> &weapons, int& nWeapons, Weapon::WeaponType type, const Vec2& shootDir)
{
	switch (type)
	{
	case Weapon::WeaponType::LaserProj:
		if (weaponCount < maxWeaponCount)
		{
			weapons.push_back(Laser(Vec2(rect.left + width / 2, rect.top), shootDir * weaponSpeed));
			nWeapons++;
			weaponCount++;
		}
		else
		{
			ShootRecycled(weapons, nWeapons, type, shootDir);
		}
		laserSound1.Play(1.0f, 0.5f);
		break;
	case Weapon::WeaponType::TurretProj:
		if (weaponCount < maxWeaponCount)
		{
			weapons.push_back(BallProjectile(Vec2(rect.left + width / 2, rect.top), shootDir * weaponSpeed));
			nWeapons++;
			weaponCount++;
		}
		else
		{
			ShootRecycled(weapons, nWeapons, type, shootDir);
		}
		laserSound2.Play(1.0f, 0.5f);
		break;
	}
}

void Ship::ShootRecycled(std::vector<Weapon>& weapons, int & nWeapons, Weapon::WeaponType type, const Vec2 & shootDir)
{
	for (Weapon& wep : weapons)
	{
		if (wep.IsReadyForRevival(type))
		{
			switch (type)
			{
			case Weapon::WeaponType::LaserProj:
             	wep.Revive(Vec2(rect.left + width / 2, rect.top), shootDir * weaponSpeed);
				break;
			case Weapon::WeaponType::TurretProj:
				wep.Revive(Vec2(rect.left + width / 2, rect.top), shootDir * weaponSpeed);
				break;
			}
			break;
		}
	}
}

Rect2 & Ship::GetRect()
{
	return rect;
}

void Ship::UsePowerup(PowerUpType power, float value, float duration)
{
	assert(power != PowerUpType::None);
	switch (power)
	{
	case PowerUpType::SpeedUp:
		speed = speed * value;
		powerUpInUse = PowerUpType::SpeedUp;
		break;
	case PowerUpType::FasterShoot:
		shootTimeGap = shootTimeGap * value;
		powerUpInUse = PowerUpType::FasterShoot;
		break;
	case PowerUpType::WeaponSpeedIncrease:
		weaponSpeed = weaponSpeed * value;
		powerUpInUse = PowerUpType::WeaponSpeedIncrease;
		break;
	case PowerUpType::Invincibility:
		invincible = true;
		powerUpInUse = PowerUpType::Invincibility;
		break;
	}

	powerUpTimeLeft = duration;
	powerUpEnabled = true;
}

void Ship::DisablePowerUp()
{
	assert(powerUpInUse != PowerUpType::None);

	switch (powerUpInUse)
	{
	case PowerUpType::SpeedUp:
		speed = originalSpeed;
		break;
	case PowerUpType::FasterShoot:
		shootTimeGap = originalShootTimeGap;
		break;
	case PowerUpType::WeaponSpeedIncrease:
		weaponSpeed = originalWeaponSpeed;
		break;
	case PowerUpType::Invincibility:
		invincible = false;
		break;
	}

	powerUpInUse = PowerUpType::None;
}
