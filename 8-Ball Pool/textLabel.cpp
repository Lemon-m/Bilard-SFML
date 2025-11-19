#include "textLabel.h"
#include "popUp.h"

TextLabel::TextLabel(sf::Font& font, const int& fontSize, sf::Color color, sf::Color hColor, sf::Vector2f position, const std::string& textString) : TextLabel(font, fontSize, color, position, textString)
{
	hoverColor = hColor;
}

TextLabel::TextLabel(sf::Font& font, const int& fontSize, sf::Color color, sf::Vector2f position, const std::string& textString)
{
	text.setFont(font);
	text.setFillColor(color);
	normalColor = color;
	hoverColor = color;
	text.setCharacterSize(fontSize);
	text.setString(textString);
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(position);
}

bool TextLabel::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x;
	float mouseY = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y;

	if (text.getGlobalBounds().contains(mouseX, mouseY))
	{
		text.setFillColor(hoverColor);
		return true;
	}
	else
	{
		text.setFillColor(normalColor);
		return false;
	}
}

void TextLabel::changeText(const std::string& textString)
{
	sf::Vector2f currentPos = text.getPosition();
	text.setString(textString);
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(currentPos);
}

void TextLabel::draw(sf::RenderWindow& window)
{
	window.draw(text);
}
