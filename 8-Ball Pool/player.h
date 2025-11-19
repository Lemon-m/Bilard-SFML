#pragma once
#include <vector>

struct Player
{
	int ID;
	int ballType = 0; // 0 - open table | 1 - solids | 2 - stripes
	int score = 0;
	int eightBallHoleID;
	bool eightBallHoleSet = false;

	Player(int id) : ID(id) {}
};