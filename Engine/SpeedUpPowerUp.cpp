#include "SpeedUpPowerUp.h"

SpeedUpPowerUp::SpeedUpPowerUp(Vec2 & pos_in, Ship & ship_in, int width, int height, PowerLevel level)
	:
	PowerUps(pos_in, ship_in, width, height, level)
{
}

void SpeedUpPowerUp::EnablePowerup() const
{
	ship.UsePowerup(Ship::PowerUpType::SpeedUp, speed[(int)powerLevel], duration[(int)powerLevel]);
}
