#pragma once

#include <vector>
#include "Vec2.h"
#include "Rect2.h"
#include "Ship.h"

class PowerUps
{
public:
	enum class PowerLevel
	{
		Low,
		Medium,
		High,
		Ultra
	};
public:
	PowerUps(Vec2& pos, Ship& ship_in, int width, int height, PowerLevel level);
	virtual void EnablePowerup() const = 0;
	void PowerUpsCollisions();
	void Draw(Graphics& gfx) const;
protected:
	Ship& ship;
	PowerLevel powerLevel;
private:
	bool enabled = true;
	Vec2 pos;
	Rect2 rect;
};