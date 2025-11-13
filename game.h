#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "state.h"

class Game
{
	public:

		Game();
		
		void run();

		void pushState(std::unique_ptr<State> state);

		void popState();

		void changeState(std::unique_ptr<State> state);

		State* getCurrentState();

	private:

		sf::RenderWindow window;

		std::stack<std::unique_ptr<State>> states;
};