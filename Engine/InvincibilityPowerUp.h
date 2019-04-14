#pragma once

#include "PowerUps.h"

class InvincibilityPowerUp : public PowerUps
{
public:
	InvincibilityPowerUp(Vec2& pos_in, Ship& ship_in, int width, int height, PowerLevel level);
	void EnablePowerup() const override;
private:
	float duration[4] = { 2, 3, 4, 5 };
};