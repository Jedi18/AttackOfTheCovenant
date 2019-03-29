#pragma once

#include <random>
#include "Graphics.h"

class StarBackground
{
public:
	StarBackground(std::mt19937& rng, Vec2& vel_in);
	void Draw(Graphics& gfx) const;
	void UpdateStars(std::mt19937& rng, const float dt);
private:
	Vec2 vel;
	static constexpr int nStars = 30;
	float xStarPoints[nStars];
	float yStarPoints[nStars];
};