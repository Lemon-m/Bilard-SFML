#pragma once

#include "player.h"
#include <SFML/Graphics.hpp>

struct TextLabel;

class Turn;

class Table
{
public:
	Table(const sf::Vector2f& tablePosition, const std::string& imageDirectory, const sf::Vector2f& spriteScale, const sf::Vector2f* wallDimensions, const sf::Vector2f* wallPositions, const sf::Vector2f* holePositions);

	void drawTable(sf::RenderWindow& window);

	void drawHoveredOverHole(sf::RenderWindow& window, const int& i);

	void drawHitboxes(sf::RenderWindow& window);

	sf::RectangleShape* getWalls();

	int getWallsSize();

	int getHolesSize();

	sf::RectangleShape getWall(const int& i);

	sf::Vector2f getWallDimensions(const int& i);

	sf::Vector2f getWallPosition(const int& i);

	sf::CircleShape getHole(const int& i);

	float getHoleRadius(const int& i);

	sf::Vector2f getHolePosition(const int& i);
	
	sf::Vector2f getPosition();

	bool set8BallHoleMode(Turn& turn, Player& p1, Player& p2, const int& i, TextLabel& p1Marker, TextLabel& p2Marker, sf::CircleShape& p1MarkerArrow, sf::CircleShape& p2MarkerArrow, bool& p1MarkerActive, bool& p2MarkerActive, sf::RenderWindow& window, sf::Mouse mouse, sf::Event& event);

protected:
	sf::Texture _tTexture;
	sf::Sprite _tSprite;
	sf::RectangleShape _walls[12];
	sf::Vector2f _wallDimensions[12];
	sf::Vector2f _wallPositions[12];
	int _wallsSize;
	sf::CircleShape _holes[6];
	sf::Vector2f _holePositions[6];
	int _holesSize;
	sf::Vector2f _tablePosition;
};
