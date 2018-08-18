#include "Wall.h"
#include <assert.h>



Wall::Wall(std::mt19937 & rng, const Board &brd, const Snake & snake)
{
	blockedSpots[0].Spawn(rng, brd, snake);

}

void Wall::NewSpot(std::mt19937 & rng, const Board &brd, const Snake & snake)
{
	nSpots += 1;
	blockedSpots[nSpots].Spawn(rng, brd, snake);

}

bool Wall::IsInSpot(const Location & target)
{
	for (int i = 0; i < nSpots; i++)
	{
		if (blockedSpots[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

void Wall::Draw(Board & brd) const
{
	for (int i = 0; i < nSpots; i++)
	{
		blockedSpots[i].Draw(brd);
	}
}




void Wall::BlockedSpot::Spawn(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	Location newLoc;

	std::uniform_int_distribution<int> xDist(1, brd.GetGridWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, brd.GetGridHeight() - 2);
	
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTileFull(newLoc));
	loc = newLoc;
}

const Location & Wall::BlockedSpot::GetLocation()
{
	return loc;
}

void Wall::BlockedSpot::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}
