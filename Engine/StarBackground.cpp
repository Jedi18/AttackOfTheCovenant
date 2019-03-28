#include "StarBackground.h"
#include "SpriteCodex.h"

StarBackground::StarBackground(std::mt19937 & rng, Vec2 & vel_in)
	:
	vel(vel_in)
{
	std::uniform_int_distribution<int> xDist(2, Graphics::ScreenWidth - 3);
	std::uniform_int_distribution<int> yDist(2, Graphics::ScreenHeight - 3);

	int i = 0;

	while (i < nStars)
	{
		xStarPoints[i] = xDist(rng);
		yStarPoints[i] = yDist(rng);
		i++;
	}
}

void StarBackground::Draw(Graphics& gfx) const
{	
	for (int i = 0; i < nStars; i++)
	{
		SpriteCodex::DrawStars(gfx, xStarPoints[i], yStarPoints[i]);
	}
}

void StarBackground::UpdateStars(std::mt19937& rng, const float dt)
{
	std::uniform_int_distribution<int> xDist(2, Graphics::ScreenWidth - 3);
	//std::uniform_int_distribution<int> yDist(2, Graphics::ScreenHeight - 3);

	for (int i = 0; i < nStars; i++)
	{
		xStarPoints[i] += vel.x * dt;
		yStarPoints[i] += vel.y * dt;

		if (xStarPoints[i] < 2 || xStarPoints[i] > Graphics::ScreenWidth - 3 || yStarPoints[i] < 2 || yStarPoints[i] > Graphics::ScreenHeight - 3)
		{
			xStarPoints[i] = xDist(rng);
			yStarPoints[i] = Graphics::ScreenHeight - 3;
		}
	}
}
