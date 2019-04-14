#pragma once

#include "PowerUps.h"

class WeaponSpeedIncrease : public PowerUps
{
public:
	WeaponSpeedIncrease(Vec2& pos_in, Ship& ship_in, int width, int height, PowerLevel level);
	void EnablePowerup() const override;
private:
	float speedIncrease[4] = { 1.5, 2, 2.5, 3 };
	float duration[4] = { 8, 7, 5, 4 };
};