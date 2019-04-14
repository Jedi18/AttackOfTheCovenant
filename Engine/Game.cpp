/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ship(Vec2(100, 600), Vec2(200, 200)),
	rng(rd()),
	stars(rng, Vec2(0, -100)),
	spawnField(-60.0f, 0.5f, asteroidList, powerupsList, rng),
	backgroundSound(L"backgroundMusic.wav", 0.0f, 1.0f),
	mesainvincible(Vec2(300, 300), ship, 20, 20, PowerUps::PowerLevel::High)
{
	backgroundSound.Play(1.0f, 0.5f);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	// Check if required amount of asteroids have been spawned
	if (!spawnField.spawnLimitReached)
	{
		spawnField.SpawnAsteroids(dt, nAsteroids);
	}

	spawnField.SpawnPowerUps(dt, ship, nPowerUps);

	ship.Update(wnd.kbd,wnd.mouse, dt, weaponList, nWeapons);

	ship.AsteroidCollision(asteroidList, nAsteroids);

	for (int i = 0; i < nAsteroids; i++)
	{
		asteroidList[i].Update(dt);
	}

	for (int i = 0; i < nWeapons; i++)
	{
		weaponList[i].Update(dt);
	}
	
	for (int i = 0; i < nAsteroids; i++)
	{
		asteroidList[i].WeaponCollision(weaponList, nWeapons);
	}

	for (int i = 0; i < powerupsList.size(); i++)
	{
		powerupsList[i]->PowerUpsCollisions();
	}

	stars.UpdateStars(rng, dt);

	// Recycle asteroids by relocating them if they've collided with boundary or weapon
	spawnField.RelocateCheck();
}

void Game::ComposeFrame()
{
	stars.Draw(gfx);
	ship.Draw(gfx);
	for (int i = 0; i < nAsteroids; i++)
	{
		asteroidList[i].Draw(gfx);
	}
	for (int i = 0; i < nWeapons; i++)
	{
		weaponList[i].Draw(gfx);
	}
	for (int i = 0; i < powerupsList.size(); i++)
	{
		powerupsList[i]->Draw(gfx);
	}
}
