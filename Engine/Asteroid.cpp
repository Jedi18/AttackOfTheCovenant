#include "Asteroid.h"
#include "SpriteCodex.h"

Asteroid::Asteroid(Vec2 & pos_in, Vec2 & vel_in, int asteroid_no_in)
	:
	pos(pos_in),
	vel(vel_in),
	asteroid_no(asteroid_no_in),
	rect(pos_in.x, pos_in.x + width[asteroid_no_in], pos_in.y, pos_in.y + height[asteroid_no_in])
{
}

void Asteroid::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawAsteroid0(pos, gfx);
}
