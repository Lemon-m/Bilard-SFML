#include "cueBall.h"
#include "globals.h"
#include "table.h"
#include "turn.h"

CueBall::CueBall(const float& radius, const sf::Vector2f& ballPosition, const sf::Texture& texture) : Ball(radius, ballPosition, texture)
{
	_ID = 16;

	aimLine.setSize(sf::Vector2f(0, 0));
	aimLine.setPosition(ballPosition);

	_ballInHand = false;
	_ballInHandRequest = false;
	_aiming = false;
	_rotationInRadians = 0;
	_force = 0;
	_mouseDistance = 0;
}

void CueBall::aim(sf::RenderWindow& window, sf::Event& event, Turn& turn)
{
	_aiming = true;

	_rotation = (std::atan2(sf::Mouse::getPosition(window).x - _ballPosition.x, sf::Mouse::getPosition(window).y - _ballPosition.y) * 180) / pi;
	_mouseDistance = sqrt(pow((_ballPosition.x) - sf::Mouse::getPosition(window).x, 2) + pow((_ballPosition.y) - sf::Mouse::getPosition(window).y, 2));

	aimLine.setPosition(_ballPosition);
	aimLine.setSize(sf::Vector2f(3, _mouseDistance));
	aimLine.setRotation(-_rotation);

	_force = _mouseDistance - 40;

	if (_force > 150)
	{
		_force = 150;
	}
	else if (_force < 15)
	{
		_force = 15;
	}

	_force *= 5;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		Shoot();
		turn.cueBallShot();
	}

	//std::cout << "force: " << _force << "\n";
	//std::cout << "Mouse Distance: " << _mouseDistance << "\n";
	//std::cout << "rotation: " << _rotation << "\n";
}

void CueBall::ballInHandMode(sf::RenderWindow& window, sf::Mouse mouse, Table& table, sf::Event& event)
{
	float x = std::clamp(mouse.getPosition(window).x, static_cast<int>(table.getPosition().x + 65 + ball.getRadius()), static_cast<int>(table.getPosition().x + tableX - 65 - ball.getRadius()));
	float y = std::clamp(mouse.getPosition(window).y, static_cast<int>(table.getPosition().y + 64 + ball.getRadius()), static_cast<int>(table.getPosition().y + tableY - 64 - ball.getRadius()));
	_ballPosition = sf::Vector2f(x, y);

	if (event.type == sf::Event::MouseButtonPressed)
	{
		_ballInHand = false;
	}
}

void CueBall::Shoot()
{
	_aiming = false;
	_rotationInRadians = (_rotation * (pi / 180)) - 1.57079633; // 1.57079633 rad = 90 degrees
	_velocity.x = -(_force * cos(_rotationInRadians));
	_velocity.y = _force * sin(_rotationInRadians);
	aimLine.setSize(sf::Vector2f(0, 0));

	//std::cout << "Hit\n";
	//std::cout << "rotation in radians: " << _rotationInRadians << "\n";
}

bool CueBall::getAiming()
{
	return _aiming;
}

void CueBall::setAiming(bool& aiming)
{
	_aiming = aiming;
}

bool CueBall::getBallInHand()
{
	return _ballInHand;
}

void CueBall::setBallInHand(bool ballInHand)
{
	_ballInHand = ballInHand;
}

bool CueBall::getBallInHandRequest()
{
	return _ballInHandRequest;
}

void CueBall::setBallInHandRequest(bool ballInHandRequest)
{
	_ballInHandRequest = ballInHandRequest;
}

void CueBall::drawBall(sf::RenderWindow& window)
{
	ball.setPosition(_ballPosition);
	window.draw(aimLine);
	window.draw(ball);

}

void CueBall::handleHoleCollision(Table& table, const int& i, Turn& turn)
{
	_ballInHandRequest = true;
	turn.setSwitchRequest(true);
	_velocity = sf::Vector2f(0.f, 0.f);
	aimLine.setSize(sf::Vector2f(0, 0));
	setBallPosition(sf::Vector2f(1220, 920));
}
