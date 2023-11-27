#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	// Début de la boucle de jeu
	sf::CircleShape triangle (80, 3);
	triangle.setFillColor(sf::Color::Red);
	triangle.setPosition(640, 360);
	//triangle.setSize(sf::Vector2f(128, 128));

	sf::Clock frameClock;

	while (window.isOpen())
	{
		// Gérer les événéments survenus depuis le dernier tour de boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
				case sf::Event::Closed:
					// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
					window.close();
					break;

				default:
					break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();
		std::cout << 1.f / deltaTime << " FPS" << std::endl;

		// Logique
		sf::Vector2f pos = triangle.getPosition();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			pos.x = pos.x - deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pos.x = pos.x + deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			pos.y = pos.y - deltaTime * cubeSpeed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			pos.y = pos.y + deltaTime * cubeSpeed;

		triangle.setPosition(pos);

		// Affichage
		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici
		window.draw(triangle);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}
