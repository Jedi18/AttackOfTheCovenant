#pragma once

#include "Rect2.h"
#include "Asteroid.h"
#include <vector>
#include <random>
#include "PowerUps.h"
#include "SpeedUpPowerUp.h"
#include "FasterShootPowerUp.h"
#include "WeaponSpeedIncrease.h"
#include "InvincibilityPowerUp.h"

class SpawnField
{
public:
	SpawnField(float y_in, float spawnFrequency_in, std::vector<Asteroid>& asteroidsList_in, std::vector<PowerUps>& powerupList, std::mt19937& rng_in);
	void SpawnAsteroids(const float dt, int& nAsteroids);
	void SpawnPowerUps(const float dt, Ship& ship, int& nPowerUps);
	void RelocateCheck();
	void RelocateAsteroid(Asteroid& ast);
protected:
	void UpdatePowerUpsList();
public:
	bool spawnLimitReached = false;
private:
	static constexpr float fieldHeight = 10.0f;
	static constexpr int maxX = Graphics::ScreenWidth-1-50;
	static constexpr int minX = 50;
	static constexpr int minVelY = 100;
	static constexpr int maxVelY = 300;
	static constexpr int maxSpawnAmount = 10;
	static constexpr int maxSpawnAmountPowerUps = 4;
	static constexpr int powerUpTypesNo = 4;

	int curSpawnAmount = 0;
	int powerUpSpawnAmount = 0;
	float y;
	std::mt19937& rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	std::uniform_int_distribution<int> velDist;
	std::uniform_int_distribution<int> astNo;
	std::uniform_int_distribution<int> powerupDist;
	std::vector<Asteroid>& asteroidsList;
	std::vector<PowerUps>& powerUpsList;
	float spawnFrequency;
	float spawnCounter = 0.0f;

	float powerUpSpawnFrequency = 2.0f;
	float powerUpSpawnCounter = 0.0f;;
};