#include "mainMenuState.h"
#include "game.h"
#include "playState.h"
#include "tutorialState.h"
#include "ball.h"
#include <memory>
#include <stack>
#include <iostream>

MainMenuState::MainMenuState(Game& game) : State(game),
_playButton(_game.frutiger, 48, sf::Color::Black, sf::Color(102, 102, 102), sf::Vector2f(600.f, 375.f), "Play"),
_tutorialButton(_game.frutiger, 48, sf::Color::Black, sf::Color(102, 102, 102), sf::Vector2f(600.f, 450.f), "Tutorial"),
_quitButton(_game.frutiger, 48, sf::Color::Black, sf::Color(102, 102, 102), sf::Vector2f(600.f, 525.f), "Quit"),
_popUpYes(_game.frutiger, 56, sf::Color(31, 224, 69), sf::Color(85, 219, 117), sf::Vector2f(470.f, 555.f), "Yes"),
_popUpNo(_game.frutiger, 56, sf::Color(255, 42, 74), sf::Color(255, 71, 101), sf::Vector2f(730.f, 555.f), "No"),
_popUp(_game.frutiger, "    Are you sure\nyou want to quit?"),
_volumeLabel(_game.frutiger, 18, sf::Color::Black, sf::Vector2f(50.f, 873.75f), "Volume:"),
_volumeValue(_game.frutiger, 18, sf::Color::Black, sf::Vector2f(260.f, 873.75f), std::to_string(_game.getVolume())),
_rotationSwitchLabel(_game.frutiger, 18, sf::Color::Black, sf::Vector2f(67.5f, 845.f), "Ball rotation:"),
_creditLabel(_game.frutiger, 18, sf::Color::Black, sf::Vector2f(1045.f, 868.75f), " Game made by Lemon-m on GitHub\nMain Menu BG by u/Rottingbodiess")
{
	_popUpActive = false;

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

	_volumeBarHitbox.setSize(sf::Vector2f(190.f, 50.f));
	_volumeBarHitbox.setPosition(70.f, 865.f);

	_volumeBarGrey.setSize(sf::Vector2f(148.f, 10.f));
	_volumeBarGrey.setOrigin(0.f, 5.f);
	_volumeBarGrey.setPosition(90.f, 880.f);
	_volumeBarGrey.setFillColor(sf::Color(85, 85, 85));

	_volumeBarGreen.setSize(sf::Vector2f(game.getVolume() * 1.5f, 10.f));
	_volumeBarGreen.setOrigin(0.f, 5.f);
	_volumeBarGreen.setPosition(90.f, 880.f);
	_volumeBarGreen.setFillColor(sf::Color::Green);

	_switchOnTexture.loadFromFile("assets/SwitchOn.png");
	_switchOffTexture.loadFromFile("assets/SwitchOff.png");

	_switch.setTexture(_switchOnTexture);
	_switch.setOrigin(_switch.getLocalBounds().width / 2, _switch.getLocalBounds().height / 2);
	_switch.setPosition(165.f, 850.f);
}

void MainMenuState::handleEvent(sf::Event& event)
{
	float mouseX = _game.window.mapPixelToCoords(sf::Mouse::getPosition(_game.window)).x;
	float mouseY = _game.window.mapPixelToCoords(sf::Mouse::getPosition(_game.window)).y;

	if (_popUpActive == false)
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
				_quitButton.text.setFillColor(_quitButton.normalColor);
				_popUpActive = true;
			}
		}

		if (_volumeBarHitbox.getGlobalBounds().contains(mouseX, mouseY) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			int newVol = std::clamp(mouseX - 90.f, 0.f, 150.f);
			_volumeBarGreen.setSize(sf::Vector2f(newVol, 10.f));
			_game.setVolume(newVol / 1.5);
			_volumeValue.changeText(std::to_string(_game.getVolume()));
		}

		if (_switch.getGlobalBounds().contains(mouseX, mouseY) && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			_game.setBallRotationSwitch(!_game.isBallRotationOn());
			if (_game.isBallRotationOn() == true)
			{
				_switch.setTexture(_switchOnTexture);
			}
			else
			{
				_switch.setTexture(_switchOffTexture);
			}
		}
	}
	else
	{
		if (_popUp.closeBtn.isMouseOver(_game.window) == true || _popUpNo.isMouseOver(_game.window) == true)
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				_popUp.closeBtn.text.setFillColor(_popUp.closeBtn.normalColor);
				_popUpNo.text.setFillColor(_popUp.closeBtn.normalColor);
				_popUpActive = false;
			}
		}
		else if (_popUpYes.isMouseOver(_game.window) == true)
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				_game.window.close();
				return;
			}
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
	_volumeLabel.draw(window);
	_volumeValue.draw(window);
	_rotationSwitchLabel.draw(window);
	_creditLabel.draw(window);
	window.draw(_volumeBarGrey);
	window.draw(_volumeBarGreen);
	window.draw(_switch);
	if (_popUpActive == true)
	{
		_popUp.draw(window);
		_popUpYes.draw(window);
		_popUpNo.draw(window);
	}
}
