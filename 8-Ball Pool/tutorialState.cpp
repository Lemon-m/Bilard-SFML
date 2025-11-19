#include "tutorialState.h"
#include "mainMenuState.h"

TutorialState::TutorialState(Game& game) : State(game),
_leftButton(_game.frutiger, 96, sf::Color::White, sf::Color(102, 102, 102), sf::Vector2f(115.f, 450.f), "<"),
_rightButton(_game.frutiger, 96, sf::Color::White, sf::Color(102, 102, 102), sf::Vector2f(1080.f, 450.f), ">"),
_currentSlideText1(_game.frutiger, 48, sf::Color::White, sf::Vector2f(545.f, 72.5f), "1"),
_currentSlideText2(_game.frutiger, 48, sf::Color::White, sf::Vector2f(600.f, 72.5f), "/"),
_currentSlideText3(_game.frutiger, 48, sf::Color::White, sf::Vector2f(640.f, 72.5f), "24")
{
	_currentSlide = 0;

	_bgTexture.loadFromFile("assets/tutorial_bg.png");
	_bg.setTexture(_bgTexture);
	_bg.setScale(sf::Vector2f(0.75f, 0.75f));
	_bg.setPosition(sf::Vector2f(0.f, 0.f));

	_backTexture.loadFromFile("assets/backIcon.png");
	_backBtn.setTexture(_backTexture);
	_backBtn.setScale(0.375f, 0.375f);
	_backBtn.setPosition(15.f, 15.f);

	for (int i = 0; i < sizeof(_tutorialSlidesTextures) / sizeof(_tutorialSlidesTextures[0]); i++)
	{
		std::string fileString = "assets/tutorial/tutorial" + std::to_string(i + 1) + ".png";
		_tutorialSlidesTextures[i].loadFromFile(fileString);
	}

	for (int i = 0; i < sizeof(_tutorialSlides) / sizeof(_tutorialSlides[0]); i++)
	{
		//_tutorialSlides[i].setSize(sf::Vector2f(900.f, 675.f));
		_tutorialSlides[i].setTexture(_tutorialSlidesTextures[i]);
		_tutorialSlides[i].setOrigin(_tutorialSlides[i].getLocalBounds().width / 2.f, _tutorialSlides[i].getLocalBounds().height / 2.f);
		_tutorialSlides[i].setPosition(600.f, 450.f);
	}

	_soggyCatNose.setRadius(25);
	_soggyCatNose.setOrigin(_soggyCatNose.getRadius(), _soggyCatNose.getRadius());
	_soggyCatNose.setFillColor(sf::Color::Green);
	_soggyCatNose.setPosition(290.f, 510.f);

	_squeakBuffer.loadFromFile("assets/audio/Squeak.ogg");

	for (int i = 0; i < _squeakSounds.size(); i++)
	{
		_squeakSounds[i].setBuffer(_squeakBuffer);
	}
}



void TutorialState::handleEvent(sf::Event& event)
{
	float mouseX = _game.window.mapPixelToCoords(sf::Mouse::getPosition(_game.window)).x;
	float mouseY = _game.window.mapPixelToCoords(sf::Mouse::getPosition(_game.window)).y;

	sf::Vector2f disctanceVector;
	disctanceVector.x = _soggyCatNose.getPosition().x - mouseX;
	disctanceVector.y = _soggyCatNose.getPosition().y - mouseY;
	float distance = sqrt(disctanceVector.x * disctanceVector.x + disctanceVector.y * disctanceVector.y);

	if (distance <= _soggyCatNose.getRadius() && _currentSlide == sizeof(_tutorialSlides) / sizeof(_tutorialSlides[0]) - 1)
	{
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			playSound(_game.getVolume(), _squeakSounds);
		}
	}

	if (_leftButton.isMouseOver(_game.window))
	{
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			leftButtonPressed();
		}
	}

	if (_rightButton.isMouseOver(_game.window))
	{
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			rightButtonPressed();
		}
	}

	if (_backBtn.getGlobalBounds().contains(mouseX, mouseY))
	{
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			_game.changeState(std::make_unique<MainMenuState>(_game));
		}
	}
}

void TutorialState::update(float dt)
{
}

void TutorialState::render(sf::RenderWindow& window)
{
	window.draw(_bg);
	window.draw(_backBtn);
	window.draw(_tutorialSlides[_currentSlide]);
	//window.draw(_soggyCatNose);
	_leftButton.draw(window);
	_rightButton.draw(window);
	_currentSlideText1.draw(window);
	_currentSlideText2.draw(window);
	_currentSlideText3.draw(window);
}

void TutorialState::playSound(float volume, std::array<sf::Sound, 20>& pool)
{
	for (int i = 0; i < pool.size(); i++)
	{
		if (pool[i].getStatus() != sf::Sound::Playing)
		{
			pool[i].setVolume(volume);
			pool[i].play();
			return;
		}
	}

	pool[0].setVolume(volume);
	pool[0].play();
}

void TutorialState::leftButtonPressed()
{
	_currentSlide--;
	_currentSlide = std::clamp(_currentSlide, 0, static_cast<int>(sizeof(_tutorialSlides) / sizeof(_tutorialSlides[0])) - 1);
	_currentSlideText1.changeText(std::to_string(_currentSlide + 1));
}

void TutorialState::rightButtonPressed()
{
	_currentSlide++;
	_currentSlide = std::clamp(_currentSlide, 0, static_cast<int>(sizeof(_tutorialSlides) / sizeof(_tutorialSlides[0])) - 1);
	_currentSlideText1.changeText(std::to_string(_currentSlide + 1));
}
