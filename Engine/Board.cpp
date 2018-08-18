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

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 1 && loc.x < width-1
		&& loc.y >= 1 && loc.y < height-1;
}

void Board::DrawBorder(Color c)
{
	
	for (int i = 0; i < width; i++)
	{
		Location borderLoc{ i, 0 };
		DrawCell(borderLoc, c);
	}
	for (int i = 0; i < height; i++)
	{
		Location borderLoc{ 0, i };
		DrawCell(borderLoc, c);
	}
	for (int i = 0; i < width; i++)
	{
		Location borderLoc{ i, height-1 };
		DrawCell(borderLoc, c);
	}
	for (int i = 0; i < height; i++)
	{
		Location borderLoc{ width-1, i };
		DrawCell(borderLoc, c);
	}
}
