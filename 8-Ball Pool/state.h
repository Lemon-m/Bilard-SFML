#pragma once
#include <SFML/Graphics.hpp>

class Game;

class State
{
	public:

		State(Game& game) : _game(game) {}

		virtual ~State() = default;

		virtual void handleEvent(sf::Event& event) = 0;

		virtual void update(float dt) = 0;

		virtual void render(sf::RenderWindow& window) = 0;

	protected:

		Game& _game;
};