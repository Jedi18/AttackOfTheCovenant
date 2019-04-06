#include "BallProjectile.h"

BallProjectile::BallProjectile(Vec2 & pos_in, Vec2 & vel_in, Color c_in)
	:
	Weapon(pos_in, vel_in, c_in, Rect2(pos_in.x, pos_in.x + radius, pos_in.y, pos_in.y + radius))
{
	myType = Weapon::WeaponType::TurretProj;
}

void BallProjectile::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect2(rect, c);
	}
}
