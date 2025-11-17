#include "table.h"
#include "turn.h"
#include "textLabel.h"
#include <iostream>

Table::Table(const sf::Vector2f& tablePosition, const std::string& imageDirectory, const sf::Vector2f& spriteScale, const sf::Vector2f* wallDimensions, const sf::Vector2f* wallPositions, const sf::Vector2f* holePositions)
{
	if (!_tTexture.loadFromFile(imageDirectory))
	{
		std::cerr << "Error\n";
	}

	_wallsSize = sizeof(_walls) / sizeof(_walls[0]);

	_holesSize = sizeof(_holes) / sizeof(_holes[0]);

	_tSprite.setTexture(_tTexture);

	_tSprite.setScale(spriteScale);

	_tablePosition = tablePosition;
	_tSprite.setPosition(_tablePosition);

	for (int i = 0; i < sizeof(_walls) / sizeof(_walls[0]); i++)
	{
		_wallDimensions[i] = wallDimensions[i];
		_wallPositions[i] = wallPositions[i] + _tablePosition;
		_walls[i].setSize(_wallDimensions[i]);
		_walls[i].setPosition(_wallPositions[i]);
		_walls[i].setFillColor(sf::Color(255, 0, 0));
	}

	for (int i = 0; i < sizeof(_holes) / sizeof(_holes[0]); i++)
	{
		_holePositions[i] = holePositions[i] + _tablePosition;
		_holes[i].setRadius(27);
		_holes[i].setOrigin(_holes[i].getRadius(), _holes[i].getRadius());
		_holes[i].setPosition(_holePositions[i]);
		_holes[i].setFillColor(sf::Color(0, 255, 0));
	}

	_holes[1].setRadius(24); // middle holes are smaller shoutout to the texture guy
	_holes[1].setOrigin(24, 24);
	_holes[1].setPosition(_holePositions[1]);

	_holes[4].setRadius(24); // same here
	_holes[4].setOrigin(24, 24);
	_holes[4].setPosition(_holePositions[4]);
}

void Table::drawTable(sf::RenderWindow& window)
{
	window.draw(_tSprite);
}

void Table::drawHoveredOverHole(sf::RenderWindow& window, const int& i)
{
	window.draw(_holes[i]);
}

void Table::drawHitboxes(sf::RenderWindow& window)
{
	for (int i = 0; i < sizeof(_walls) / sizeof(_walls[0]); i++)
	{
		window.draw(_walls[i]);
	}

	for (int i = 0; i < sizeof(_holes) / sizeof(_holes[0]); i++)
	{
		window.draw(_holes[i]);
	}
}

sf::RectangleShape* Table::getWalls()
{
	return _walls;
}

int Table::getWallsSize()
{
	return _wallsSize;
}

int Table::getHolesSize()
{
	return _holesSize;
}

sf::RectangleShape Table::getWall(const int& i)
{
	try
	{
		if (i >= 0 && i < sizeof(_walls) / sizeof(_walls[0]))
		{
			return _walls[i];
		}
		else
		{
			throw(i);
		}
	}
	catch (int i)
	{
		std::cout << "i variable must be within the range of the count of elements in the _walls table\n";
		std::cout << "i value: " << i << "\n";

		return sf::RectangleShape(sf::Vector2f(0, 0));
	}
}

sf::Vector2f Table::getWallDimensions(const int& i)
{
	try
	{
		if (i >= 0 && i < sizeof(_walls) / sizeof(_walls[0]))
		{
			return _wallDimensions[i];
		}
		else
		{
			throw(i);
		}
	}
	catch (int i)
	{
		std::cout << "i variable must be within the range of the count of elements in the _wallDimensions table\n";
		std::cout << "i value: " << i << "\n";

		return sf::Vector2f(0, 0);
	}
}

sf::Vector2f Table::getWallPosition(const int& i)
{
	try
	{
		if (i >= 0 && i < sizeof(_walls) / sizeof(_walls[0]))
		{
			return _wallPositions[i];
		}
		else
		{
			throw(i);
		}
	}
	catch (int i)
	{
		std::cout << "i variable must be within the range of the count of elements in the _wallPositions table\n";
		std::cout << "i value: " << i << "\n";

		return sf::Vector2f(0, 0);
	}
}

sf::CircleShape Table::getHole(const int& i)
{
	try
	{
		if (i >= 0 && i < sizeof(_holes) / sizeof(_holes[0]))
		{
			return _holes[i];
		}
		else
		{
			throw(i);
		}
	}
	catch (int i)
	{
		std::cout << "i variable must be within the range of the count of elements in the _holes table\n";
		std::cout << "i value: " << i << "\n";

		return sf::CircleShape(0);
	}
}

float Table::getHoleRadius(const int& i)
{
	try
	{
		if (i >= 0 && i < sizeof(_holes) / sizeof(_holes[0]))
		{
			return _holes[i].getRadius();
		}
		else
		{
			throw(i);
		}
	}
	catch (int i)
	{
		std::cout << "i variable must be within the range of the count of elements in the _holes table\n";
		std::cout << "i value: " << i << "\n";

		return 0.0f;
	}
}

sf::Vector2f Table::getHolePosition(const int& i)
{
	try
	{
		if (i >= 0 && i < sizeof(_holes) / sizeof(_holes[0]))
		{
			return _holePositions[i];
		}
		else
		{
			throw(i);
		}
	}
	catch (int i)
	{
		std::cout << "i variable must be within the range of the count of elements in the _wallPositions table\n";
		std::cout << "i value: " << i << "\n";

		return sf::Vector2f(0, 0);
	}
}

sf::Vector2f Table::getPosition()
{
	return _tablePosition;
}

bool Table::set8BallHoleMode(Turn& turn, Player& p1, Player& p2, const int& i, TextLabel& p1Marker, TextLabel& p2Marker, sf::CircleShape& p1MarkerArrow, sf::CircleShape& p2MarkerArrow, bool& p1MarkerActive, bool& p2MarkerActive, sf::RenderWindow& window, sf::Mouse mouse, sf::Event& event)
{
	sf::Vector2f disctanceVector;
	disctanceVector.x  = _holes[i].getPosition().x - window.mapPixelToCoords(mouse.getPosition(window)).x;
	disctanceVector.y = _holes[i].getPosition().y - window.mapPixelToCoords(mouse.getPosition(window)).y;
	float distance = sqrt(disctanceVector.x * disctanceVector.x + disctanceVector.y * disctanceVector.y);

	if (distance <= _holes[i].getRadius())
	{
		_holes[i].setFillColor(sf::Color(0, 255, 0, 128));
		turn.setHoveredOverHoleID(i);
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (turn.getCurrentPlayerID() == 1)
			{
				std::cout << "Gracz nr. 1 musi trafiæ ósemk¹ do ³uzy " << i << "\n";
				p1.eightBallHoleID = i;
				p1.eightBallHoleSet = true;
				turn.set8BallHoleSetMode(false);

				if (p2MarkerActive == true && p2.eightBallHoleID == i)
				{
					p2Marker.changeText("P1, P2");
				}
				else
				{
					switch (i)
					{
						case 0: case 1: case 2:
							p1MarkerArrow.setRotation(180);
							p1MarkerArrow.setPosition(_holes[i].getPosition().x, _holes[i].getPosition().y - 40.f);
							p1Marker.text.setPosition(_holes[i].getPosition().x - 1.f, _holes[i].getPosition().y - 50.f);
							break;
						case 3: case 4: case 5:
							p1MarkerArrow.setPosition(_holes[i].getPosition().x, _holes[i].getPosition().y + 40.f);
							p1Marker.text.setPosition(_holes[i].getPosition().x - 1.f, _holes[i].getPosition().y + 50.f);
							break;
						default:
							break;
					}
					p1MarkerActive = true;
				}
			}
			else if (turn.getCurrentPlayerID() == 2)
			{
				std::cout << "Gracz nr. 2 musi trafiæ ósemk¹ do ³uzy " << i << "\n";
				p2.eightBallHoleID = i;
				p2.eightBallHoleSet = true;
				turn.set8BallHoleSetMode(false);

				if (p1MarkerActive == true && p1.eightBallHoleID == i)
				{
					p1Marker.changeText("P1, P2");
				}
				else
				{
					switch (i)
					{
						case 0: case 1: case 2:
							p2MarkerArrow.setRotation(180);
							p2MarkerArrow.setPosition(_holes[i].getPosition().x, _holes[i].getPosition().y - 40.f);
							p2Marker.text.setPosition(_holes[i].getPosition().x - 1.f, _holes[i].getPosition().y - 50.f);
							break;
						case 3: case 4: case 5:
							p2MarkerArrow.setPosition(_holes[i].getPosition().x, _holes[i].getPosition().y + 40.f);
							p2Marker.text.setPosition(_holes[i].getPosition().x - 1.f, _holes[i].getPosition().y + 50.f);
							break;
						default:
							break;
					}
					p2MarkerActive = true;
				}
			}
		}
		return true;
	}
	else
	{
		_holes[i].setFillColor(sf::Color(0, 255, 0));
		turn.setHoveredOverHoleID(-1);
		return false;
	}
}

