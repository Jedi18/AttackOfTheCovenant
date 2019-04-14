#include "PowerUps.h"

PowerUps::PowerUps(Vec2& pos_in, Ship& ship_in, int width, int height, PowerLevel level)
	:
	pos(pos_in),
	ship(ship_in),
	rect(pos.x, pos.x + width, pos.y, pos.y + height),
	powerLevel(level)
{
}

void PowerUps::EnablePowerup() const
{
}

void PowerUps::PowerUpsCollisions()
{
	if (enabled)
	{
		if (rect.IsOverlappingWith(ship.GetRect()))
		{
			EnablePowerup();
			enabled = false;
		}
	}
}

void PowerUps::Draw(Graphics & gfx) const
{
	if (enabled)
	{
		gfx.DrawRect2(rect, Colors::Red);
	}
}

bool PowerUps::IsEnabled() const
{
	return enabled;
}
