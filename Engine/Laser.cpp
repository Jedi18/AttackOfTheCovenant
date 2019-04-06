#include "Laser.h"

Laser::Laser(Vec2 & pos_in, Vec2 & vel_in, Color c_in)
	:
	Weapon(pos_in, vel_in, c_in, Rect2(pos_in.x, pos_in.x + width, pos_in.y, pos_in.y + height))
{
	myType = Weapon::WeaponType::LaserProj;
}

void Laser::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect2(rect, c);
	}
}
