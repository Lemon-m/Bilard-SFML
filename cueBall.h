#pragma once
#include "ball.h"

class Turn;

class CueBall : public Ball
{
public:
	CueBall(const float& radius, const sf::Vector2f& ballPosition, const sf::Texture& texture);

	sf::RectangleShape aimLine;

	void aim(sf::RenderWindow& window, sf::Event& event, Turn& turn);

	void ballInHandMode(sf::RenderWindow& window, sf::Mouse mouse, Table& table, sf::Event& event);

	void Shoot();

	bool getAiming();

	void setAiming(bool& aiming);

	bool getBallInHand();

	void setBallInHand(bool ballInHand);

	bool getBallInHandRequest();

	void setBallInHandRequest(bool ballInHand);

	void drawBall(sf::RenderWindow& window) override;

	void handleHoleCollision(Table& table, const int& i, Turn& turn);

protected:
	bool _aiming;
	bool _ballInHand;
	bool _ballInHandRequest;
	float _rotationInRadians;
	int _force;
	int _mouseDistance;


};