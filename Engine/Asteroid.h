#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "Rect2.h"
#include "Laser.h"
#include <vector>

class Asteroid
{
	// Position is stored in terms of screen coordinates of top left corner
public:
	Asteroid(Vec2& pos, Vec2& vel, int asteroid_no);
	void Update(const float dt);
	void Draw(Graphics& gfx) const;
	void CollisionBoundary();
	void WeaponCollision(std::vector<Weapon> &weapons, int& nWeapons);
	bool IsDestroyed() const;
	Rect2& GetRect();
	void Destroy();
	void SetPositionAndVelocity(Vec2 pos, Vec2 vel);
	void SetRespawnConditions();
public:
	static constexpr int no_asteroid_types = 2;
	bool toBeRelocated = false;
private:
	int asteroid_no;
	float width[no_asteroid_types] = { 50, 40 };
	float height[no_asteroid_types] = { 50, 55 };
	Vec2 pos;
	Vec2 vel;
	Rect2 rect;
	bool destroyed = false;
	bool disableCollisionBoundary = true;
	bool enteredPlayingGround = false;
};