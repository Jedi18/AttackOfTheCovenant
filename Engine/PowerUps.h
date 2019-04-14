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
	bool IsEnabled() const;
public:
	// blacklist the item so that spawner knows it has already been detected as being disabled
	// i.e. when spawner is checking listto see which is newly disabled, it dosen't take this into account 
	// as it has been detected as disabled on a previous loop
	bool blackListedFromSpawn = false;
protected:
	Ship& ship;
	PowerLevel powerLevel;
private:
	bool enabled = true;
	Vec2 pos;
	Rect2 rect;
};