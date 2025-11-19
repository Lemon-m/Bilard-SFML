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

	static void resetBallCount();

	virtual void drawBall(sf::RenderWindow& window, const bool& rotationOn);

	sf::Vector2f getVelocity();

	sf::Vector2f getBallPosition();

	sf::Vector2f getClosestWallCoordinate();

	unsigned int getID();

	bool getDeletionReq();

	void setVelocity(sf::Vector2f velocity);

	void setBallRotation(const float& rotation);

	void setBallPosition(const sf::Vector2f& ballPosition);

	float getMagnitude();

	float getAngularVelocity();

	float getRotation();

	void calculateVelocity(const float& dt, const bool& rotationOn);

	bool checkTableCollision(Table& table, const int& i);

	bool checkBallCollision(Ball& testedBall);

	bool checkHoleCollision(Table& table, const int& i);

	bool checkTableCollision(Table& table, const int& i, const sf::Vector2f& ballPosition);

	void handleTableCollision(Table& table, const int& i);

	void handleBallCollision(Ball& cBall);

	void handleHoleCollision(Table& table, const int& i, Turn& turn, Player& p1, Player& p2, std::vector<int>& scoredSolids, std::vector<int>& scoredStripes, std::vector<sf::Sprite>& scoredSolidsUI, std::vector<sf::Sprite>& scoredStripesUI, sf::Vector2f& p1FirstUIBallPos, sf::Vector2f& p2FirstUIBallPos, int& win);

	sf::CircleShape ball;

protected:
	const sf::Texture* _bTexture;
	sf::Vector2f _ballPosition;
	sf::Vector2f _velocity;
	sf::Vector2f _frictionVector;
	sf::Vector2f _closestWallCoordinate;
	unsigned int _ID;
	float _rotation; // rad
	float _angularVelocity; // rad
	float _friction;
	float _magnitude;
	float _stoppingThreshold;
	bool _deletionReq;

	unsigned static int _ballCount;

};