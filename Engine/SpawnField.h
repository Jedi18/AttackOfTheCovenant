#pragma once

#include "Rect2.h"
#include "Asteroid.h"
#include <vector>
#include <random>

class SpawnField
{
public:
	SpawnField(float y_in, float spawnFrequency_in, std::vector<Asteroid>& asteroidsList_in, std::mt19937& rng_in);
	void SpawnAsteroids(const float dt, int& nAsteroids);
	void RelocateCheck();
	void RelocateAsteroid(Asteroid& ast);
public:
	bool spawnLimitReached = false;
private:
	static constexpr float fieldHeight = 10.0f;
	static constexpr int maxX = Graphics::ScreenWidth-1-50;
	static constexpr int minX = 50;
	static constexpr int minVelY = 100;
	static constexpr int maxVelY = 300;
	static constexpr int maxSpawnAmount = 10;
	int curSpawnAmount = 0;
	float y;
	std::mt19937& rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> velDist;
	std::uniform_int_distribution<int> astNo;
	std::vector<Asteroid>& asteroidsList;
	float spawnFrequency;
	float spawnCounter = 0.0f;
};