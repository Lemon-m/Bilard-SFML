#include "game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(1920, 1080), "8-Ball Pool", sf::Style::Fullscreen), view(sf::FloatRect(0, 0, 1200.f, 900.f))
{
	if (icon.loadFromFile("assets/ball_8.png"))
	{
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	isFullscreen = true;
	ballRotationOn = true;

	volume = 100;

	setViewLetterbox();

	window.setView(view);

	frutiger.loadFromFile("assets/frutiger.ttf");
	loadBallTextures();
}

void Game::run()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		float dt = std::clamp(clock.restart().asSeconds(), 0.f, 0.0167f); // 16.7ms -> 60hz
		sf::Event event;

		if (!states.empty())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
				{
					toggleFullscreen();
				}

				states.top()->handleEvent(event);
			}

			states.top()->update(dt);

			window.clear();
			states.top()->render(window);
			window.display();
		}
	}
}

void Game::pushState(std::unique_ptr<State> state)
{
	states.push(std::move(state));
}

void Game::popState()
{
	if (!states.empty())
	{
		states.pop();
	}
}

void Game::createWindow()
{
	window.close();

	if (isFullscreen)
	{
		window.create(sf::VideoMode::getDesktopMode(), "8-Ball Pool", sf::Style::Fullscreen);
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	else
	{
		window.create(sf::VideoMode(1200, 900), "8-Ball Pool", sf::Style::Titlebar | sf::Style::Close);
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	view = sf::View(sf::FloatRect(0, 0, 1200.f, 900.f));
	setViewLetterbox();
	window.setView(view);
}

void Game::setViewLetterbox()
{
	float windowRatio = float(window.getSize().x) / window.getSize().y;
	float viewRatio = 1200.f / 900.f;
	float sizeX = 1.f;
	float sizeY = 1.f;

	if (windowRatio > viewRatio)
	{
		sizeX = viewRatio / windowRatio;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
	}

	view.setViewport(sf::FloatRect((1.f - sizeX) / 2.f, (1.f - sizeY) / 2.f, sizeX, sizeY));
}

void Game::toggleFullscreen()
{
	isFullscreen = !isFullscreen;
	createWindow();
}

void Game::setVolume(const int& vol)
{
	volume = vol;
}

void Game::setBallRotationSwitch(bool ballRotation)
{
	ballRotationOn = ballRotation;
}

void Game::changeState(std::unique_ptr<State> state)
{
	if (!states.empty())
	{
		states.pop();
	}
	states.push(std::move(state));
}

void Game::loadBallTextures()
{
	for (int i = 0; i < 16; i++)
	{
		std::string fileString = "assets/ball_" + std::to_string(i + 1) + ".png";
		ballTextures[i].loadFromFile(fileString);
	}
}

int Game::getVolume()
{
	return volume;
}

bool Game::isBallRotationOn()
{
	return ballRotationOn;
}

State* Game::getCurrentState()
{
	if (states.empty() == true)
	{
		return nullptr;
	}
	else
	{
		return states.top().get();
	}
}