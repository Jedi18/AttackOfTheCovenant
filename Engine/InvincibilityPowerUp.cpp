#include "InvincibilityPowerUp.h"

InvincibilityPowerUp::InvincibilityPowerUp(Vec2 & pos_in, Ship & ship_in, int width, int height, PowerLevel level)
	:
	PowerUps(pos_in, ship_in, width, height, level)
{
}

void InvincibilityPowerUp::EnablePowerup() const
{
	ship.UsePowerup(Ship::PowerUpType::Invincibility, 0, duration[(int)powerLevel]);
}
