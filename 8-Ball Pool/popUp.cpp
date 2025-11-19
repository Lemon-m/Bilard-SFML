#include "popUp.h"

PopUp::PopUp(sf::Font& font, const std::string& msgString, const int& fontSize) : PopUp(font, msgString)
{
	message.text.setCharacterSize(fontSize);
	message.changeText(msgString);
}

PopUp::PopUp(sf::Font& font, const std::string& msgString) : closeBtn(font, 64, sf::Color(255, 0, 37), sf::Color(255, 54, 85), sf::Vector2f(845.f, 295.f), "×"),
message(font, 48, sf::Color::White, sf::Vector2f(600.f, 430.f), msgString)
{
	popUpBg.loadFromFile("assets/popup.png");
	popUpSprite.setTexture(popUpBg);
	popUpSprite.setPosition(sf::Vector2f(0.f, 0.f));
}

void PopUp::draw(sf::RenderWindow& window)
{
	window.draw(popUpSprite);
	closeBtn.draw(window);
	message.draw(window);
}