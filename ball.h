#pragma once
#include "player.h"
#include <SFML/Graphics.hpp>

class Table;

class Turn;

class Ball
{
public:

	Ball();

	Ball(const float& radius, const sf::Vector2f& ballPosition, const sf::Texture& texture);

	virtual void drawBall(sf::RenderWindow& window);

	sf::Vector2f getVelocity();

	sf::Vector2f getBallPosition();

	sf::Vector2f getClosestWallCoordinate();

	unsigned int getID();

	bool getDeletionReq();

	void setVelocity(sf::Vector2f velocity);

	void setBallPosition(const sf::Vector2f& ballPosition);

	void calculateVelocity(const float& dt);

	bool checkTableCollision(Table& table, const int& i);

	bool checkBallCollision(Ball& testedBall);

	bool checkHoleCollision(Table& table, const int& i);

	bool checkTableCollision(Table& table, const int& i, const sf::Vector2f& ballPosition);

	void handleTableCollision(Table& table, const int& i);

	void handleBallCollision(Ball& cBall);

	void handleHoleCollision(Table& table, const int& i, Turn& turn, Player& p1, Player& p, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes, int& win);

	sf::CircleShape ball;

protected:
	const sf::Texture* _bTexture;
	sf::Vector2f _ballPosition;
	sf::Vector2f _velocity;
	sf::Vector2f _frictionVector;
	sf::Vector2f _closestWallCoordinate;
	unsigned int _ID;
	float _rotation;
	float _friction;
	float _magnitude;
	float _stoppingThreshold;
	bool _deletionReq;

private:
	unsigned static int _ballCount;

};