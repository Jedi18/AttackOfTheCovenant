#pragma once

#include "PowerUps.h"

class FasterShootPowerUp : public PowerUps
{
public:
	FasterShootPowerUp(Vec2& pos_in, Ship& ship_in, int width, int height, PowerLevel level);
	void EnablePowerup() const override;
private:
	float shootTimeGap[4] = { 0.8f, 0.6f, 0.5f, 0.4f };
	float duration[4] = { 8, 7, 5, 4 };
};