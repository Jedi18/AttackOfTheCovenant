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
	ast0(Vec2(100, 50), Vec2(0, 200), 0),
	rng(rd())
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

	ship.Update(wnd.kbd, dt, laserList, nLasers);
	ast0.Update(dt);

	for (int i = 0; i < nLasers; i++)
	{
		laserList[i].Update(dt);
	}
	
	ast0.LaserCollision(laserList, nLasers);
}

void Game::ComposeFrame()
{
	// Draw Stars
	SpriteCodex::DrawStars(gfx, nStars, xStarPoints, yStarPoints);

	ship.Draw(gfx);
	ast0.Draw(gfx);
	for (int i = 0; i < nLasers; i++)
	{
		laserList[i].Draw(gfx);
	}
}
