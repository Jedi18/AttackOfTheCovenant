#pragma once

#include "Weapon.h"

class BallProjectile : public Weapon
{
public:
	BallProjectile(Vec2& pos_in, Vec2& vel_in, Color c_in = Colors::Green);
	void Draw(Graphics& gfx) const;
private:
	static constexpr int radius = 5;
};