#include "SFML\Graphics.hpp"
#include "GameSession.h"
#define WINDOW_TITLE "Asteroid Wars"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

// Window
sf::RenderWindow* window;
GameSession* game;

// Main method
int main()
{
	bool isClosing = false;
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);	// Updates per second
	float delta = 0;

	game = new GameSession();

	// Game loop
	while (window->isOpen() && !isClosing)
	{
		// Process Events
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				isClosing = true;
				break;
			case sf::Event::Resized:
				//window->setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
				break;
			}
		}

		if (!isClosing)
		{
			// Update logic if 1/60 seconds has passed
			while (deltaTime > ups)
			{
				deltaTime -= ups;
				delta = deltaTime.asSeconds() * 1000.f;
				game->Update(delta);
			}

			window->clear();
			game->Draw(window);
			window->display();

			deltaTime += clock.restart();
		}
	}

	delete game;
	delete window;

	return EXIT_SUCCESS;
}