#include "game.h"

Game::Game() : window(sf::VideoMode(1200, 900), "Bilard") {}

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

void Game::changeState(std::unique_ptr<State> state)
{
	if (!states.empty())
	{
		states.pop();
	}
	states.push(std::move(state));
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