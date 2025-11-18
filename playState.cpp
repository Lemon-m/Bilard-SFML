#include "playState.h"
#include "mainMenuState.h"
#include <iostream>

PlayState::PlayState(Game& game) : State(game), 
p1(1),
p2(2),
scoredSolids(),
scoredStripes(),
turnText(_game.frutiger, 72, sf::Color::White,  sf::Vector2f(600.f, 65.f), "Player 1's turn"),
preShotText(_game.frutiger, 28, sf::Color::White, sf::Vector2f(600.f, 125.f), ""),
player1Text(_game.frutiger, 42, sf::Color::White, sf::Vector2f(180.f, 760.f), "Player 1"),
player1Type(_game.frutiger, 28, sf::Color::White, sf::Vector2f(180.f, 800.f), ""),
player2Text(_game.frutiger, 42, sf::Color::White, sf::Vector2f(1005.f, 760.f), "Player 2"),
player2Type(_game.frutiger, 28, sf::Color::White, sf::Vector2f(1005.f, 800.f), ""),
p1Marker(_game.frutiger, 18, sf::Color::White, sf::Vector2f(20.f, 20.f), "P1"),
p2Marker(_game.frutiger, 18, sf::Color::White, sf::Vector2f(20.f, 20.f), "P2"),
backPopUpYes(_game.frutiger, 56, sf::Color(31, 224, 69), sf::Color(85, 219, 117), sf::Vector2f(470.f, 555.f), "Yes"),
backPopUpNo(_game.frutiger, 56, sf::Color(255, 42, 74), sf::Color(255, 71, 101), sf::Vector2f(730.f, 555.f), "No"),
backPopUp(_game.frutiger, "Are you sure you want to return\n           to the main menu?\n    (current game will be reset)", 38),
winPopUp(_game.frutiger, "placeholder", 42),
winPopUpReset(_game.frutiger, 56, sf::Color(28, 101, 255), sf::Color(98, 148, 255), sf::Vector2f(600.f, 555.f), "Reset"),
resetBtn(_game.frutiger, 42, sf::Color(80, 133, 255), sf::Color(117, 160, 255), sf::Vector2f(600.f, 860.f), "Reset"),
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
	Ball::resetBallCount();

	gameEnded = false;
	ballsStationary = true;
	backPopUpActive = false;
	winPopUpActive = false;
	p1MarkerActive = false;
	p2MarkerActive = false;

	bgTexture.loadFromFile("assets/pool_bg.png");
	bg.setTexture(bgTexture);
	bg.setScale(sf::Vector2f(0.75f, 0.75f));
	bg.setPosition(sf::Vector2f(0.f, 0.f));

	backTexture.loadFromFile("assets/backIcon.png");
	backBtn.setTexture(backTexture);
	backBtn.setScale(0.375f, 0.375f);
	backBtn.setPosition(15.f, 15.f);

	p1FirstUIBallPos = sf::Vector2f(120.f, 835.f);
	p2FirstUIBallPos = sf::Vector2f(1045.f, 835.f);

	p1MarkerArrow.setPointCount(3);
	p1MarkerArrow.setRadius(10);
	p1MarkerArrow.setOrigin(p1MarkerArrow.getRadius(), p1MarkerArrow.getRadius());
	p1MarkerArrow.setFillColor(sf::Color::White);

	p2MarkerArrow.setPointCount(3);
	p2MarkerArrow.setRadius(10);
	p2MarkerArrow.setOrigin(p2MarkerArrow.getRadius(), p2MarkerArrow.getRadius());
	p2MarkerArrow.setFillColor(sf::Color::White);


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

	// for testing vvv
	//p1.ballType = 1;
	//p2.ballType = 2;
	//turn = Turn(p1, scoredSolids, scoredStripes);
	//turn.set8BallHoleSetMode(true);
}

void PlayState::handleEvent(sf::Event& event)
{
	if (backPopUpActive == false && winPopUpActive == false)
	{
		float mouseX = _game.window.mapPixelToCoords(sf::Mouse::getPosition(_game.window)).x;
		float mouseY = _game.window.mapPixelToCoords(sf::Mouse::getPosition(_game.window)).y;

		if (backBtn.getGlobalBounds().contains(mouseX, mouseY))
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				backPopUpActive = true;
			}
		}
	}

	if (backPopUpActive == false && winPopUpActive == false)
	{
		if (resetBtn.isMouseOver(_game.window) == true && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && gameEnded == true)
		{
			_game.changeState(std::make_unique<PlayState>(_game));
			return;
		}

		if (ballsStationary == true && win == 0)
		{
			if (turn.get8ballHoleSetMode() == true)
			{
				for (int i = 0; i < table.getHolesSize(); i++)
				{
					if (table.set8BallHoleMode(turn, p1, p2, i, p1Marker, p2Marker, p1MarkerArrow, p2MarkerArrow, p1MarkerActive, p2MarkerActive, _game.window, _game.mouse, event) == true)
					{
						break;
					}
				}
			}
			else if (cueBall.getBallInHand() == true)
			{
				cueBall.ballInHandMode(_game.window, _game.mouse, table, event, turn.getOpenTableMode());
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
	else if (backPopUpActive == true)
	{
		if (backPopUp.closeBtn.isMouseOver(_game.window) == true || backPopUpNo.isMouseOver(_game.window) == true)
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				backPopUp.closeBtn.text.setFillColor(backPopUp.closeBtn.normalColor);
				backPopUpNo.text.setFillColor(backPopUp.closeBtn.normalColor);
				backPopUpActive = false;
			}
		}
		else if (backPopUpYes.isMouseOver(_game.window) == true && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			_game.changeState(std::make_unique<MainMenuState>(_game));
			return;
		}
	}
	else if (winPopUpActive == true)
	{
		if (winPopUp.closeBtn.isMouseOver(_game.window) == true)
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				winPopUp.closeBtn.text.setFillColor(winPopUp.closeBtn.normalColor);
				winPopUpActive = false;
			}
		}
		else if (winPopUpReset.isMouseOver(_game.window) == true && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			_game.changeState(std::make_unique<PlayState>(_game));
			return;
		}
	}
}

void PlayState::update(float dt)
{
	if (win == 0)
	{
		turnText.changeText("Player " + std::to_string(turn.getCurrentPlayerID()) + "'s turn");
	}
	else
	{
		turnText.changeText("Player " + std::to_string(win) + " won!");
	}

	if (turn.get8ballHoleSetMode() == true)
	{
		preShotText.changeText("(select your final pocket for the 8-ball)");
	}
	else if (cueBall.getBallInHand() == true)
	{
		preShotText.changeText("(ball in hand)");
	}
	else
	{
		preShotText.changeText("");
	}

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
				//std::cout << "kolizja z ³uz¹\n";
				balls[i].handleHoleCollision(table, j, turn, p1, p2, scoredSolids, scoredStripes, scoredSolidsUI, scoredStripesUI, p1FirstUIBallPos, p2FirstUIBallPos, win);
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
				//std::cout << "kolizja z ³uz¹\n";
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
		//std::cout << "Koniec gry! Wygra³ gracz nr. " << win << "\n";
		backPopUpActive = false;
		winPopUp.message.changeText("       Player " + std::to_string(win) + " Wins!\nDo you want to reset?");
		winPopUpActive = true;
		gameEnded = true;
	}
	else if (ballsStationary == true && turn.getCueBallShot() == true && gameEnded == false)
	{
		if (turn.getOpenTableMode() == true)
		{
			turn.setSwitchRequest(true);
		}

		if (((turn.getScoredSolidsCounter() != 0 && turn.getScoredStripesCounter() == 0) || (turn.getScoredStripesCounter() != 0 && turn.getScoredSolidsCounter() == 0)) && turn.getOpenTableMode() == true)
		{
			turn.setTeams(p1, p2, scoredSolids, scoredStripes, cueBall);

			if (p1.ballType == 1 && p2.ballType == 2)
			{
				player1Type.changeText("(Solids)");

				if (!scoredSolids.empty())
				{
					scoredSolidsUI.push_back(sf::Sprite());
					scoredSolidsUI[0].setTexture(_game.ballTextures[scoredSolids[0] - 1]);
					scoredSolidsUI[0].setScale(0.25f, 0.25f);
					scoredSolidsUI[0].setOrigin(sf::Vector2f(17.5f, 17.5f));
					scoredSolidsUI[0].setPosition(p1FirstUIBallPos);

					for (int i = 1; i < scoredSolids.size(); i++)
					{
						scoredSolidsUI.push_back(sf::Sprite());
						scoredSolidsUI[i].setTexture(_game.ballTextures[scoredSolids[i] - 1]);
						scoredSolidsUI[i].setScale(0.25f, 0.25f);
						scoredSolidsUI[i].setOrigin(sf::Vector2f(17.5f, 17.5f));
						scoredSolidsUI[i].setPosition(p1FirstUIBallPos.x + (i * 17.5f), p1FirstUIBallPos.y);
					}
				}

				player2Type.changeText("(Stripes)");

				if (!scoredStripes.empty())
				{
					scoredStripesUI.push_back(sf::Sprite());
					scoredStripesUI[0].setTexture(_game.ballTextures[scoredStripes[0] - 1]);
					scoredStripesUI[0].setScale(0.25f, 0.25f);
					scoredStripesUI[0].setOrigin(sf::Vector2f(17.5f, 17.5f));
					scoredStripesUI[0].setPosition(p2FirstUIBallPos);

					for (int i = 1; i < scoredStripes.size(); i++)
					{
						scoredStripesUI.push_back(sf::Sprite());
						scoredStripesUI[i].setTexture(_game.ballTextures[scoredStripes[i] - 1]);
						scoredStripesUI[i].setScale(0.25f, 0.25f);
						scoredStripesUI[i].setOrigin(sf::Vector2f(17.5f, 17.5f));
						scoredStripesUI[i].setPosition(p2FirstUIBallPos.x - (i * 17.5f), p2FirstUIBallPos.y);
					}
				}
			}
			else if (p1.ballType == 2 && p2.ballType == 1)
			{
				player1Type.changeText("(Stripes)");

				if (!scoredStripes.empty())
				{
					scoredStripesUI.push_back(sf::Sprite());
					scoredStripesUI[0].setTexture(_game.ballTextures[scoredStripes[0] - 1]);
					scoredStripesUI[0].setScale(0.25f, 0.25f);
					scoredStripesUI[0].setOrigin(sf::Vector2f(17.5f, 17.5f));
					scoredStripesUI[0].setPosition(p1FirstUIBallPos);

					for (int i = 1; i < scoredStripes.size(); i++)
					{
						scoredStripesUI.push_back(sf::Sprite());
						scoredStripesUI[i].setTexture(_game.ballTextures[scoredStripes[i] - 1]);
						scoredStripesUI[i].setScale(0.25f, 0.25f);
						scoredStripesUI[i].setOrigin(sf::Vector2f(17.5f, 17.5f));
						scoredStripesUI[i].setPosition(p1FirstUIBallPos.x + (i * 17.5f), p1FirstUIBallPos.y);
					}
				}

				player2Type.changeText("(Solids)");

				if (!scoredSolids.empty())
				{
					scoredSolidsUI.push_back(sf::Sprite());
					scoredSolidsUI[0].setTexture(_game.ballTextures[scoredSolids[0] - 1]);
					scoredSolidsUI[0].setScale(0.25f, 0.25f);
					scoredSolidsUI[0].setOrigin(sf::Vector2f(17.5f, 17.5f));
					scoredSolidsUI[0].setPosition(p2FirstUIBallPos);

					for (int i = 1; i < scoredSolids.size(); i++)
					{
						scoredSolidsUI.push_back(sf::Sprite());
						scoredSolidsUI[i].setTexture(_game.ballTextures[scoredSolids[i] - 1]);
						scoredSolidsUI[i].setScale(0.25f, 0.25f);
						scoredSolidsUI[i].setOrigin(sf::Vector2f(17.5f, 17.5f));
						scoredSolidsUI[i].setPosition(p2FirstUIBallPos.x - (i * 17.5f), p2FirstUIBallPos.y);
					}
				}

			}
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
		//turn.set8BallHoleSetMode(true);
	}
}

void PlayState::render(sf::RenderWindow& window)
{
	window.draw(bg);
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
	//table.drawHitboxes(window);
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
	turnText.draw(window);
	preShotText.draw(window);
	player1Text.draw(window);
	player1Type.draw(window);
	player2Text.draw(window);
	player2Type.draw(window);
	if (p1.ballType != 0 && p2.ballType != 0)
	{
		for (int i = 0; i < scoredSolidsUI.size(); i++)
		{
			window.draw(scoredSolidsUI[i]);
		}
		for (int i = 0; i < scoredStripesUI.size(); i++)
		{
			window.draw(scoredStripesUI[i]);
		}
	}
	if (p1MarkerActive == true)
	{
		p1Marker.draw(window);
		window.draw(p1MarkerArrow);
	}
	if (p2MarkerActive == true)
	{
		p2Marker.draw(window);
		window.draw(p2MarkerArrow);
	}
	if (win != 0)
	{
		resetBtn.draw(window);
	}
	cueBall.drawBall(window);
	window.draw(backBtn);
	if (backPopUpActive == true)
	{
		backPopUp.draw(window);
		backPopUpYes.draw(window);
		backPopUpNo.draw(window);
	}
	else if(winPopUpActive)
	{
		winPopUp.draw(window);
		winPopUpReset.draw(window);
	}
}
