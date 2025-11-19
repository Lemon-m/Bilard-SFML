#include "cueBall.h"
#include "globals.h"
#include "table.h"
#include "turn.h"

CueBall::CueBall(const float& radius, const sf::Vector2f& ballPosition, const sf::Texture& texture) : Ball(radius, ballPosition, texture)
{
	_ID = 16;
	_ballCount--;

	cueStickTexture.loadFromFile("assets/cue.png");

	cueStick.setTexture(cueStickTexture);
	cueStick.setOrigin(0.f, 15.f);
	cueStick.setPosition(ballPosition);

	hitForceBar.setFillColor(sf::Color::Red);
	hitForceBar.setSize(sf::Vector2f(198.f, 5.f));
	hitForceBar.setOrigin(-121.f, 15.f);
	hitForceBar.setPosition(ballPosition);

	hitForce.setFillColor(sf::Color::Green);
	hitForce.setSize(sf::Vector2f(0.f, 5.f));
	hitForce.setOrigin(-121.f, 15.f);
	hitForce.setPosition(ballPosition);

	_ballInHand = false;
	_ballInHandRequest = false;
	_aiming = false;
	_shotAngle = 0;
	_angleInRadians = 0;
	_force = 0;
	_mouseDistance = 0;
}

void CueBall::aim(sf::RenderWindow& window, sf::Event& event, Turn& turn)
{
	_aiming = true;

	_shotAngle = (std::atan2(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x - _ballPosition.x, window.mapPixelToCoords(sf::Mouse::getPosition(window)).y - _ballPosition.y) * 180) / pi;
	_mouseDistance = sqrt(pow((_ballPosition.x) - window.mapPixelToCoords(sf::Mouse::getPosition(window)).x, 2) + pow((_ballPosition.y) - window.mapPixelToCoords(sf::Mouse::getPosition(window)).y, 2));

	//aimLine.setPosition(_ballPosition);
	//aimLine.setSize(sf::Vector2f(3, _mouseDistance));
	//aimLine.setRotation(-_rotation);

	cueStick.setPosition(_ballPosition);
	cueStick.setRotation(-_shotAngle + 90);

	hitForceBar.setPosition(_ballPosition);
	hitForceBar.setRotation(-_shotAngle + 90);

	hitForce.setPosition(_ballPosition);

	float hitForceLength = (std::clamp(_mouseDistance, 55, 190) * 1.465) - 80;

	hitForce.setSize(sf::Vector2f(hitForceLength, 5.f));
	hitForce.setRotation(-_shotAngle + 90);

	_force = _mouseDistance - 40; // force = 75 (max mouseDistance = 55) | force = 150 (min mouseDistance = 190)
	_force = std::clamp(_force, 15, 150);
	_force *= 5;

	if (event.type == sf::Event::MouseButtonReleased)
	{
		Shoot();
		turn.cueBallShot();
	}

	//std::cout << "force: " << _force << "\n";
	//std::cout << "Mouse Distance: " << _mouseDistance << "\n";
	//std::cout << "rotation: " << _rotation << "\n";
}

void CueBall::ballInHandMode(sf::RenderWindow& window, sf::Mouse mouse, Table& table, sf::Event& event, const bool& openTable)
{
	float x;
	if (openTable == true)
	{
		x = std::clamp(static_cast<int>(window.mapPixelToCoords(mouse.getPosition(window)).x), static_cast<int>(table.getPosition().x + 741), static_cast<int>(table.getPosition().x + tableX - 65 - ball.getRadius()));
	}
	else
	{
		x = std::clamp(static_cast<int>(window.mapPixelToCoords(mouse.getPosition(window)).x), static_cast<int>(table.getPosition().x + 65 + ball.getRadius()), static_cast<int>(table.getPosition().x + tableX - 65 - ball.getRadius()));
	}
	float y = std::clamp(static_cast<int>(window.mapPixelToCoords(mouse.getPosition(window)).y), static_cast<int>(table.getPosition().y + 64 + ball.getRadius()), static_cast<int>(table.getPosition().y + tableY - 64 - ball.getRadius()));
	_ballPosition = sf::Vector2f(x, y);

	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		_ballInHand = false;
	}
}

void CueBall::Shoot()
{
	_aiming = false;
	_angleInRadians = (_shotAngle * (pi / 180)) - 1.57079633; // 1.57079633 rad = 90 degrees
	_velocity.x = -(_force * cos(_angleInRadians));
	_velocity.y = _force * sin(_angleInRadians);
	hitForce.setSize(sf::Vector2f(0.f, 5.f));

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

int CueBall::getForce()
{
	return _force;
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

void CueBall::drawBall(sf::RenderWindow& window, const bool& rotationOn)
{
	ball.setPosition(_ballPosition);
	if (rotationOn == true)
	{
		ball.setRotation(_rotation * (180 / pi));
	}

	if (_aiming == true)
	{
		window.draw(cueStick);
		window.draw(hitForceBar);
		window.draw(hitForce);
	}
	//window.draw(aimLine);
	window.draw(ball);

}

void CueBall::handleHoleCollision(Table& table, const int& i, Turn& turn)
{
	_ballInHandRequest = true;
	turn.setSwitchRequest(true);
	_velocity = sf::Vector2f(0.f, 0.f);
	hitForce.setSize(sf::Vector2f(0.f, 5.f));
	setBallPosition(sf::Vector2f(1220, 920));
}
