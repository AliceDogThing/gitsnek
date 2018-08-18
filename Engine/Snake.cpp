#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow(int segCounter)
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody(segCounter);
		++nSegments;
		
	}
}

void Snake::Draw(Board & brd) const
{
	segments[0].DrawHead(brd);
	for (int i = 1; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l = segments[0].GetLocation();
	l.Add(delta_loc);
	return l;
}

bool Snake::IsInTile(const Location& target) const
{
	//ensures that snake can move its head to where its tail was the frame before
	for (int i = 0; i < nSegments-1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTileFull(const Location & target) const
{
	//checks for the entire snake's position to ensure goal will not spawn on it
	for (int i = 1; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

int Snake::GetSegments()
{
	return nSegments;
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headcolor;
}

void Snake::Segment::InitBody(int counter)
{
	if (counter % 4 == 0)
	{
		c = Snake::bodycolor;
	}
	else if (counter % 4 == 1)
	{
		c = { 0 , 200, 0 };
	}
	else if (counter % 4 == 2)
	{
		c = { 20, 180, 20 };
	}
	else if (counter % 4 == 3)
	{
		c = { 0 , 200, 0 };
	}
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd) const
{

	brd.DrawCell(loc , c);
}

void Snake::Segment::DrawHead(Board& brd) const
{

	brd.DrawCell(loc, c);
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
