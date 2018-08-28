#include "Goal.h"

Goal::Goal(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(1+brd.GetBuffer(), brd.GetGridWidth() - (2+brd.GetBuffer()));
	std::uniform_int_distribution<int> yDist(1+brd.GetBuffer(), brd.GetGridHeight() - (2+brd.GetBuffer()));
	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
		//avoid placing where snake already is
	} while (snake.IsInTileFull(newLoc));
	loc = newLoc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & Goal::GetLocation()
{
	return loc;
}

bool Goal::IsInTile(const Location & target)
{
	return (loc == target);
}

