#pragma once
#include "state.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "game.h"
#include "ball.h"
#include "cueBall.h"
#include "table.h"
#include "turn.h"
#include "player.h"
#include "textLabel.h"
#include "popUp.h"

class PlayState : public State
{
	public:
		PlayState(Game& game);

		void handleEvent(sf::Event& event) override;

		void update(float dt) override;

		void render(sf::RenderWindow& window) override;

		void playSound(float volume, std::array<sf::Sound, 20>& pool, int force);

		void playSound(float volume, std::array<sf::Sound, 20>& pool);

	protected:

		Player p1, p2;
		std::vector<int> scoredSolids, scoredStripes;
		std::vector<sf::Sprite> scoredSolidsUI, scoredStripesUI;
		std::vector<Ball> balls;
		Turn turn;
		CueBall cueBall;
		Table table;
		sf::Texture bgTexture, backTexture;
		sf::Sprite bg, backBtn;
		sf::SoundBuffer wallHitBuffer, ballCollisionBuffer, lightBallCollisionBuffer, cueBallHitBuffer, sinkBuffer;
		std::array<sf::Sound, 20> wallHitSounds, ballCollisionSounds, lightBallCollisionSounds, cueBallHitSounds, sinkSounds;
		PopUp backPopUp, winPopUp;
		TextLabel backPopUpYes, backPopUpNo, winPopUpReset, resetBtn, turnText, preShotText, player1Text, player1Type, player2Text, player2Type, p1Marker, p2Marker;
		sf::CircleShape p1MarkerArrow, p2MarkerArrow;
		sf::Vector2f p1FirstUIBallPos, p2FirstUIBallPos;
		bool backPopUpActive, winPopUpActive,ballsStationary, gameEnded, p1MarkerActive, p2MarkerActive;
		int win = 0; // 0 - no win | 1 - p1 win | p2 - win
};
