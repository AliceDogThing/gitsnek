#include "Board.h"

Board::Board(Graphics & gfx)
	:
	gfx(gfx)

{

}

void Board::DrawCell(const Location & loc, Color c)
{
	//drawing code used for head
	/*
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	*/
	gfx.DrawRectDim(loc.x * dimension + 1, loc.y * dimension + 1, dimension - 1, dimension - 1, c);

}

void Board::DrawSnakeSegs(const Location & loc, Color c)
{
	//drawing code used for segments to make a pattern
	/*
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	*/
	gfx.DrawRectSnake(loc.x * dimension + 1, loc.y * dimension + 1, dimension - 1, dimension - 1, c);

}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetBuffer() const
{
	return borderBuffer;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= (1+borderBuffer) && loc.x < width-(1+borderBuffer)
		&& loc.y >= (1+borderBuffer) && loc.y < height-(1+borderBuffer);
}

void Board::DrawBorder(Color c)
{
	
	for (int i = borderBuffer; i < width- borderBuffer; i++)
	{
		Location borderLoc{ i, borderBuffer };
		DrawCell(borderLoc, c);
	}
	for (int i = borderBuffer; i < height- borderBuffer; i++)
	{
		Location borderLoc{ borderBuffer, i };
		DrawCell(borderLoc, c);
	}
	for (int i = borderBuffer; i < width- borderBuffer; i++)
	{
		Location borderLoc{ i, height-(1+ borderBuffer) };
		DrawCell(borderLoc, c);
	}
	for (int i = borderBuffer; i < height- borderBuffer; i++)
	{
		Location borderLoc{ width-(1+ borderBuffer), i };
		DrawCell(borderLoc, c);
	}
}
