#include "mainMenuState.h"
#include "game.h"
#include "playState.h"
#include "tutorialState.h"
#include "ball.h"
#include <memory>
#include <stack>

MainMenuState::MainMenuState(Game& game) : State(game),
_playButton(_game.frutiger, 48, sf::Color::Black, sf::Color(102, 102, 102), sf::Vector2f(600.f, 375.f), "Play"),
_tutorialButton(_game.frutiger, 48, sf::Color::Black, sf::Color(102, 102, 102), sf::Vector2f(600.f, 450.f), "Tutorial"),
_quitButton(_game.frutiger, 48, sf::Color::Black, sf::Color(102, 102, 102), sf::Vector2f(600.f, 525.f), "Quit")
{
	_bgTexture.loadFromFile("assets/main_menu_bg.png");
	_bg.setTexture(_bgTexture);
	_bg.setScale(sf::Vector2f(0.833333f, 0.833333f));
	_bg.setPosition(sf::Vector2f(0.f, 0.f));

	_title.setFont(_game.frutiger);
	_title.setFillColor(sf::Color::Black);
	_title.setCharacterSize(130);
	_title.setOutlineThickness(3);
	_title.setOutlineColor(sf::Color(177, 177, 177));
	_title.setString("8-Ball Pool");
	sf::Vector2f titleCenter(_title.getLocalBounds().width / 2.f, _title.getLocalBounds().height / 2.f);
	_title.setOrigin(titleCenter);
	_title.setPosition(sf::Vector2f(600.f, 200.f));
}

void MainMenuState::handleEvent(sf::Event& event)
{
	if (_playButton.isMouseOver(_game.window))
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			_game.changeState(std::make_unique<PlayState>(_game));
			return;
		}
	}

	if (_tutorialButton.isMouseOver(_game.window))
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			_game.changeState(std::make_unique<TutorialState>(_game));
			return;
		}
	}

	if (_quitButton.isMouseOver(_game.window))
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			_game.window.close();
			return;
		}
	}
}

void MainMenuState::update(float dt)
{
}

void MainMenuState::render(sf::RenderWindow& window)
{
	window.draw(_bg);
	window.draw(_title);
	_playButton.draw(window);
	_tutorialButton.draw(window);
	_quitButton.draw(window);
}
