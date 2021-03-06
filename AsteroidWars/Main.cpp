#include <Windows.h>
#include "SFML\Graphics.hpp"
#include "Ship.h"
#include "Window.h"
#include "GameSession.h"
#include "GA/GASession.h"

#define GAME 1	// 0 = GA test bed, 1 = Game (FSM or FuSM)

// Window
sf::RenderWindow* Window;
sf::RenderWindow* DebugWindow;
GameSession* Game;
GASession* GA;

// Main method
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	
#if GAME
	Game = new GameSession();
	GA = NULL;
#else
	GA = new GASession();
	DebugWindow = new sf::RenderWindow(sf::VideoMode(DEBUG_WIDTH, DEBUG_HEIGHT), DEBUG_TITLE);
	Game = NULL;
#endif

	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);	// Updates per second
	
	float delta = 0;

	// Game loop
	while (Window->isOpen())
	{
		// Process Events
		sf::Event event;
		while (Window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				Window->close();
				break;
			case sf::Event::Resized:
				//window->setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
				break;
			}
		}

		// Update logic if 1/60 seconds has passed
		while (deltaTime > ups)
		{
			deltaTime -= ups;
			delta = deltaTime.asSeconds();

#if GAME
			Game->Update(delta);
#else
			GA->Update(delta);
#endif

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				Window->close();

		}

		Window->clear();
#if GAME
		Game->Draw();
#else
		GA->Draw();
#endif
		Window->display();

#if GAME == 0
		sf::Vector2i pos(Window->getPosition().x - DEBUG_WIDTH, Window->getPosition().y);
		DebugWindow->setPosition(pos);
		DebugWindow->clear();
		GA->DrawInformation();
		DebugWindow->display();
#endif

		deltaTime += clock.restart();
	}

	delete Game;
	delete Window;
	delete DebugWindow;

	return EXIT_SUCCESS;
}