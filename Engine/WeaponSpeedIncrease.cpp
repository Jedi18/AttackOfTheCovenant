#include "WeaponSpeedIncrease.h"

WeaponSpeedIncrease::WeaponSpeedIncrease(Vec2 & pos_in, Ship & ship_in, int width, int height, PowerLevel level)
	:
	PowerUps(pos_in, ship_in, width, height, level)
{
}

void WeaponSpeedIncrease::EnablePowerup() const
{
	ship.UsePowerup(Ship::PowerUpType::WeaponSpeedIncrease, speedIncrease[(int)powerLevel], duration[(int)powerLevel]);
}