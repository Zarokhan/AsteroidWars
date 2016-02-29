#include <Windows.h>
#include "SFML\Graphics.hpp"
#include "Window.h"
#include "GameSession.h"

// Window
sf::RenderWindow* window;
GameSession* game;

// Main method
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	game = new GameSession();

	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);	// Updates per second
	
	float delta = 0;

	// Game loop
	while (window->isOpen())
	{
		// Process Events
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
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
			game->Update(delta);
		}

		window->clear();
		game->Draw();
		window->display();

		deltaTime += clock.restart();
	}

	delete game;
	delete window;

	return EXIT_SUCCESS;
}