#include "SpawnField.h"
#include "Graphics.h"

SpawnField::SpawnField(float y_in, float spawnFrequency_in, std::vector<Asteroid>& asteroidsList_in, std::mt19937& rng_in)
	:
	y(y_in),
	spawnFrequency(spawnFrequency_in),
	asteroidsList(asteroidsList_in),
	rng(rng_in),
	xDist(minX, maxX),
	velDist(minVelY, maxVelY),
	astNo(0,Asteroid::no_asteroid_types-1)
{
}

void SpawnField::SpawnAsteroids(const float dt, int& nAsteroids)
{
	if (curSpawnAmount == maxSpawnAmount)
	{
		spawnLimitReached = true;
	}
	if (curSpawnAmount < maxSpawnAmount)
	{
		if (spawnCounter > spawnFrequency)
		{
			Vec2 pos = { (float)xDist(rng), y };
			Vec2 vel = { 0, (float)velDist(rng) };
			int asteroid_no = astNo(rng);

			asteroidsList.push_back(Asteroid(pos, vel, asteroid_no));
			nAsteroids++;

			spawnCounter = 0.0f;
			curSpawnAmount++;
		}
		else {
			spawnCounter += dt;
		}
	}
}

void SpawnField::RelocateCheck()
{
	for (Asteroid& ast : asteroidsList)
	{
		if (ast.toBeRelocated)
		{
			RelocateAsteroid(ast);
		}
	}
}

void SpawnField::RelocateAsteroid(Asteroid & ast)
{
	Vec2 pos = { (float)xDist(rng), y };
	Vec2 vel = { 0, (float)velDist(rng) };

	ast.SetPositionAndVelocity(pos, vel);

	ast.toBeRelocated = false;
	ast.SetRespawnConditions();
}
