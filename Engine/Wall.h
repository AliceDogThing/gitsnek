#pragma once

#include "Snake.h"

#include "Board.h"
#include <random>

class Wall
{
public:

	Wall(std::mt19937& rng, const Board& brd, const Snake& snake);
	void NewSpot(std::mt19937 & rng, const Board &brd, const Snake & snake);
	bool IsInSpot(const Location& target);
	void Draw( Board& brd) const;
private:


	class BlockedSpot
	{
	private:
		
		Location loc;
		static constexpr Color c = Colors::White;
	public:
		void Spawn(std::mt19937& rng, const Board& brd, const Snake& snake);
		const Location& GetLocation();
		void Draw(Board& brd) const;
		
	};


	
private:
	
	static constexpr int nSpotsMax = 100;
	BlockedSpot blockedSpots[nSpotsMax];
	
	int nSpots = 0;
	
};