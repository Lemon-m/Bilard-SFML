#pragma once
#include "state.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "game.h"
#include "textLabel.h"

class TutorialState : public State
{
public:
	TutorialState(Game& game);

	void handleEvent(sf::Event& event) override;

	void update(float dt) override;

	void render(sf::RenderWindow& window) override;

	void leftButtonPressed();

	void rightButtonPressed();

protected:

	sf::Texture _bgTexture;
	sf::Sprite _bg;
	std::array<sf::Texture, 24> _tutorialSlidesTextures;
	std::array<sf::Sprite, 24> _tutorialSlides;
	TextLabel _currentSlideText1;
	TextLabel _currentSlideText2;
	TextLabel _currentSlideText3;
	TextLabel _leftButton;
	TextLabel _rightButton;
	int _currentSlide;
};