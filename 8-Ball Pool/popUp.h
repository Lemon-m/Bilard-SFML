#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "textLabel.h"

struct PopUp
{
	PopUp(sf::Font& font, const std::string& msgString, const int& fontSize);

	PopUp(sf::Font& font, const std::string& msgString);

	void draw(sf::RenderWindow& window);

	sf::Texture popUpBg;

	sf::Sprite popUpSprite;

	TextLabel closeBtn;

	TextLabel message;
};