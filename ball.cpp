#include "ball.h"
#include "table.h"
#include "turn.h"
#include "player.h"
#include "globals.h"
#include <algorithm>


Ball::Ball()
{
	//default
}

Ball::Ball(const float& radius, const sf::Vector2f& ballPosition, const sf::Texture& texture)
{
	_ballCount++;
	_ID = _ballCount;

	_rotation = 0;
	_friction = 0;
	_magnitude = 0;
	_stoppingThreshold = 7.5f;
	_velocity.x = 0;
	_velocity.y = 0;
	_ballPosition.x = ballPosition.x;
	_ballPosition.y = ballPosition.y;
	_bTexture = &texture;
	_frictionVector.x = 0;
	_frictionVector.y = 0;
	_closestWallCoordinate.x = 0;
	_closestWallCoordinate.y = 0;
	_deletionReq = false;

	ball.setRadius(radius);
	ball.setPosition(ballPosition);
	ball.setOrigin(radius, radius);
	ball.setTexture(_bTexture);
}

void Ball::drawBall(sf::RenderWindow& window)
{
	ball.setPosition(_ballPosition);
	window.draw(ball);
}

sf::Vector2f Ball::getVelocity()
{
	return _velocity;
}

void Ball::setVelocity(sf::Vector2f velocity)
{
	_velocity.x = velocity.x;
	_velocity.y = velocity.y;
}

sf::Vector2f Ball::getBallPosition()
{
	return _ballPosition;
}

sf::Vector2f Ball::getClosestWallCoordinate()
{
	return _closestWallCoordinate;
}

unsigned int Ball::getID()
{
	return _ID;
}

bool Ball::getDeletionReq()
{
	return _deletionReq;
}

void Ball::setBallPosition(const sf::Vector2f& ballPosition)
{
	_ballPosition.x = ballPosition.x;
	_ballPosition.y = ballPosition.y;
}

void Ball::calculateVelocity(const float& dt)
{
	_magnitude = std::sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
	if (_magnitude > 0)
	{
		_friction = 0.4f * _magnitude * dt;
		_frictionVector.x = _velocity.x / _magnitude * _friction;
		_frictionVector.y = _velocity.y / _magnitude * _friction;
		_velocity -= _frictionVector;
		if (std::sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y) < _stoppingThreshold)
		{
			_velocity = sf::Vector2f(0.f, 0.f);
		}
	}
}

bool Ball::checkTableCollision(Table& table, const int& i)
{
	sf::Vector2f wallPos = table.getWallPosition(i);
	sf::Vector2f wallSize = table.getWallDimensions(i);

	_closestWallCoordinate.x = std::clamp(ball.getPosition().x, wallPos.x, wallPos.x + wallSize.x);
	_closestWallCoordinate.y = std::clamp(ball.getPosition().y, wallPos.y, wallPos.y + wallSize.y);

	float distanceX = ball.getPosition().x - _closestWallCoordinate.x;
	float distanceY = ball.getPosition().y - _closestWallCoordinate.y;

	float distanceSquared = distanceX * distanceX + distanceY * distanceY;

	return distanceSquared <= ball.getRadius() * ball.getRadius();
}

bool Ball::checkBallCollision(Ball& testedBall)
{
	sf::Vector2f tBallPos = testedBall.ball.getPosition();

	float distanceFromBall = sqrt(pow(tBallPos.x - ball.getPosition().x, 2) + pow(tBallPos.y - ball.getPosition().y, 2));

	return distanceFromBall <= 2 * testedBall.ball.getRadius();
}

bool Ball::checkHoleCollision(Table& table, const int& i)
{
	sf::CircleShape hole = table.getHole(i);
	sf::Vector2f holePos = table.getHolePosition(i);

	float distanceFromHole = sqrt(pow(holePos.x - ball.getPosition().x, 2) + pow(holePos.y - ball.getPosition().y, 2));

	return distanceFromHole <= hole.getRadius();

}

bool Ball::checkTableCollision(Table& table, const int& i, const sf::Vector2f& ballPosition) // overload for corner checks
{
	sf::Vector2f wallPos = table.getWallPosition(i);
	sf::Vector2f wallSize = table.getWallDimensions(i);

	_closestWallCoordinate.x = std::clamp(ball.getPosition().x, wallPos.x, wallPos.x + wallSize.x);
	_closestWallCoordinate.y = std::clamp(ball.getPosition().y, wallPos.y, wallPos.y + wallSize.y);

	float distanceX = ballPosition.x - _closestWallCoordinate.x;
	float distanceY = ballPosition.y - _closestWallCoordinate.y;

	float distanceSquared = distanceX * distanceX + distanceY * distanceY;

	return distanceSquared <= ball.getRadius() * ball.getRadius();
}

void Ball::handleTableCollision(Table& table, const int& i)
{
	sf::Vector2f distanceVector = _ballPosition - _closestWallCoordinate;

	float distance = sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);

	if (distance == 0.f)
	{
		distance = 0.001f;
	}

	float collisionNormalX = distanceVector.x / distance;
	float collisionNormalY = distanceVector.y / distance;
	sf::Vector2f collisionNormal = { collisionNormalX, collisionNormalY };

	float overlap = ball.getRadius() - distance + 1;

	setBallPosition(getBallPosition() + collisionNormal * overlap);

	float velAlongNormal = _velocity.x * collisionNormal.x + _velocity.y * collisionNormal.y;
	//_velocity.x -= 2 * (_velocity.x * collisionNormal.x) * collisionNormal.x;
	//_velocity.y -= 2 * (_velocity.y * collisionNormal.y) * collisionNormal.y;

	_velocity -= 2.f * velAlongNormal * collisionNormal;

	_velocity *= 0.98f;

	_velocity *= 0.98f;
}

void Ball::handleBallCollision(Ball& cBall)
{
	sf::Vector2f posDiff = cBall.getBallPosition() - _ballPosition;
	float posDiffLength = sqrt(posDiff.x * posDiff.x + posDiff.y * posDiff.y);
	float collisionNormalX = posDiff.x / posDiffLength;
	float collisionNormalY = posDiff.y / posDiffLength;
	sf::Vector2f collisionNormal = { collisionNormalX, collisionNormalY };

	sf::Vector2f velDiff = _velocity - cBall.getVelocity();

	float velNormalScalar = velDiff.x * collisionNormalX + velDiff.y * collisionNormalY;

	_velocity -= velNormalScalar * collisionNormal;
	_velocity *= 0.98f;

	cBall.setVelocity(cBall.getVelocity() + velNormalScalar * collisionNormal);
	cBall.setVelocity(cBall.getVelocity() * 0.98f);

	float overlap = (ball.getRadius() + cBall.ball.getRadius()) - posDiffLength;
	if (overlap > 0.f)
	{
		sf::Vector2f correction = collisionNormal * overlap;
		_ballPosition -= correction;
		cBall.setBallPosition(cBall.getBallPosition() + correction * 0.01f);
	}
}

void Ball::handleHoleCollision(Table& table, const int& i, Turn& turn, Player& p1, Player& p2, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes, int& win)
{
	_velocity = sf::Vector2f(0, 0);
	_deletionReq = true;

	if (_ID == 8)
	{
		if (turn.isLastBall() == false)
		{
			if (turn.getCurrentPlayerID() == 1)
			{
				win = 2;
			}
			else if (turn.getCurrentPlayerID() == 2)
			{
				win = 1;
			}
		}
		else
		{
			turn.eightBallScored();
		}
	}
	else
	{
		turn.ballScored(*this, p1, p2, scoredSolids, scoredStripes);
	}
}
