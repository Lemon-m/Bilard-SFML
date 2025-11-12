#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ball.h"
#include "cueBall.h"
#include "table.h"
#include "player.h"
#include "turn.h"

unsigned int Ball::_ballCount = 0;
static const float pi = 3.141592654f;

int main()
{

	sf::RenderWindow window(sf::VideoMode(1200, 900), "Bilard");
	//window.setFramerateLimit(60);

	sf::Font arial;

	if (!arial.loadFromFile("assets/arial.ttf"))
	{
		std::cerr << "Couldn't load font\n";
		return -1;
	}

	sf::Clock clock;
	float dt;

	sf::Event event;

	sf::Mouse mouse;

	Player p1, p2;

	p1.ID = 1;
	p2.ID = 2;

	std::vector<int> scoredSolids;
	std::vector<int> scoredStripes;

	int win = 0; // 0 - no win | 1 - p1 win | p2 - win
	bool gameEnded = false;

	Turn turn(p1, scoredSolids, scoredStripes, true); //open table

	std::array<sf::Texture, 16> ballTextures;

	for (int i = 0; i < 16; i++)
	{
		std::string fileString = "assets/ball_" + std::to_string(i + 1) + ".png";

		if (!ballTextures[i].loadFromFile(fileString))
		{
			std::cerr << "Error loading textures\n";
		}
	}

	std::vector<Ball> balls;
	balls.emplace_back(20, sf::Vector2f(420, 450), ballTextures[0]);
	balls.emplace_back(20, sf::Vector2f(350, 410), ballTextures[1]);
	balls.emplace_back(20, sf::Vector2f(280, 490), ballTextures[2]);
	balls.emplace_back(20, sf::Vector2f(315, 510), ballTextures[3]);
	balls.emplace_back(20, sf::Vector2f(385, 470), ballTextures[4]);
	balls.emplace_back(20, sf::Vector2f(280, 370), ballTextures[5]);
	balls.emplace_back(20, sf::Vector2f(315, 430), ballTextures[6]);
	balls.emplace_back(20, sf::Vector2f(350, 450), ballTextures[7]);
	balls.emplace_back(20, sf::Vector2f(315, 390), ballTextures[8]);
	balls.emplace_back(20, sf::Vector2f(350, 490), ballTextures[9]);
	balls.emplace_back(20, sf::Vector2f(385, 430), ballTextures[10]);
	balls.emplace_back(20, sf::Vector2f(280, 530), ballTextures[11]);
	balls.emplace_back(20, sf::Vector2f(280, 450), ballTextures[12]);
	balls.emplace_back(20, sf::Vector2f(315, 470), ballTextures[13]);
	balls.emplace_back(20, sf::Vector2f(280, 410), ballTextures[14]);

	bool ballsStationary = true;

	CueBall cueBall(20, sf::Vector2f(840, 450), ballTextures[15]);
	Table table
	(
		sf::Vector2f(100, 168), // table position
		"assets/table.png", // table asset
		sf::Vector2f(0.21973192704f, 0.21984435797f), // sprite scale - 1000x565
		new sf::Vector2f[12] // wall dimensions
		{
			sf::Vector2f(371, 17), // top left - light green [0]
			sf::Vector2f(376, 17), // top right - light green [1]
			sf::Vector2f(19, 369), // right - light green [2]
			sf::Vector2f(375, 18), // bottom right - light green [3]
			sf::Vector2f(371, 18), // bottom left - light green [4]
			sf::Vector2f(18, 369), // left - light green [5]
			sf::Vector2f(391, 47), // top left - brown [6]
			sf::Vector2f(401, 47), // top right - brown [7]
			sf::Vector2f(46, 406), // right - brown [8]
			sf::Vector2f(401, 46), // bottom right - brown [9]
			sf::Vector2f(391, 46), // bottom left - brown [10]
			sf::Vector2f(47, 406)  // left - brown [11]
		},
		new sf::Vector2f[12] // wall positions (same wall order as above)
		{
			sf::Vector2f(92, 47), // [0]
			sf::Vector2f(525, 47), // [1]
			sf::Vector2f(935, 98), // [2]
			sf::Vector2f(526, 501), // [3]
			sf::Vector2f(92, 501), // [4]
			sf::Vector2f(47, 100), // [5]
			sf::Vector2f(79, 0), // [6]
			sf::Vector2f(519, 0), // [7]
			sf::Vector2f(954, 80), // [8]
			sf::Vector2f(519, 519),  // [9]
			sf::Vector2f(79, 519), // [10]
			sf::Vector2f(0, 80) // [11]
		}, 
		new sf::Vector2f[6] // hole positions
		{
			sf::Vector2f(47, 53), // top left
			sf::Vector2f(494, 41), // middle top
			sf::Vector2f(945, 53), // top right
			sf::Vector2f(946, 513), // bottom right
			sf::Vector2f(494,524), // middle bottom
			sf::Vector2f(47,513) // bottom left
		}
	);

	sf::Text text;
	text.setFont(arial);
	text.setCharacterSize(72);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}



			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Space || cueBall.getAiming() == true) && cueBall.getBallInHand() == false && ballsStationary == true && win == 0)
			{
				cueBall.aim(window, event, turn);
			}

			if (cueBall.getBallInHand() == true && ballsStationary == true)
			{
				cueBall.ballInHandMode(window, mouse, table, event);
				for (int i = 0; i < balls.size(); i++)
				{
					if (cueBall.checkBallCollision(balls[i]))
					{
						cueBall.setBallInHand(true);
					}
				}
			}
		}

		std::string currentTeamNumber = std::to_string(turn.getCurrentPlayerID());
		text.setString(currentTeamNumber);
		sf::Vector2f textCenter(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
		text.setOrigin(textCenter);
		text.setPosition(sf::Vector2f(600.f, 125.f));

		dt = std::clamp(clock.restart().asSeconds(), 0.f, 0.0167f); // 16.7ms -> 60hz

		for (int i = 0; i < balls.size(); i++)
		{
			balls[i].setBallPosition(balls[i].getBallPosition() + balls[i].getVelocity() * dt);
			balls[i].calculateVelocity(dt);

			for (int j = i + 1; j < balls.size(); j++)
			{
				if (balls[i].checkBallCollision(balls[j]))
				{
					balls[i].handleBallCollision(balls[j]);
				}
			}

			for (int j = 0; j < table.getHolesSize(); j++)
			{
				if (balls[i].checkHoleCollision(table, j))
				{
					std::cout << "kolizja z ³uz¹\n";
					balls[i].handleHoleCollision(table, j, turn, p1, p2, scoredSolids, scoredStripes, win);
				}
			}

			for (int j = 0; j < table.getWallsSize(); j++)
			{
				if (balls[i].checkTableCollision(table, j))
				{
					balls[i].handleTableCollision(table, j);
					if (turn.getCueBallCollisions() > 0)
					{
						turn.wallHit();
					}
				}
			}
		}

		if (cueBall.getBallInHand() == false)
		{
			cueBall.setBallPosition(cueBall.getBallPosition() + cueBall.getVelocity() * dt);
			cueBall.calculateVelocity(dt);

			for (int i = 0; i < balls.size(); i++)
			{
				if (cueBall.checkBallCollision(balls[i]))
				{
					//std::cout << "kolizja z bil¹\n";
					cueBall.handleBallCollision(balls[i]);
					if (turn.getCueBallCollisions() == 0)
					{
						turn.firstBallIDSetAndCheck(balls[i], cueBall, win);
					}
					turn.cueBallCollision();
				}
			}

			for (int i = 0; i < table.getHolesSize(); i++)
			{
				if (cueBall.checkHoleCollision(table, i))
				{
					std::cout << "kolizja z ³uz¹\n";
					if (turn.get8BallScored() == false)
					{
						cueBall.handleHoleCollision(table, i, turn);
					}
					else
					{
						if (turn.getCurrentPlayerID() == 1)
						{
							win = 2;
						}
						else if (turn.getCurrentPlayerID() == 2)
						{
							win = 1;
						}
						cueBall.setVelocity(sf::Vector2f(0.f, 0.f));
						cueBall.setBallPosition(sf::Vector2f(1220, 920));
					}
				}
			}

			for (int i = 0; i < table.getWallsSize(); i++)
			{
				if (cueBall.checkTableCollision(table, i))
				{
					//std::cout << "kolizja\n";
					cueBall.handleTableCollision(table, i);
					if (turn.getCueBallCollisions() > 0)
					{
						turn.wallHit();
					}
				}
			}
		}

		if (cueBall.getVelocity().x == 0 && cueBall.getVelocity().y == 0)
		{
			for (int i = 0; i < balls.size(); i++)
			{
				if (balls[i].getVelocity().x == 0.f && balls[i].getVelocity().y == 0.f)
				{
					ballsStationary = true;
				}
				else
				{
					ballsStationary = false;
					break;
				}
			}
		}
		else
		{
			ballsStationary = false;
		}

		if (ballsStationary == true && turn.get8BallScored() == true && win == 0)
		{
			if (turn.getCurrentPlayerID() == 1)
			{
				win = 1;
			}
			else if (turn.getCurrentPlayerID() == 2)
			{
				win = 2;
			}
		}

		if (win != 0 && gameEnded == false)
		{
			std::cout << "Koniec gry! Wygra³ gracz nr. " << win << "\n";
			gameEnded = true;
		}
		else if (ballsStationary == true && turn.getCueBallShot() == true && gameEnded == false)
		{
			if (turn.getOpenTableMode() == true)
			{
				turn.setSwitchRequest(true);
			}

			if ((scoredSolids.size() != scoredStripes.size()) && turn.getOpenTableMode() == true)
			{
				turn.setTeams(p1, p2, scoredSolids, scoredStripes, cueBall);
			}

			if (turn.getCueBallShot() == true)
			{
				if (turn.getCueBallCollisions() == 0 || (turn.getWallCollisionCounter() == 0 && turn.getScoredBallsCounter() == 0))
				{
					turn.setSwitchRequest(true);
					cueBall.setBallInHandRequest(true);
				}
				else if (turn.getScoredBallsCounter() == 0)
				{
					turn.setSwitchRequest(true);
				}
			}

			if (turn.getSwitchReq() == true)
			{
				if (turn.getCurrentPlayerID() == 1)
				{
					if (turn.getOpenTableMode() == false)
					{
						turn = Turn(p2, scoredSolids, scoredStripes);
					}
					else
					{
						turn = Turn(p2, scoredSolids, scoredStripes, true);
					}
				}
				else if (turn.getCurrentPlayerID() == 2)
				{
					if (turn.getOpenTableMode() == false)
					{
						turn = Turn(p1, scoredSolids, scoredStripes);
					}
					else
					{
						turn = Turn(p1, scoredSolids, scoredStripes, true);
					}
				}

				if (cueBall.getBallInHandRequest() == true)
				{
					cueBall.setBallInHand(true);
					cueBall.setBallInHandRequest(false);
				}
			}
			else
			{
				if (turn.getCurrentPlayerID() == 1)
				{
					if (turn.getOpenTableMode() == false)
					{
						turn = Turn(p1, scoredSolids, scoredStripes);
					}
					else
					{
						turn = Turn(p1, scoredSolids, scoredStripes, true);
					}
				}
				else if (turn.getCurrentPlayerID() == 2)
				{
					if (turn.getOpenTableMode() == false)
					{
						turn = Turn(p2, scoredSolids, scoredStripes);
					}
					else
					{
						turn = Turn(p2, scoredSolids, scoredStripes, true);
					}
				}
			}
		}

		window.clear();
		table.drawTable(window);
		table.drawHitboxes(window);
		for (int i = 0; i < balls.size();)
		{
			if (balls[i].getDeletionReq() == true)
			{
				balls.erase(balls.begin() + i);
			}
			else
			{
				balls[i].drawBall(window);
				i++;
			}
		}
		cueBall.drawBall(window);
		window.draw(text);
		window.display();
	}

	return 0;
}
 