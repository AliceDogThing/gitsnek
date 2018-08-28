#pragma once

#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell( const Location& loc, Color c);
	void DrawSnakeSegs(const Location & loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	int GetBuffer() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder(Color c);
private:
	static constexpr int dimension = 20;
	static constexpr int width = 40;
	static constexpr int height = 30;
	static constexpr int borderBuffer = 5;
	Graphics& gfx;


};