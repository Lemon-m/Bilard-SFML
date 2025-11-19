#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <array>
#include "state.h"

class Game
{
	public:

		Game();
		
		void run();

		void pushState(std::unique_ptr<State> state);

		void popState();

		void createWindow();

		void setViewLetterbox();

		void toggleFullscreen();

		void setVolume(const int& vol);

		void setBallRotationSwitch(bool ballRotation);

		void changeState(std::unique_ptr<State> state);

		void loadBallTextures();

		int getVolume();

		bool isBallRotationOn();

		State* getCurrentState();

		std::array<sf::Texture, 16> ballTextures;

		sf::Font frutiger;

		sf::RenderWindow window;

		sf::View view;

		sf::Mouse mouse;

	private:

		std::stack<std::unique_ptr<State>> states;
		sf::Image icon;
		int volume;
		bool isFullscreen;
		bool ballRotationOn;
};