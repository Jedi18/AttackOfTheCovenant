#include "SpawnField.h"
#include "Graphics.h"
#include "Ship.h"
#include <assert.h>

SpawnField::SpawnField(float y_in, float spawnFrequency_in, std::vector<Asteroid>& asteroidsList_in, std::vector<std::unique_ptr<PowerUps>>& powerupList, std::mt19937& rng_in)
	:
	y(y_in),
	spawnFrequency(spawnFrequency_in),
	asteroidsList(asteroidsList_in),
	powerUpsList(powerupList),
	rng(rng_in),
	xDist(minX, maxX),
	yDist(0, 500),
	velDist(minVelY, maxVelY),
powerupDist(1, powerUpTypesNo),
astNo(0, Asteroid::no_asteroid_types - 1)
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

void SpawnField::SpawnPowerUps(const float dt, Ship& ship, int& nPowerUps)
{
	if (powerUpSpawnCounter > powerUpSpawnFrequency)
	{
		// check powerups list vector to see if any of the powerups has been disabled so that we can change 
		// powerUpSpawnAmount
		UpdatePowerUpsList();

		if (powerUpSpawnAmount < maxSpawnAmountPowerUps)
		{
			Vec2 pos = { (float)xDist(rng), (float)yDist(rng) };

			int powerUpType = powerupDist(rng);
			// for now since powerupdist also has 4 allowable values
			assert(powerUpTypesNo == 4);
			int powerLevel = powerupDist(rng);

			switch (powerUpType)
			{
			case 0:
				powerUpsList.push_back(std::unique_ptr<PowerUps>(new SpeedUpPowerUp(pos, ship, 20, 20, (PowerUps::PowerLevel)powerLevel)));
				break;
			case 1:
				powerUpsList.push_back(std::unique_ptr<PowerUps>(new FasterShootPowerUp(pos, ship, 20, 20, (PowerUps::PowerLevel)powerLevel)));
				break;
			case 2:
				powerUpsList.push_back(std::unique_ptr<PowerUps>(new WeaponSpeedIncrease(pos, ship, 20, 20, (PowerUps::PowerLevel)powerLevel)));
				break;
			case 3:
				powerUpsList.push_back(std::unique_ptr<PowerUps>(new InvincibilityPowerUp(pos, ship, 20, 20, (PowerUps::PowerLevel)powerLevel)));
				break;
			}
			powerUpSpawnAmount++;
			nPowerUps++;
		}
		powerUpSpawnCounter = 0.0f;
	}
	else
	{
		powerUpSpawnCounter += dt;
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

void SpawnField::UpdatePowerUpsList()
{
	for (size_t i = 0; i < powerUpsList.size(); i++)
	{
		if (!powerUpsList[i]->IsEnabled() && !powerUpsList[i]->blackListedFromSpawn)
		{
			powerUpSpawnAmount--;
			powerUpsList[i]->blackListedFromSpawn = true;
		}
	}
}
