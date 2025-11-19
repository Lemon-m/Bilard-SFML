#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

struct TextLabel
{
	TextLabel(sf::Font& font, const int& fontSize, sf::Color color, sf::Color hoverColor, sf::Vector2f position, const std::string& textString);

	TextLabel(sf::Font& font, const int& fontSize, sf::Color color, sf::Vector2f position, const std::string& textString);

	bool isMouseOver(sf::RenderWindow& window);

	void changeText(const std::string& textString);

	void draw(sf::RenderWindow& window);

	sf::Text text;

	sf::Color normalColor;

	sf::Color hoverColor;
};