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
#include "Board.h"
#include "SpriteCodex.h"
#include <chrono>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	goal(rng, brd, snek),
	wall(rng, brd, snek),
	snek({ 20,15 })
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}
using std::chrono::steady_clock;
steady_clock::time_point start = steady_clock::now();
void Game::UpdateModel()
{
	
	brd.DrawBorder(Colors::Cyan);
	if (!gameIsOver)
	{
		
		snekMoveCounter += ft.Mark() * 60; //change this to be the difference in time/duration between frames
		if (snekMoveCounter > snekMovePeriod)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP) && delta_loc.y != 1)
			{
				delta_loc = { 0,-1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN) && delta_loc.y != -1)
			{
				delta_loc = { 0,1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT) && delta_loc.x != 1)
			{
				delta_loc = { -1,0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && delta_loc.x != -1)
			{
				delta_loc = { 1,0 };
			}
			snekMoveCounter = 0.0f;
			const Location next = snek.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || snek.IsInTile(next) || wall.IsInSpot(next))
			{
				gameIsOver = true;
			}
			else
			{
				const bool eating = next == goal.GetLocation();
				//used for wall collision check, could also use the above check for next position with wall
				
				if (eating)
				{
					snek.Grow(patternCount);
					patternCount += 1;
					snekSegCounter += 1;
				}
				snek.MoveBy(delta_loc);
				if (eating)
				{
					goal.Respawn(rng, brd, snek);
				}
				while (wall.IsInSpot(goal.GetLocation()))
				{
					goal.Respawn(rng, brd, snek);
				}
			}
			if (snekSegCounter > 2) //after eating up two more dots
			{
				wall.NewSpot(rng, brd, snek);
				wall.NewSpot(rng, brd, snek);
				snekSegCounter = 0;
				//add two new dots and reset counter for dots eaten
				if (snekMovePeriod > 3.0f) //as long as the frames between movement is above 3 reduce it by 3
				{
					snekMovePeriod -= 3.0f;
				}
				
			}
				
		}
	}

}

void Game::ComposeFrame()
{
	

	
	snek.Draw(brd);
	goal.Draw(brd);
	wall.Draw(brd);
	
	if (gameIsOver)
	{
		SpriteCodex::DrawGameOver(200, 200, gfx);
		steady_clock::time_point end = std::chrono::steady_clock::now();
		std::chrono::duration<float> runtime = end - start;
		float durationSeconds = runtime.count();
	}
	
}
