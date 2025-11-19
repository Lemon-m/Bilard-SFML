#pragma once
#include "player.h"

class Ball;

class CueBall;

class Turn
{
	public:

		Turn(const Player& p, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes, bool openTableMode);

		Turn(const Player& p, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes);

		void cueBallCollision();

		void wallHit();

		void cueBallShot();

		void firstBallIDSetAndCheck(Ball& ball, CueBall& cueBall, int& win);

		void setSwitchRequest(bool switchReq);

		void set8BallHoleSetMode(bool EightBallHoleSetMode);

		void setHoveredOverHoleID(const int& hoveredOverHoleID);

		void setTeams(Player& p1, Player& p2, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes, CueBall& cueBall);

		void ballScored(Ball& ball, Player& p1, Player& p2, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes);

		void eightBallScored();

		int getCueBallCollisions();

		int getCurrentPlayerTeam();

		int getCurrentPlayerID();

		int getScoredBallsCounter();

		int getScoredSolidsCounter();

		int getScoredStripesCounter();

		int getWallCollisionCounter();

		int getHoveredOverHoleID();

		bool getSwitchReq();

		bool getCueBallShot();

		bool getOpenTableMode();

		bool isLastBall();

		bool get8BallScored();

		bool get8ballHoleSetMode();

	protected:

		Player _p;
		int _wallCollisionCounter;
		int _cueBallCollisions;
		int _scoredBallsCounter;
		int _scoredSolidsCounter;
		int _scoredStripesCounter;
		int _firstBallID;
		int _hoveredOverHoleID;
		bool _openTableMode;
		bool _switchReq;
		bool _cueBallShot;
		bool _lastBall;
		bool _8BallScored;
		bool _8ballHoleSetMode;
};