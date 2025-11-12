#include "turn.h"
#include "ball.h"
#include "cueBall.h"
#include "globals.h"
#include <iostream>

Turn::Turn(const Player& p, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes, bool openTableMode)
{
	_p = p;
	_wallCollisionCounter = 0;
	_cueBallCollisions = 0;
	_scoredBallsCounter = 0;
	_firstBallID = 0;
	_switchReq = false;
	_cueBallShot = false;
	_openTableMode = openTableMode;
	if ((_p.ballType == 1 && scoredSolids.size() == 7) || (_p.ballType == 2 && scoredStripes.size() == 7))
	{
		_lastBall = true;
	}
	else
	{
		_lastBall = false;
	}
	_8BallScored = false;
}

Turn::Turn(const Player& p, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes)
{
	_p = p;
	_wallCollisionCounter = 0;
	_cueBallCollisions = 0;
	_scoredBallsCounter = 0;
	_firstBallID = 0;
	_switchReq = false;
	_cueBallShot = false;
	_openTableMode = false;
	if ((_p.ballType == 1 && scoredSolids.size() == 7) || (_p.ballType == 2 && scoredStripes.size() == 7))
	{
		_lastBall = true;
	}
	else
	{
		_lastBall = false;
	}
	_8BallScored = false;
}

void Turn::cueBallCollision()
{
	_cueBallCollisions++;
}

void Turn::wallHit()
{
	_wallCollisionCounter++;
}

void Turn::cueBallShot()
{
	_cueBallShot = true;
}

void Turn::firstBallIDSetAndCheck(Ball& ball, CueBall& cueBall, int &win)
{

	_firstBallID = ball.getID();
	if ( (_p.ballType == 1 && stripes.count(_firstBallID)) || (_p.ballType == 2 && solids.count(_firstBallID)) )
	{
		_switchReq = true;
		cueBall.setBallInHandRequest(true);
	}

	else if (ball.getID() == 8 && _lastBall == false)
	{
		if (_p.ID == 1)
		{
			win = 2;
		}
		else if (_p.ID == 2)
		{
			win = 1;
		}
	}
}

void Turn::setSwitchRequest(bool switchReq)
{
	_switchReq = switchReq;
}

void Turn::setTeams(Player& p1, Player& p2, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes, CueBall& cueBall)
{
	if (scoredSolids.size() > scoredStripes.size())
	{
		if (_p.ID == p1.ID)
		{
			p1.ballType = 1;
			p2.ballType = 2;
			p1.score = scoredSolids.size();
			p2.score = scoredStripes.size();
		}
		else if (_p.ID == p2.ID)
		{
			p2.ballType = 1;
			p1.ballType = 2;
			p2.score = scoredSolids.size();
			p1.score = scoredStripes.size();
		}
		_p.ballType = 1;
		_p.score = scoredSolids.size();
		_scoredBallsCounter = scoredSolids.size();
	}
	else if (scoredSolids.size() < scoredStripes.size())
	{
		if (_p.ID == p1.ID)
		{
			p1.ballType = 2;
			p2.ballType = 1;
			p1.score = scoredStripes.size();
			p2.score = scoredSolids.size();
		}
		else if (_p.ID == p2.ID)
		{
			p2.ballType = 2;
			p1.ballType = 1;
			p2.score = scoredStripes.size();
			p2.score = scoredSolids.size();

		}
		_p.ballType = 2;
		_p.score = scoredStripes.size();
		_scoredBallsCounter = scoredStripes.size();
	}
	_openTableMode = false;
	if (cueBall.getBallInHandRequest() == false)
	{
		_switchReq = false;
	}

	std::cout << "Ustalono dru¿yny!\nTyp bili gracza 1 - " << p1.ballType << "\nTyp bili gracza 2 - " << p2.ballType << "\nLicznik wbiytch bili w turze przez aktualnego gracza - " << _scoredBallsCounter << "\nUstalono z faulem? - " << cueBall.getBallInHandRequest() << "\nZmiana tur? - " << _switchReq << "\n";
}

void Turn::ballScored(Ball& ball, Player& p1, Player& p2, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes)
{
	if (solids.count(ball.getID()))
	{
		scoredSolids.push_back(ball.getID());
		if (p1.ballType == 1)
		{
			p1.score++;
		}
		else if (p2.ballType == 1)
		{
			p2.score++;
		}
		if (_p.ballType == 1)
		{
			_p.score++;
			_scoredBallsCounter++;
		}
	}
	else if (stripes.count(ball.getID()))
	{
		scoredStripes.push_back(ball.getID());
		if (p1.ballType == 2)
		{
			p1.score++;
		}
		else if (p2.ballType == 2)
		{
			p2.score++;
		}
		if (_p.ballType == 2)
		{
			_p.score++;
			_scoredBallsCounter++;
		}
	}
}

void Turn::eightBallScored()
{
	_8BallScored = true;
}

int Turn::getCueBallCollisions()
{
	return _cueBallCollisions;
}

int Turn::getCurrentPlayerTeam()
{
	return _p.ballType;
}

int Turn::getCurrentPlayerID()
{
	return _p.ID;
}

int Turn::getScoredBallsCounter()
{
	return _scoredBallsCounter;
}

int Turn::getWallCollisionCounter()
{
	return _wallCollisionCounter;
}

bool Turn::getSwitchReq()
{
	return _switchReq;
}

bool Turn::getCueBallShot()
{
	return _cueBallShot;
}

bool Turn::getOpenTableMode()
{
	return _openTableMode;
}

bool Turn::isLastBall()
{
	return _lastBall;
}

bool Turn::get8BallScored()
{
	return _8BallScored;
}
