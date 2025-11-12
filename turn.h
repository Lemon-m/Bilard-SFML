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

		void setTeams(Player& p1, Player& p2, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes, CueBall& cueBall);

		void ballScored(Ball& ball, Player& p1, Player& p2, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes);

		void eightBallScored();

		int getCueBallCollisions();

		int getCurrentPlayerTeam();

		int getCurrentPlayerID();

		int getScoredBallsCounter();

		int getWallCollisionCounter();

		bool getSwitchReq();

		bool getCueBallShot();

		bool getOpenTableMode();

		bool isLastBall();

		bool get8BallScored();

	protected:

		Player _p;
		int _wallCollisionCounter;
		int _cueBallCollisions;
		int _scoredBallsCounter;
		int _firstBallID;
		bool _openTableMode;
		bool _switchReq;
		bool _cueBallShot;
		bool _lastBall;
		bool _8BallScored;
};