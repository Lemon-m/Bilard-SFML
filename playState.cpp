#include "playState.h"
#include <iostream>

PlayState::PlayState(Game& game) : State(game), 
p1(1),
p2(2),
scoredSolids(),
scoredStripes(),
turn(p1, scoredSolids, scoredStripes, true), 
cueBall(20, sf::Vector2f(840, 450), _game.ballTextures[15]),
table
(
	sf::Vector2f(100, 168), // table position
	"assets/table.png", // table asset
	sf::Vector2f(0.21973192704f, 0.21984435797f), // sprite scale - 1000x565
	new sf::Vector2f[12] // wall dimensions
	{
		sf::Vector2f(369, 17), // top left - light green [0]
		sf::Vector2f(374, 17), // top right - light green [1]
		sf::Vector2f(19, 364), // right - light green [2]
		sf::Vector2f(371, 18), // bottom right - light green [3]
		sf::Vector2f(369, 18), // bottom left - light green [4]
		sf::Vector2f(18, 362), // left - light green [5]
		sf::Vector2f(389, 47), // top left - brown [6]
		sf::Vector2f(397, 47), // top right - brown [7]
		sf::Vector2f(46, 401), // right - brown [8]
		sf::Vector2f(399, 46), // bottom right - brown [9]
		sf::Vector2f(389, 46), // bottom left - brown [10]
		sf::Vector2f(47, 401)  // left - brown [11]
	},
	new sf::Vector2f[12] // wall positions (same wall order as above)
	{
		sf::Vector2f(94, 47), // [0]
		sf::Vector2f(525, 47), // [1]
		sf::Vector2f(935, 100), // [2]
		sf::Vector2f(526, 501), // [3]
		sf::Vector2f(94, 501), // [4]
		sf::Vector2f(47, 102), // [5]
		sf::Vector2f(81, 0), // [6]
		sf::Vector2f(519, 0), // [7]
		sf::Vector2f(954, 82), // [8]
		sf::Vector2f(519, 519),  // [9]
		sf::Vector2f(81, 519), // [10]
		sf::Vector2f(0, 82) // [11]
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
)
{
	_bgTexture.loadFromFile("assets/pool_bg.png");
	_bg.setTexture(_bgTexture);
	_bg.setScale(sf::Vector2f(0.75f, 0.75f));
	_bg.setPosition(sf::Vector2f(0.f, 0.f));

	balls.emplace_back(20, sf::Vector2f(420, 450), _game.ballTextures[0]);
	balls.emplace_back(20, sf::Vector2f(350, 410), _game.ballTextures[1]);
	balls.emplace_back(20, sf::Vector2f(280, 490), _game.ballTextures[2]);
	balls.emplace_back(20, sf::Vector2f(315, 510), _game.ballTextures[3]);
	balls.emplace_back(20, sf::Vector2f(385, 470), _game.ballTextures[4]);
	balls.emplace_back(20, sf::Vector2f(280, 370), _game.ballTextures[5]);
	balls.emplace_back(20, sf::Vector2f(315, 430), _game.ballTextures[6]);
	balls.emplace_back(20, sf::Vector2f(350, 450), _game.ballTextures[7]);
	balls.emplace_back(20, sf::Vector2f(315, 390), _game.ballTextures[8]);
	balls.emplace_back(20, sf::Vector2f(350, 490), _game.ballTextures[9]);
	balls.emplace_back(20, sf::Vector2f(385, 430), _game.ballTextures[10]);
	balls.emplace_back(20, sf::Vector2f(280, 530), _game.ballTextures[11]);
	balls.emplace_back(20, sf::Vector2f(280, 450), _game.ballTextures[12]);
	balls.emplace_back(20, sf::Vector2f(315, 470), _game.ballTextures[13]);
	balls.emplace_back(20, sf::Vector2f(280, 410), _game.ballTextures[14]);

	text.setFont(_game.frutiger);
	text.setCharacterSize(72);
}

void PlayState::handleEvent(sf::Event& event)
{
	if (ballsStationary == true && win == 0)
	{
		if (turn.get8ballHoleSetMode() == true)
		{
			for (int i = 0; i < table.getHolesSize(); i++)
			{
				if (table.set8BallHoleMode(turn, p1, p2, i, _game.window, _game.mouse, event) == true)
				{
					break;
				}
			}
		}
		else if (cueBall.getBallInHand() == true)
		{
			cueBall.ballInHandMode(_game.window, _game.mouse, table, event);
			for (int i = 0; i < balls.size(); i++)
			{
				if (cueBall.checkBallCollision(balls[i]))
				{
					cueBall.setBallInHand(true);
				}
			}
		}
		else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Space) || cueBall.getAiming() == true)
		{
			cueBall.aim(_game.window, event, turn);
		}
	}
}

void PlayState::update(float dt)
{
	std::string currentTeamNumber = std::to_string(turn.getCurrentPlayerID());
	text.setString(currentTeamNumber);
	sf::Vector2f textCenter(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setOrigin(textCenter);
	text.setPosition(sf::Vector2f(600.f, 125.f));

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

	if (cueBall.getBallInHand() == false && turn.get8ballHoleSetMode() == false)
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
}

void PlayState::render(sf::RenderWindow& window)
{
	window.draw(_bg);
	table.drawTable(window);
	if (turn.get8ballHoleSetMode() == true)
	{
		for (int i = 0; i < table.getHolesSize(); i++)
		{
			if (turn.getHoveredOverHoleID() == i)
			{
				table.drawHoveredOverHole(window, i);
			}
		}
	}
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
}
