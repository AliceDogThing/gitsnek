#pragma once

#include "Board.h"


class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody(int counter);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		void DrawHead(Board & brd) const;
		void MoveBy(const Location& delta_loc);
		const Location& GetLocation() const;

	private:
		Location loc;
		Color c;

	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow(int segCounter);
	void Draw(Board& brd) const;
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool IsInTile(const Location& target) const;
	bool IsInTileFull(const Location& target) const;
	int GetSegments();
private:
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	static constexpr Color headcolor = Colors::Yellow;
	static constexpr Color bodycolor = Colors::Green;
	Color bodycolor2 = { 0, 200, 0 };
	Color bodycolor3 = { 10, 180, 10 };
	Color bodycolor4 = { 0, 200, 0 };
};