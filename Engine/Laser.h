#pragma once

#include "Weapon.h"
#include "Graphics.h"

class Laser : public Weapon
{
public:
	Laser(Vec2& pos_in, Vec2& vel_in, Color c_in = Colors::Red);
	void Draw(Graphics& gfx) const;
private:
	static int constexpr width = 4;
	static int constexpr height = 16;
};