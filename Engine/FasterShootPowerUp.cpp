#include "FasterShootPowerUp.h"

FasterShootPowerUp::FasterShootPowerUp(Vec2 & pos_in, Ship & ship_in, int width, int height, PowerLevel level)
	:
	PowerUps(pos_in, ship_in, width, height, level)
{
}

void FasterShootPowerUp::EnablePowerup() const
{
	ship.UsePowerup(Ship::PowerUpType::FasterShoot, shootTimeGap[(int)powerLevel], duration[(int)powerLevel]);
}
